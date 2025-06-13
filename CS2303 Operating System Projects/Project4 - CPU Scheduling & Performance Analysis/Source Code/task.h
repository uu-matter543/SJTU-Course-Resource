#ifndef TASK_H
#define TASK_H

typedef struct task {
    char *name;
    int tid;
    int priority;
    int burst;
} Task;

#endif
