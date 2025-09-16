#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct block{
    int start;
    int end;
    bool used;
    char pid[10];
};

struct node{
    struct block *hole;
    struct node *prior;
    struct node *next;
};

struct node *head;
struct node *tail;

struct node *unused[256];
int end;

void reorder()
{
    for (int i = 0; i < end; i++)
        for (int j = 0; j < end-i-1; j++)
            if (unused[j]->hole->end - unused[j]->hole->start <
            unused[j+1]->hole->end - unused[j+1]->hole->start)
            {
                struct node *tmp = unused[j];
                unused[j] = unused[j+1];
                unused[j+1] = tmp;
            }
}

void init()
{
    head = (struct node*)malloc(sizeof(struct node));
    tail = (struct node*)malloc(sizeof(struct node));
    head->hole = NULL;
    tail->hole = NULL;
    struct node *whole = (struct node*)malloc(sizeof(struct node));
    whole->hole = (struct block*)malloc(sizeof(struct block));
    whole->hole->start = 0;
    whole->hole->end = 255;
    whole->hole->used = false;
    whole->prior = head;
    whole->next = tail;
    
    head->prior = NULL;
    head->next = whole;
    tail->prior = whole;
    tail->next = NULL;
    
    unused[0] = whole;
    end = 1;
    printf("Available block list created.\n");
}

void print_status()
{
    struct node *tmp = head->next;
    while (tmp != tail)
    {
        if(tmp->hole->used) printf("[%d:%d] - [%s]\n",
        tmp->hole->start*4096, tmp->hole->end*4096+4095, tmp->hole->pid);
        else printf("[%d:%d] - Unused\n",
        tmp->hole->start*4096, tmp->hole->end*4096+4095);
        tmp = tmp->next;
    }
}

void insert_process(struct node* tmp, char *pid, int size)
{
    struct node* allo = (struct node*)malloc(sizeof(struct node));
    allo->hole = (struct block*)malloc(sizeof(struct block));
    allo->hole->start = tmp->hole->start;
    allo->hole->end = tmp->hole->start + size - 1;
    allo->hole->used = true;
    strcpy(allo->hole->pid, pid);
    allo->prior = tmp->prior;
    allo->next = tmp;
    tmp->hole->start = allo->hole->end + 1;
    tmp->prior = allo;
    allo->prior->next = allo;
    if (tmp->hole->start > tmp->hole->end)
    {
        tmp->prior->next = tmp->next;
        tmp->next->prior = tmp->prior;
        for (int i = 0; i < end; i++)
            if (unused[i] == tmp)
            {
                if (i == end-1) unused[i] = unused[end-1];
                end--;
            }
        free(tmp->hole);
        free(tmp);
    }
    reorder();
}

void first_fit(char *pid, int size)
{
    struct node *tmp = head->next;
    int tmp_size = 0;
    while (tmp != tail)
    {
        tmp_size = tmp->hole->end - tmp->hole->start + 1;
        if (!tmp->hole->used && size <= tmp_size)
        {
            insert_process(tmp, pid, size);
            printf("First fit succeeded.\n");
            break;
        }
        else tmp = tmp->next;
    }
    if (tmp == tail) printf("First fit failed.\n");
}

void best_fit(char *pid, int size)
{
    struct node *cur = NULL;
    for (int i = end-1; i>=0; i--)
        if (unused[i]->hole->end - unused[i]->hole->start + 1 >= size)
        {
            cur = unused[i];
            break;
        }
    if (!cur) printf("Best fit failed.\n");
    else
    {
        insert_process(cur, pid, size);
        printf("Best fit succeeded.\n");
    }
}

void worst_fit(char *pid, int size)
{
    struct node *cur = NULL;
    if (end > 0 && unused[0]->hole->end-unused[0]->hole->start+1 >= size) cur = unused[0];
    if (!cur) printf("Worst fit failed.\n");
    else
    {
        insert_process(cur, pid, size);
        printf("Worst fit succeeded.\n");
    }
}

void release(char *pid)
{
    struct node* tmp = head->next;
    while (tmp != tail)
    {
        if (strcmp(tmp->hole->pid, pid) == 0) tmp->hole->used = false;
        unused[end] = tmp;
        end++;
        tmp = tmp->next;
    }
    tmp = head->next->next;
    while (tmp != tail)
    {
        if (!tmp->prior->hole->used && !tmp->hole->used)
        {
            struct node *del = tmp->prior;
            tmp->hole->start = del->hole->start;
            tmp->prior = del->prior;
            del->prior->next = tmp;
            for (int i = 0; i < end; i++)
                if (unused[i] == del)
                {
                    if (i != end-1) unused[i] = unused[end-1];
                    end--;
                }
            free(del->hole);
            free(del);
        }
        tmp = tmp->next;
    }
    reorder();
    printf("Released [%s] if it exists.\n", pid);
}

int main(int argc, char **argv)
{
    init();
    char command[10];
    char pid[10];
    int size;
    char method;
    while(true)
    {
        printf("allocator>");
        scanf("%s", command);
        if (strcmp("exit", command) == 0) break;
        if (strcmp("STAT", command) == 0) print_status();
        else if (strcmp("RQ", command) == 0)
        {
            scanf("%s %d %c", pid, &size, &method);
            size = size / 4096 + (size%4096!=0);
            if (method == 'F') first_fit(pid, size);
            if (method == 'B') best_fit(pid, size);
            if (method == 'W') worst_fit(pid, size);
        }
        else if (strcmp("RL", command) == 0)
        {
            scanf("%s", pid);
            release(pid);
        }
    }
    printf("Exited from allocator.\n");
    return 0;
}
