#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include "threadpool.h"

bool close = false;

struct task
{
    void (*function)(void *p);
    void *data;
};
struct task_node
{
    struct task to_do;
    struct task_node *next;
};
struct task_node *head, *tail;

pthread_t bee[3];
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;

int enqueue(struct task t) 
{
    pthread_mutex_lock(&queue_mutex);
    tail->next = (struct task_node*)malloc(sizeof(struct task_node));
    if (tail->next == NULL)
    {
        printf("Error: Queue is full!\n");
        return 1;
    }
    tail = tail->next;
    tail->to_do = t;
    pthread_mutex_unlock(&queue_mutex);
    return 0;
}

struct task dequeue() 
{
    pthread_mutex_lock(&queue_mutex);
    if (head == tail)
    {
        printf("Error: Queue is empty!\n");
        exit(0);
    }
    struct task_node *del = head;
    head = head->next;
    free(del);
    pthread_mutex_unlock(&queue_mutex);
    return head->to_do;
}

void *worker(void *param)
{
    static struct task to_execute;
    while (true)
    {
        sem_wait(&sem);
        if (close) pthread_exit(0);
        to_execute = dequeue();
        execute(to_execute.function, to_execute.data);
    }
    pthread_exit(0);
}

void execute(void (*somefunction)(void *p), void *p)
{
    (*somefunction)(p);
}

int pool_submit(void (*somefunction)(void *p), void *p)
{
    struct task to_do;
    to_do.function = somefunction;
    to_do.data = p;
    enqueue(to_do);
    sem_post(&sem);
    return 0;
}

void pool_init(void)
{
    head = (struct task_node*)malloc(sizeof(struct task_node));
    tail = head;
    sem_init(&sem, 0, 0);
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&bee[3],NULL,worker,NULL);
        printf("Thread %d created.\n", i);
    }
}

void pool_shutdown(void)
{
    close = true;
    for (int i = 0; i < 3; i++) sem_post(&sem);
    for (int i = 0; i < 3; i++) pthread_join(bee[i], NULL);
    printf("Joined the threads.\n");
    sem_destroy(&sem);
    pthread_mutex_destroy(&queue_mutex);
}
