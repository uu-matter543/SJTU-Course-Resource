import java.util.concurrent.*;
import java.util.Scanner;

public class mergesort extends RecursiveAction
{
  private int[] data;
  private int left;
  private int right;
  
  public mergesort(int[] data, int left, int right)
  {
    this.data = data;
    this.left = left;
    this.right = right;
  }
  
  protected void compute()
  {
    if (right - left <= 3) insertionsort(data, left, right);
    else 
    {
      int mid = left + (right - left) / 2;
      invokeAll(new mergesort(data, left, mid),
                new mergesort(data, mid+1, right));
      merge(data, left, mid, right);
    }
  }
  
  private void insertionsort(int[] data, int left, int right)
  {
    for (int i = left + 1; i <= right; i++)
    {
      int tmp = data[i];
      int j = i - 1;
      while (j >= left && data[j] > tmp)
      {
        data[j+1] = data[j];
        j--;
      }
      data[j+1] = tmp;
    }
  }
  
  public void merge(int[] data, int left, int mid, int right)
  {
    int[] tmp = new int[right - left + 1];
    int i = left, j = mid + 1, k = 0;
    while(i <= mid && j <= right)
    {
      if (data[i] <= data[j])
      {
        tmp[k] = data[i];
        i++; k++;
      }
      else
      {
        tmp[k] = data[j];
        j++; k++;
      }
    }
    while (i <= mid)
    {
      tmp[k] = data[i];
      i++; k++;
    }
    while (j <= right)
    {
      tmp[k] = data[j];
      j++; k++;
    }
    System.arraycopy(tmp, 0, data, left, right - left + 1);
  }
  
  public static void main(String[] args)
  {
    Scanner buffer = new Scanner(System.in);
    System.out.println("Please enter the length of array:");
    int size = buffer.nextInt();
    int[] data = new int[size];
    System.out.println("Please enter the elements of array:");
    for (int i = 0; i < size; i++) data[i] = buffer.nextInt();
    buffer.close();
    ForkJoinPool thread_pool = new ForkJoinPool();
    mergesort sorter = new mergesort(data, 0, size - 1);
    thread_pool.invoke(sorter);
    for (int i = 0; i < size; i++) System.out.print(data[i] + " ");
    System.out.println("");
  }
}
