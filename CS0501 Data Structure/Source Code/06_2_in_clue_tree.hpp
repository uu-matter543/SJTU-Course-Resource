#ifndef in_clue_tree_h
#define in_clue_tree_h

#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template <class T>
class in_clue_list {
private:
    struct clue_node {
        T data;
        clue_node* left;
        clue_node* right;
        bool lc;
        bool rc;

        clue_node(const T& x, clue_node* l = nullptr, clue_node* r = nullptr, bool lc_flag = false, bool rc_flag = false)
            : data(x), left(l), right(r), lc(lc_flag), rc(rc_flag) {}
    };
    clue_node* root;
    clue_node* first;
    T flag;

    void delete_node(clue_node* p)
    {
        if (p)
        {
            if (!p->lc) delete_node(p->left);
            if (!p->rc) delete_node(p->right);
            delete p;
        }
    }

public:
    in_clue_list(const T& x) : root(nullptr), first(nullptr), flag(x) {}

    ~in_clue_list()
    {
        clear();
    }

    void clear()
    {
        delete_node(root);
        root = nullptr;
        first = nullptr;
    }

    void build_b_tree()
    {
        clear();
        T x;
        cout << "Enter the root node: ";
        cin >> x;
        if (x == flag) return;
        root = new clue_node(x);
        clue_node* current = root;
        queue<clue_node*> q;
        q.push(current);
        while (!q.empty())
        {
            clue_node* p = q.front();
            q.pop();
            T left, right;
            cout << "Enter left child of " << p->data << " (use '" << flag << "' for null): ";
            cin >> left;
            if (left != flag)
            {
                p->left = new clue_node(left);
                q.push(p->left);
            }
            cout << "Enter right child of " << p->data << " (use '" << flag << "' for null): ";
            cin >> right;
            if (right != flag)
            {
                p->right = new clue_node(right);
                q.push(p->right);
            }
        }
    }

    clue_node* add_clue()
    {
        stack<clue_node*> s;
        stack<int> flag;
        clue_node* tmp = root;
        if (!tmp)
        {
            first = tmp;
            return first;
        }
        clue_node* pre = nullptr;
        s.push(tmp);
        flag.push(0);
        while (!s.empty())
        {
            tmp = s.top();
            int f = flag.top();
            s.pop();
            flag.pop();
            if (f == 1)
            {
                if (!first) first = tmp;
                if (tmp->right)
                {
                    s.push(tmp->right);
                    flag.push(0);
                }
                if (!tmp->left)
                {
                    tmp->left = pre;
                    tmp->lc = true;
                }
                if (pre && !pre->right)
                {
                    pre->right = tmp;
                    pre->rc = true;
                }
                pre = tmp;
            }
            else
            {
                s.push(tmp);
                flag.push(1);
                if (tmp->left)
                {
                    s.push(tmp->left);
                    flag.push(0);
                }
            }
        }
        return first;
    }

    void in_order_by_clues() const
    {
        if (!first)
        {
            cout << "The tree is empty." << endl;
            return;
        }
        clue_node* p = first;
        while (p)
        {
            cout << p->data << " ";
            if (p->rc) p = p->right;
            else
            {
                p = p->right;
                while (p && !p->lc) p = p->left;
            }
        }
        cout << endl;
    }
};

void in_clue_tree_test()
{
    cout << "Enter the binary tree of type 'char'(use '~' for null):" << endl;
    in_clue_list<char> tree('~');
    tree.build_b_tree();
    cout << "B-tree has been built. " << endl;
    tree.add_clue();
    cout << "Clues have been added. " << endl;
    cout << "In-order traversal using clues: ";
    tree.in_order_by_clues();
}

#endif