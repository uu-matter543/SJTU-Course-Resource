#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "CPU.h"

struct node* head = NULL;

int tid_value = 0;
int task_cnt = 0;
int total_task_cnt = 0;
int time = 0;
int turn = 0;
int wait = 0;
int resp = 0;
void add(char *name, int priority, int burst)
{
  Task *new_task = malloc(sizeof(Task));
  new_task->tid = __sync_fetch_and_add(&tid_value,1);
  new_task->name = name;
  new_task->priority = priority;
  new_task->burst = burst;
  insert(&head, new_task);
  task_cnt++;
}

void schedule()
{
  total_task_cnt = task_cnt;
  while(true)
  {
    if (head == NULL) break;
    struct node *search = head;
    struct node *current = head;
    while (search->next != NULL)
    {
      search = search->next;
      if (search->task->priority >= current->task->priority) current = search;
    }
    
    run(current->task, current->task->burst);
    
    resp += time;
    time += current->task->burst;
    turn += time;
    wait += current->task->burst * (task_cnt-1);
    
    delete(&head, current->task);
    task_cnt--;
  }
  printf("Average turn time: %f\n", (float)turn/total_task_cnt);
  printf("Average wait time: %f\n", (float)wait/total_task_cnt);
  printf("Average resp time: %f\n", (float)resp/total_task_cnt);
}
