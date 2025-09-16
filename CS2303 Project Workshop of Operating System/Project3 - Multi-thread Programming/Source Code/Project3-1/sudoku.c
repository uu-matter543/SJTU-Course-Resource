#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int sudoku[9][9];
bool row_valid = true, column_valid = true, block_valid = true;

bool row ()
{
  for (int i = 0; i < 9; i++)
  {
    bool numlib[9] = {false, false, false, false, false, false, false, false, false};
    for (int j = 0; j < 9; j++)
    {
      if (numlib[sudoku[i][j] - 1]) return false;
      else numlib[sudoku[i][j] - 1] = true;
    }
  }
  return true;
}

bool column ()
{
  for (int i = 0; i < 9; i++)
  {
    bool numlib[9] = {false, false, false, false, false, false, false, false, false};
    for (int j = 0; j < 9; j++)
    {
      if (numlib[sudoku[j][i] - 1]) return false;
      else numlib[sudoku[j][i] - 1] = true;
    }
  }
  return true;
}

bool block (int row, int column)
{
  row = row * 3;
  column = column * 3;
  bool numlib[9] = {false, false, false, false, false, false, false, false, false};
  for (int i = row; i < row + 3; i++)
  {
    for (int j = column; j < column + 3; j++)
    {
      if (numlib[sudoku[i][j] - 1]) return false;
      else numlib[sudoku[i][j] - 1] = true;
    }
  }
  return true;
}

void *row_thread (void *param)
{
  row_valid = row();
  pthread_exit(0);
}

void *column_thread (void *param)
{
  column_valid = column();
  pthread_exit(0);
}

void *block_thread (void *param)
{
  int blocknum = (int)param;
  int row = blocknum / 3;
  int column = blocknum % 3;
  if (!block(row, column)) block_valid = false;
  pthread_exit(0);
}

int main ()
{
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      scanf("%d", &sudoku[i][j]);
  
  pthread_t tid[11];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  
  for (int i = 0; i < 9; i++)
    pthread_create(&tid[i], &attr, block_thread, (void *)i);
  pthread_create(&tid[9], &attr, row_thread, (void *)9);
  pthread_create(&tid[10], &attr, column_thread, (void *)10);
  for (int i = 0; i < 11; i++)
    pthread_join(tid[i], NULL);
  
  if (!row_valid) printf("At least one error row exists.\n");
  if (!column_valid) printf("At least one error column exists.\n");
  if (!block_valid) printf("At lease one block exists.\n");
  if (row_valid && column_valid && block_valid) printf("Solution is perfect!\n");
  return 0;
}
