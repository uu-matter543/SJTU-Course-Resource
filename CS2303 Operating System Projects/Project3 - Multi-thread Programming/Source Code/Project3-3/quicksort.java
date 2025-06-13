import java.util.concurrent.*;
import java.util.Scanner;

public class quicksort extends RecursiveAction
{
  private int[] data;
  private int left;
  private int right;
  
  public quicksort(int[] data, int left, int right)
  {
    this.data = data;
    this.left = left;
    this.right = right;
  }
  
  protected void compute()
  {
    if (left < right)
    {
      int mid = left + (right - left) / 2;
      mid = partition(mid);
      invokeAll(new quicksort(data, left, mid - 1),
                new quicksort(data, mid+1, right));
    }
  }
  
  private int partition(int mid)
  {
    int pivot = data[mid];
    swap(mid,right);
    int index = left;
    for(int i = left; i < right; i++)
    {
      if (data[i] < pivot)
      {
        swap(i, index);
        index++;
      }
    }
    swap(index, right);
    return index;
  }
  
  private void swap(int i, int j)
  {
    int tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
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
    quicksort sorter = new quicksort(data, 0, size - 1);
    thread_pool.invoke(sorter);
    for (int i = 0; i < size; i++) System.out.print(data[i] + " ");
    System.out.println("");
  }
}
