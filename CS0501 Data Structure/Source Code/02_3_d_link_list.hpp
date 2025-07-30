#ifndef d_link_list_h
#define d_link_list_h

#include <iostream>

using namespace std;

template <class T>
class d_link_list
{
private:
    struct node
    {
        T data;
        node* prior;
        node* next;

        node() : prior(nullptr), next(nullptr) {}
        node(const T& x, node* p = nullptr, node* q = nullptr) : data(x), prior(p), next(q) {}
    };
    node *head;
    node *tail;

    node* move(int i) const
    {
        node* p = head;
        while (i-- > 0) p = p->next;
        return p;
    }

public:
    d_link_list()
    {
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prior = head;
    }

    ~d_link_list()
    {
        clear();
        delete head;
        delete tail;
    }

    int length() const
    {
        int len = 0;
        node* p = head->next;
        while (p != tail) {
            len++;
            p = p->next;
        }
        return len;
    }

    void insert(int i, const T& x)
    {
        node* pos = move(i - 1);
        pos->next = new node(x, pos, pos->next);
        pos->next->next->prior = pos->next;
    }

    void remove(int i)
    {
        node* pos = move(i - 1);
        node* del = pos->next;
        if (del == tail) return;
        pos->next = del->next;
        del->next->prior = pos;
        delete del;
    }

    int search(int i) const
    {
        node* p = head->next;
        int j = 0;
        while (p != tail && j < i) {
            p = p->next;
            j++;
        }
        if (p == tail) return -1;
        else return j;
    }

    T visit(int i) const
    {
        node* p = move(i);
        if (p != tail) return p->data;
        else throw "Index out of range";
    }

    void traverse() const
    {
        node* p = head->next;
        while (p != tail) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    void clear()
    {
        node* p = head->next;
        head->next = tail;
        tail->prior = head;
        while (p != tail) {
            node* del = p;
            p = p->next;
            delete del;
        }
    }
};

void d_link_list_test()
{
    d_link_list<int> s;
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