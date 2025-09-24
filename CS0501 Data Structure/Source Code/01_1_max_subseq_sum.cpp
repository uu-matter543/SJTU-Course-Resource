#include <iostream>

using namespace std;

int max_subsequence_sum(int a[], int size, int &start, int &end) {
    int max_sum = 0;
    int current_sum = 0;
    start = 0;
    end = -1;
    int temp_start = 0;
    for (int i = 0; i < size; ++i)
    {
        current_sum += a[i];
        if (current_sum > max_sum)  //if find a larger sum sequence
        {
            max_sum = current_sum;  //update max sum
            start = temp_start;     //update start index
            end = i;                //update end index
        }
        if (current_sum < 0)        //exclude negative sum sequence
        {
            current_sum = 0;        //reset sum
            temp_start = i + 1;     //reset start index
        }
    }
    return max_sum;
}

int main()
{
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    int a[n];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i) cin >> a[i];
    int start, end;
    int max_sum = max_subsequence_sum(a, n, start, end);
    cout << "Maximum subsequence sum is: " << max_sum << endl;
    cout << "Subsequence indices: [" << start << ", " << end << "]" << endl;
    return 0;
}