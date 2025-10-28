#ifndef STATIC_SEARCH_TABLE_H
#define STATIC_SEARCH_TABLE_H

#include <iostream>

using namespace std;

template <class T>
int seq_search(T arr[], int size, T& key)
{
    arr[0] = key;
    int i;
    for (i = size; arr[i] != key; i--);
    return i;
}

template <class T>
int bin_search(T arr[], int size, T& key)
{
    int left = 1;
    int right = size;
    while (left <= right)
    {
        int mid = (right - left) / 2 + left;
        if (arr[mid] < key) left = mid + 1;
        else if (arr[mid] > key) right = mid - 1;
        else return mid;
    }
    return 0;
}

void static_search_table_test()
{
    cout << "Enter the number of elements: ";
    int n;
    cin >> n;
    int *arr = new int[n + 1];
    cout << "Enter " << n << " elements:" << endl;
    cout << "(Note: For binary search, elements must be sorted in ascending order)" << endl;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    cout << "Enter the key to search: ";
    int key;
    cin >> key;
    int seq_index = seq_search(arr, n, key);
    if (seq_index != 0)
        cout << "Sequential Search: Key found at index " << seq_index << endl;
    else
        cout << "Sequential Search: Key not found." << endl;
    int bin_index = bin_search(arr, n, key);
    if (bin_index != 0)
        cout << "Binary Search: Key found at index " << bin_index << endl;
    else
        cout << "Binary Search: Key not found." << endl;
    delete[] arr;
}

#endif
