#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include "buffer.h"

sem_t empty, full;
bool closedown = false;

void *producer(void *param)
{
    buffer_item item;
    while (true)
    {
        sleep(rand() % 5);
        item = rand() % 100;
        sem_wait(&empty);
        if (closedown) break;
        if (insert_item(item))
        {
            printf("Producer thread error!\n");
            break;
        }
        else printf("Producer produced item %d\n", item);
        sem_post(&full);
    }
}


void *consumer(void *param)
{
    buffer_item item;
    while (true)
    {
        sleep(rand() % 5);
        item = rand() % 100;
        sem_wait(&full);
        if (closedown) break;
        if (remove_item(&item))
        {
            printf("Consumer thread error!\n");
            break;
        }
        else printf("Consumer consumed item %d\n", item);
        sem_post(&empty);
    }
}

int main()
{
    int sleep_time;
    int producer_counts;
    int consumer_counts;
    printf("Please enter total sleep time, the number of producers, the number of consumers:\n");
    scanf("%d %d %d", &sleep_time, &producer_counts, &consumer_counts);
    buffer_init();
    sem_init(&empty, 0, 4);
    sem_init(&full, 0, 0);
    for (int i = 0; i < producer_counts; i++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, producer, NULL);
    }
    for (int i = 0; i < consumer_counts; i++)
    {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, consumer, NULL);
    }
    sleep(sleep_time);
    closedown = true;
    for (int i = 0; i < producer_counts; i++) sem_post(&empty);
    for (int i = 0; i < consumer_counts; i++) sem_post(&full);
    printf("Program finished.\n");
    return 0;
}
