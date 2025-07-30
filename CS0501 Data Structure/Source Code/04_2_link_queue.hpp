#ifndef link_queue_h
#define link_queue_h

#include <iostream>

using namespace std;

template <class T>
class link_queue{
private:
    struct Node {
        T data;
        Node *next;
        Node(const T &x, Node *n = nullptr) : data(x), next(n) {}
    };
    Node *head;
    Node *tail;

public:
    link_queue()
    {
        head = tail = nullptr;
    }

    ~link_queue()
    {
        while (!is_empty())
        {
            T x;
            dequeue();
        }
    }

    void enqueue(const T &x)
    {
        Node *new_node = new Node(x);
        if (tail) tail->next = new_node;
        else head = new_node;
        tail = new_node;
    }

    void dequeue()
    {
        if (is_empty())
        {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node *temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
    }

    void front(T &x) const
    {
        if (is_empty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        x = head->data;
    }

    bool is_empty() const
    {
        return head == nullptr;
    }
};

void link_queue_test()
{
    link_queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.enqueue(6);
    int front_value;
    q.front(front_value);
    cout << "Front value after enqueue 1,2,3,4,5,6: " << front_value << endl;
    q.dequeue();
    q.front(front_value);
    cout << "Front value after dequeue: " << front_value << endl;
    cout << "Is the queue empty? " << (q.is_empty() ? "Yes" : "No") << endl;
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    cout << "Is the queue empty after dequeuing all elements? " << (q.is_empty() ? "Yes" : "No") << endl;
    cout << "Trying to dequeue from an empty queue:" << endl;
    q.dequeue();
    cout << "Trying to get front value from an empty queue:" << endl;
    q.front(front_value);
}

#endif