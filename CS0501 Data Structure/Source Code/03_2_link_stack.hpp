#ifndef link_stack_h
#define link_stack_h

#include <iostream>

using namespace std;

template <class T>
class link_stack {
private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *n = nullptr) : data(x), next(n) {}
    };
    node *top_p;

public:
    link_stack()
    {
        top_p = nullptr;
    }

    ~link_stack()
    {
        clear();
    }

    void push(const T &x)
    {
        top_p = new node(x, top_p);
    }

    void pop()
    {
        if (is_empty()) throw "Stack is empty";
        node *del = top_p;
        top_p = top_p->next;
        delete del;
    }

    T top() const
    {
        if (is_empty()) throw "Stack is empty";
        return top_p->data;
    }

    bool is_empty() const
    {
        return top_p == nullptr;
    }

    void clear()
    {
        while (!is_empty()) pop();
    }
};

void link_stack_test()
{
    link_stack<int> s;
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