#ifndef seq_stack_h
#define seq_stack_h

#include <iostream>

using namespace std;

template <class T>
class seq_stack {
private:
    T *data;
    int max;
    int top_p;

    void double_size()
    {
        T *tmp = data;
        max *= 2;
        data = new T[max];
        for (int i = 0; i < top_p; i++) data[i] = tmp[i];
        delete[] tmp;
    }

public:
    seq_stack(int init)
    {
        data = new T[init];
        max = init;
        top_p = -1;
    }

    ~seq_stack()
    {
        delete[] data;
    }

    void push(const T &x)
    {
        if (top_p == max - 1) double_size();
        data[++top_p] = x;
    }

    void pop()
    {
        if (top_p == -1) throw "Stack is empty";
        top_p--;
    }

    T top() const
    {
        if (top_p == -1) throw "Stack is empty";
        return data[top_p];
    }

    bool is_empty() const
    {
        return top_p == -1;
    }

    void clear()
    {
        top_p = -1;
    }
};

void seq_stack_test()
{
    seq_stack<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    cout << "Top element after pushing 1,2,3,4,5: " << s.top() << endl;
    s.push(6);
    cout << "Top element after pushing 6: " << s.top() << endl;
    s.pop();
    s.pop();
    cout << "Top element after pop twice: " << s.top() << endl;
    cout << "Is stack empty? " << (s.is_empty() ? "Yes" : "No") << endl;
    s.clear();
    cout << "Is stack empty after clear? " << (s.is_empty() ? "Yes" : "No") << endl;
}

#endif