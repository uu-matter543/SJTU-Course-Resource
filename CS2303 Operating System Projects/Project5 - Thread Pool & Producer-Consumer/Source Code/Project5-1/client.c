#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "threadpool.h"

struct data
{
    int a;
    int b;
};

void add(void *param)
{
    struct data *temp;
    temp = (struct data*)param;
    printf("I add two values %d and %d result = %d\n",temp->a, temp->b, temp->a + temp->b);
}

int main(void)
{
    struct data work[15];
    for(int i = 0; i < 15; i++)
    {
        work[i].a = rand() % 128;
        work[i].b = rand() % 128;
    }
    printf("15 Works have been created.\n");
    pool_init();
    for(int i = 0; i < 15; i++) pool_submit(&add,&work[i]);
    sleep(1);
    pool_shutdown();

    return 0;
}
