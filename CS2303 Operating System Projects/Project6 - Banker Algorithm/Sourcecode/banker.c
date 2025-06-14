#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int available[4];
int max[5][4];
int need[5][4];
int allocation[5][4];

void print_status()
{
    printf("Available:\n");
    for (int i=0; i<4; i++) printf("%d ", available[i]);
    printf("\n");
    printf("Max:\n");
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<4; j++) printf("%d ", max[i][j]);
        printf("\n");
    }
    printf("Need:\n");
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<4; j++) printf("%d ", need[i][j]);
        printf("\n");
    }
    printf("Allocated:\n");
    for (int i=0; i<5; i++)
    {
        for (int j = 0; j<4; j++) printf("%d ", allocation[i][j]);
        printf("\n");
    }
}

void divide(char *input, char **param)
{
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL)
    {
        param[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    param[i] = NULL;
}

bool safe()
{
    int tmp[4];
    bool finish[5];
    for (int i=0; i<4; i++) tmp[i] = available[i];
    for (int i=0; i<5; i++) finish[i] = false;
    bool progressive = true;
    while (progressive)
    {
        progressive = false;
        for (int i=0; i<5; i++)
        {
            bool execute = true;
            for (int j=0; j<4; j++) if (tmp[j]<need[i][j]) execute = false;
            if (execute && !finish[i])
            {
                for (int j=0; j<4; j++) tmp[j] = tmp[j] + allocation[i][j];
                progressive = true;
                finish[i] = true;
            }
        }
    }
    for (int i=0; i<5; i++) if (!finish[i]) return false;
    return true;
}

void apply_resource(char **param)
{
    int tid = atoi(param[1]);
    int apply[4];
    for (int i=0; i<4; i++) apply[i] = atoi(param[i+2]);
    bool accept = true;
    for (int i=0; i<4; i++)
    {
        if (apply[i] > need[tid][i]) 
        {
            printf("Total possession[%d] will exceed maximum. Refuse request.\n", i);
            accept = false;
        }
        if (apply[i] > available[i])
        {
            printf("Current available[%d] is not enough. Refuse request.\n", i);
            accept = false;
        }
    }
    if (!accept) return;
    for (int i=0; i<4; i++)
    {
        available[i] = available[i] - apply[i];
        allocation[tid][i] = allocation[tid][i] + apply[i];
        need[tid][i] = need[tid][i] - apply[i];
    }
    accept = safe();
    if (!accept)
    {
        printf("The system will be in deadlock. Refuse request.\n");
        for (int i=0; i<4; i++)
        {
            available[i] = available[i] + apply[i];
            allocation[tid][i] = allocation[tid][i] - apply[i];
            need[tid][i] = need[tid][i] + apply[i];
        }
    }
    else printf("Accept request.\n");
}

void release_resource(char **param)
{
    int tid = atoi(param[1]);
    int apply[4];
    for (int i=0; i<4; i++) apply[i] = atoi(param[i+2]);
    bool accept = true;
    for (int i=0; i<4; i++)
        if (allocation[tid][i] < apply[i])
        {
            printf("The thread does not have enough resource[%d]. Refuse request.\n", i);
            accept = false;
        }
    if (accept)
    {
        printf("Accept request.\n");
        for (int i=0; i<4; i++)
        {
            available[i] = available[i] + apply[i];
            allocation[tid][i] = allocation[tid][i] - apply[i];
            need[tid][i] = need[tid][i] + apply[i];
        }
    }
}

int main(int argc, char **argv)
{
    if (argc != 5)
    {
        printf("Unacceptable usage!\n");
        return -1;
    }
    for (int i=0; i<4; i++) available[i] = atoi(argv[i+1]);
    FILE *f;
    f = fopen("input.txt","r");
    for (int i=0; i<5; i++) for (int j=0; j<4; j++) fscanf(f, "%d", &max[i][j]);
    for (int i=0; i<5; i++) for (int j=0; j<4; j++) need[i][j] = max[i][j];
    fclose(f);
    char *input = (char*)malloc(100*sizeof(char));
    while (true)
    {
        printf("banker>");
        fflush(stdout);
        fgets(input, 100, stdin);
        input[strlen(input) - 1] = '\0';
        if (strcmp(input, "exit") == 0) break;
        if (strcmp(input, "*") == 0)
        {
            print_status();
            continue;
        }
        char *param[10];
        for (int i=0; i<10; i++) param[i] = (char*)malloc(10*sizeof(char));
        divide(input, param);
        if (strcmp(param[0], "RQ") == 0) apply_resource(param);
        if (strcmp(param[0], "RL") == 0) release_resource(param);
    }
    printf("Exited from banker.\n");
    return 0;
}
