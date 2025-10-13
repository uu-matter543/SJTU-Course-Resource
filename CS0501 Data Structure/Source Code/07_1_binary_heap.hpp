#ifndef binary_heap_hpp
#define binary_heap_hpp

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class binary_heap {
private:
    T* data;
    int max;
    int size;

    void double_size()
    {
        T* tmp = data;
        max *= 2;
        data = new T[max];
        for (int i = 1; i <= size; i++) data[i] = tmp[i];
        delete[] tmp;
    }

    void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    void fix_down(int i)
    {
        if (i < 1 || i > size) throw "Index out of range";
        while (true)
        {
            int lc = 2*i, rc = 2*i+1;
            if (lc > size) break;
            else if (rc > size)
            {
                if (data[i] > data[lc]) swap(data[i], data[lc]);
                break;
            }
            else
            {
                int smaller = i;
                if (data[smaller] > data[lc]) smaller = lc;
                if (data[smaller] > data[rc]) smaller = rc;
                if (smaller == i) break;
                swap(data[i], data[smaller]);
                i = smaller;
            }
        }
    }
public:
    binary_heap(int init = 100)
    {
        max = init;
        size = 0;
        data = new T[max];
    }

    ~binary_heap()
    {
        delete[] data;
    }

    bool is_empty() const
    {
        return size == 0;
    }

    T top() const
    {
        if (is_empty()) throw "Heap is empty";
        return data[1];
    }

    void push(const T &x)
    {
        if (size + 1 == max) double_size();
        data[++size] = x;
        int i = size;
        while (i > 1 && data[i/2] > data[i])
        {
            swap(data[i/2], data[i]);
            i /= 2;
        }
    }

    void pop()
    {
        if (is_empty()) throw "Heap is empty";
        data[1] = data[size--];
        int i = 1;
        fix_down(i);
    }

    void traverse() const
    {
        for (int i = 1; i <= size; i++) cout << data[i] << " ";
        cout << endl;
    }

    void rebuild(const vector<T> &arr)
    {
        int n = arr.size();
        delete[] data;
        max = n+1;
        size = n;
        data = new T[max];
        for (int i = 0; i < n; i++) data[i+1] = arr[i];
        for (int i = n/2; i >= 1; i--) fix_down(i);
    }
};

void binary_heap_test()
{
    vector<int> arr = {40, 20, 60, 15, 30, 25, 10, 35, 45, 50, 55};
    cout << "Initial array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    binary_heap<int> bh;
    bh.rebuild(arr);
    cout << "Binary heap after rebuild: ";
    bh.traverse();
    cout << "Top element: " << bh.top() << endl;
    bh.push(5);
    cout << "Binary heap after pushing 5: ";
    bh.traverse();
    bh.pop();
    cout << "Binary heap after popping top element: ";
    bh.traverse();
}

#endif