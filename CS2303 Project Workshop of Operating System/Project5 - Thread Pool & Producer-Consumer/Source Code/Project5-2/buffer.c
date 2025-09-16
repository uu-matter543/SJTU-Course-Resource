#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "buffer.h"

int head, tail;
buffer_item buffer[5];
pthread_mutex_t mutex;

int buffer_init()
{
    head = 0;
    tail = 0;
    pthread_mutex_init(&mutex, NULL);
    if (head == 0 && tail == 0) return 0;
    else return -1;
}

int insert_item(buffer_item item)
{
    bool status = false;
    pthread_mutex_lock(&mutex);
    if ((tail+1) % 5 != head)
    {
        tail = (tail+1) % 5;
        buffer[tail] = item;
        status = true;
    }
    pthread_mutex_unlock(&mutex);
    if (status) return 0;
    else return 1;
}

int remove_item(buffer_item *item)
{
    bool status = false;
    pthread_mutex_lock(&mutex);
    if (head != tail)
    {
        head = (head+1) % 5;
        *item = buffer[head];
        status = true;
    }
    pthread_mutex_unlock(&mutex);
    if (status) return 0;
    else return 1;
}
