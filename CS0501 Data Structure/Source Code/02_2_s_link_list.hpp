#ifndef s_link_list_h
#define s_link_list_h

#include <iostream>

using namespace std;

template <class T>
class s_link_list{
private:
    struct node{
        T data;
        node* next;

        node() : next(nullptr) {}
        node(const T& x, node* p = nullptr) : data(x), next(p) {}
    };
    node* head;

    node* move(int i) const
    {
        node* p = head;
        while (i-- > 0) p = p->next;
        return p;
    }

public:
    s_link_list()
    {
        head = new node();
    }

    ~s_link_list()
    {
        clear();
        delete head;
    }

    int length() const
    {
        int len = 0;
        node* p = head->next;
        while (p) {
            len++;
            p = p->next;
        }
        return len;
    }
    
    void insert(int i, const T& x)
    {
        node* pos = move(i - 1);
        pos->next = new node(x, pos->next);
    }

    void remove(int i)
    {
        node* pos = move(i - 1);
        node* del = pos->next;
        pos->next = del->next;
        delete del;
    }

    int search(int i) const
    {
        node* p = head->next;
        int j = 0;
        while (p && j < i) {
            p = p->next;
            j++;
        }
        if (p == nullptr) return -1;
        else return j;
    }

    T visit(int i) const
    {
        return move(i)->data;
    }

    void traverse() const
    {
        node* p = head->next;
        while (p != nullptr) {
            cout << p->data << "\t";
            p = p->next;
        }
        cout << endl;
    }

    void clear()
    {
        node* p = head->next;
        head->next = nullptr;
        while (p != nullptr) {
            node* del = p;
            p = p->next;
            delete del;
        }
    }
};

void s_link_list_test()
{
    s_link_list<int> s;
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