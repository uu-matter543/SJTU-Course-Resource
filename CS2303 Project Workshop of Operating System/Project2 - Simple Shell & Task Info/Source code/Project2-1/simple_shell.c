#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int divide(char *input, char **args)
{
  int i = 0;
  char* token = strtok(input, " ");
  while (token != NULL)
  {
    args[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  return i;
}

bool check_for_parallelism(char* input)
{
  int len = strlen(input);
  if (len && input[len-1] == '&') return false;
  else return true;
}

int main(void)
{
  char *args[41];
  char input[80], last[80];
  char ifile[80], ofile[80];
  int should_run = 1;
  bool wait_for_children = true;
  bool history = false;
  pid_t pid;
  while (should_run)
  {
    printf("osh>");
    fflush(stdout);
    
    fgets(input, 80, stdin);
    input[strlen(input)-1] = '\0';
    
    if (strcmp(input, "exit") == 0)
    {
      printf("Exited from simple_shell %d\n", pid);
      should_run = 0;
      break;
    }
    
    if (strcmp(input, "!!") == 0)
    {
      if (history)
      {
        printf("Execute this command again:[%s]\n", last);
        strcpy(input, last);
      }
      else
      {
        printf("No command in history!\n");
        continue;
      }
    }
    else
    {
      strcpy(last, input);
      history = true;
    }
    
    wait_for_children = check_for_parallelism(input);
    pid = fork();
    if (pid == 0)
    {
      for (int i = 0; i <= 40; i++)
        args[i] = (char*) malloc(80 * sizeof(char));
      int parts = divide(input, args);
      for (int i = parts; i <= 40; i++)
      {
        free(args[i]);
        args[i] = NULL;
      }
      if (!wait_for_children)
      {
        args[parts - 1] = NULL;
        parts--;
      }
      
      int pipe_token = -1;
      for (int i = 0; i < parts; i++)
        if (strcmp(args[i], "|") == 0)
        {
          pipe_token = i;
          break;
        }
      
      if (pipe_token >= 0)
      {
        if (pipe_token == 0 || pipe_token == parts-1)
        {
          printf("Unacceptable pipe usage\n");
          continue;
        }
        int fd[2];
        pipe(fd);
        pid_t pid_pipe = fork();
        if (pid_pipe == 0)
        {
          for (int i = pipe_token; i < parts; i++)
            args[i] = NULL;
          close(fd[0]);
          dup2(fd[1], STDOUT_FILENO);
          execvp(args[0], args);
          close(fd[1]);
        }
        else
        {
          wait(NULL);
          for (int i = pipe_token + 1; i < parts; i++) args[i - pipe_token - 1] = args[i];
          for (int i = parts - pipe_token - 1; i < parts; i++) args[i] = NULL;
          close(fd[1]);
          dup2(fd[0], STDIN_FILENO);
          close(fd[0]);
          execvp(args[0], args);
        }
      }
      else
      {
        if (parts >= 3)
        {
          if (strcmp(args[parts - 2], "<") == 0)
          {
            strcpy(ifile, args[parts - 1]);
            int fd = open(ifile, O_RDONLY);
            if (fd < 0)
            {
              printf("Failed to open file[%s]\n", ifile);
              continue;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
          }
          if (strcmp(args[parts - 2], ">") == 0)
          {
            strcpy(ofile, args[parts - 1]);
            int fd = open(ofile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (fd < 0)
            {
              printf("Failed to open file[%s]\n", ofile);
              continue;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
          }
          args[parts - 2] = NULL;
          args[parts - 1] = NULL;
          parts -= 2;
          execvp(args[0], args);
        }
        execvp(args[0], args);
      }
    }
    else if (wait_for_children)
      wait(NULL);
  }
  return 0;
}
