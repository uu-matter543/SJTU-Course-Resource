#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int n;
int *before_sort;
int *after_sort;

struct range
{
  int begin;
  int end;
};

int cmp(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

void *sort(void *param)
{
  struct range *obj = (struct range *)param;
  int begin = obj -> begin;
  int end = obj -> end;
  qsort(before_sort + begin, end - begin + 1, sizeof(int), cmp);
  pthread_exit(0);
}

void *merge(void *param)
{
  struct range *obj = (struct range *)param;
  int begin = obj -> begin;
  int end = obj -> end;
  int mid = (end - begin + 1) / 2;
  int i = begin, j = mid + 1, k = begin;
  while (i <= mid && j <= end)
  {
    if (before_sort[i] <= before_sort[j])
    {
      after_sort[k] = before_sort[i];
      i++; k++;
    }
    else
    {
      after_sort[k] = before_sort[j];
      j++; k++;
    }
  }
  while (i <= mid)
  {
    after_sort[k] = before_sort[i];
    i++; k++;
  }
  while (j <= end)
  {
    after_sort[k] = before_sort[j];
    j++; k++;
  }
  pthread_exit(0);
}

int main()
{
  printf("Please enter the size of array:");
  scanf("%d", &n);
  printf("Please enter the elements of array:\n");
  before_sort = (int *)malloc(n * sizeof(int));
  after_sort = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) scanf("%d", before_sort+i);
  
  struct range obj[3];
  obj[0].begin = 0;
  obj[0].end = n - 1;
  obj[1].begin = 0;
  obj[1].end = n / 2;
  obj[2].begin = n / 2 + 1;
  obj[2].end = n - 1;
  
  pthread_t tid[3];
  pthread_create(&tid[1], NULL, sort, &obj[1]);
  pthread_create(&tid[2], NULL, sort, &obj[2]);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  pthread_create(&tid[0], NULL, merge, &obj[0]);
  pthread_join(tid[0], NULL);
  
  for (int i = 0; i < n; i++) printf("%d ", after_sort[i]);
  printf("\n");
  return 0;
}
