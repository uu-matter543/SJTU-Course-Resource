#ifndef seq_queue_h
#define seq_queue_h

#include <iostream>

using namespace std;

template <class T>
class seq_queue {
private:
    T *data;
    int max;
    int head;
    int tail;

    void double_size()
    {
        T *tmp = data;
        data = new T[max * 2];
        for (int i = 0; i < max; i++) data[i] = tmp[(head + i) % max];
        head = 0;
        tail = max - 1;
        max *= 2;
        delete[] tmp;
    }

public:
    seq_queue(int init)
    {
        data = new T[init];
        max = init;
        head = 0;
        tail = 0;
    }

    ~seq_queue()
    {
        delete[] data;
    }

    void enqueue(const T &x)
    {
        if ((tail + 1) % max == head) double_size();
        tail = (tail + 1) % max;
        data[tail] = x;
    }

    void dequeue()
    {
        if (head == tail)
        {
            cout << "Queue is empty!" << endl;
            return;
        }
        head = (head + 1) % max;
    }

    void front(T &x) const
    {
        if (head == tail)
        {
            cout << "Queue is empty!" << endl;
            return;
        }
        x = data[(head + 1) % max];
    }

    bool is_empty() const
    {
        return head == tail;
    }
};

void seq_queue_test()
{
    seq_queue<int> q(5);
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