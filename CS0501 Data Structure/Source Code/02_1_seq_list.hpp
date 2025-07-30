#ifndef seq_list_h
#define seq_list_h

#include <iostream>

using namespace std;

template <class T>
class seq_list {

private:
    T *data;
    int max;
    int size;

    void double_size()
    {
        T *tmp = data;
        max *= 2;
        data = new T[max];
        for (int i = 0; i < size; i++) data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seq_list(int init)
    {
        data = new T[init];
        max = init;
        size = 0;
    }

    ~seq_list()
    {
        delete[] data;
    }

    int length() const
    {
        return size;
    }

    void insert(int i, const T &x)
    {
        if (size == max) double_size();
        for (int j = size; j > i; j--) data[j] = data[j - 1];
        data[i] = x;
        size++;
    }

    void remove(int i)
    {
        for (int j = i; j < size - 1; j++) data[j] = data[j + 1];
        size--;
    }

    int search(const T &x) const
    {
        int i = 0;
        while (i < size && data[i] != x) i++;
        if (i == size) return -1;
        else return i;
    }

    T visit(int i) const
    {
        return data[i];
    }

    void traverse() const
    {
        for (int i = 0; i < size; i++) cout << data[i] << "\t";
        cout << endl;
    }
    
    void clear()
    {
        size = 0;
    }
};

void seq_list_test()
{
    seq_list<int> s(5);
    s.insert(0,1);
    s.insert(1,2);
    s.insert(2,3);
    s.insert(3,4);
    s.insert(4,5);
    cout << "After initializing by {1,2,3,4,5}: " << endl;
    s.traverse();
    cout << "Size of s: " << s.length() << endl;
    cout << "Visit s[2]: " << s.visit(2) << endl;
    cout << "Search 3: " << s.search(3) << endl;
    s.insert(2,6);
    cout << "After adding 6 at s[2]: " << endl;
    s.traverse();
    cout << "Size of s: " << s.length() << endl;
    s.remove(2);
    cout << "After removing s[2]: " << endl;
    s.traverse();
    cout << "Size of s: " << s.length() << endl;
}

#endif