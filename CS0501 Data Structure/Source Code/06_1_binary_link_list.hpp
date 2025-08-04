# ifndef binary_link_list_h
# define binary_link_list_h

#include <iostream>
#include <queue>

using namespace std;

template <class T>
class binary_link_list {
private:
    struct node {
        T data;
        node* left;
        node* right;

        node() : left(nullptr), right(nullptr) {}
        node(const T& x, node* l = nullptr, node* r = nullptr) : data(x), left(l), right(r) {}
    };
    node* root;
    T flag;

    node* find(const T&x) const
    {
        node* p;
        queue<node*> q;
        if (is_empty()) return nullptr;
        q.push(root);
        while (!q.empty())
        {
            p = q.front();
            q.pop();
            if (p->data == x) return p;
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        return nullptr;
    }

    int size(node* p) const
    {
        if (!p) return 0;
        return 1 + size(p->left) + size(p->right);
    }

    int height(node* p) const
    {
        if (!p) return 0;
        int leftHeight = height(p->left);
        int rightHeight = height(p->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    void preorder(node* p) const
    {
        if (p)
        {
            cout << p->data << " ";
            preorder(p->left);
            preorder(p->right);
        }
    }

    void inorder(node* p) const
    {
        if (p)
        {
            inorder(p->left);
            cout << p->data << " ";
            inorder(p->right);
        }
    }

    void postorder(node* p) const
    {
        if (p)
        {
            postorder(p->left);
            postorder(p->right);
            cout << p->data << " ";
        }
    }

    void delete_node(node* p)
    {
        if (p)
        {
            delete_node(p->left);
            delete_node(p->right);
            delete p;
        }
    }

public:
    binary_link_list(const T& x)
    {
        root = nullptr;
        flag = x;
    }

    ~binary_link_list()
    {
        clear();
    }

    bool is_empty() const
    {
        return root == nullptr;
    }

    void clear()
    {   
        delete_node(root);
        root = nullptr;
    }

    int tree_size() const
    {
        return size(root);
    }

    int tree_height() const
    {
        return height(root);
    }

    void pre_order() const
    {
        preorder(root);
        cout << endl;
    }

    void in_order() const
    {
        inorder(root);
        cout << endl;
    }

    void post_order() const
    {
        postorder(root);
        cout << endl;
    }

    void level_order() const
    {
        if (is_empty()) return;
        queue<node*> q;
        q.push(root);
        while (!q.empty())
        {
            node* p = q.front();
            q.pop();
            cout << p->data << " ";
            if (p->left) q.push(p->left);
            if (p->right) q.push(p->right);
        }
        cout << endl;
    }

    T left_child(const T& x) const
    {
        node* p = find(x);
        if (p && p->left) return p->left->data;
        return flag;
    }

    T right_child(const T& x) const
    {    
        node* p = find(x);
        if (p && p->right) return p->right->data;
        return flag;
    }

    void delete_left(const T& x)
    {
        node* p = find(x);
        if (p && p->left)
        {
            delete_node(p->left);
            p->left = nullptr;
        }
    }

    void delete_right(const T& x)
    {
        node* p = find(x);
        if (p && p->right)
        {
            delete_node(p->right);
            p->right = nullptr;
        }
    }

    void input()
    {
        clear();
        T x;
        cout << "Enter the root node: ";
        cin >> x;
        if (x == flag) return;
        root = new node(x);
        queue<node*> q;
        q.push(root);
        while (!q.empty())
        {
            node* p = q.front();
            q.pop();
            T left, right;
            cout << "Enter left child of " << p->data << " (use '" << flag << "' for null): ";
            cin >> left;
            if (left != flag)
            {
                p->left = new node(left);
                q.push(p->left);
            }
            cout << "Enter right child of " << p->data << " (use '" << flag << "' for null): ";
            cin >> right;
            if (right != flag)
            {
                p->right = new node(right);
                q.push(p->right);
            }
        }
    }

    void output() const
    {
        if (is_empty())
        {
            cout << "The tree is empty." << endl;
            return;
        }
        cout << "Pre-order: ";
        pre_order();
        cout << "In-order: ";
        in_order();
        cout << "Post-order: ";
        post_order();
        cout << "Level-order: ";
        level_order();
        cout << "node, left child, right child: " << endl;
        queue<node*> q;
        q.push(root);
        while (!q.empty())
        {
            node* p = q.front();
            q.pop();
            cout << p->data << ", ";
            if (p->left)
            {
                cout << p->left->data;
                q.push(p->left);
            }
            else cout << flag;
            cout << ", ";
            if (p->right)
            {
                cout << p->right->data;
                q.push(p->right);
            }
            else cout << flag;
            cout << endl;
        }
    }
};

/**
 * @brief Test function for binary_link_list
 * 
 * Example input:
 * 
 * [Initial tree input] A L C B E ~ D ~ ~ ~ ~ W ~ ~ X ~ ~
 * 
 * [Enter any 2 characters to find its left/right child] i j
 * 
 * [Delete left child of L, delete right child of C] L C
 */
void binary_link_list_test()
{
    binary_link_list<char> tree('~');
    cout << "Enter the binary tree of type 'char'(use '~' for null):" << endl;
    tree.input();
    tree.output();
    cout << "Tree size: " << tree.tree_size() << endl;
    cout << "Tree height: " << tree.tree_height() << endl;
    char tmp;
    cout << "Enter a character to find its left child: ";
    cin >> tmp;
    char leftChild = tree.left_child(tmp);
    if (leftChild != '~') cout << "Left child of " << tmp << " is: " << leftChild << endl;
    else cout << tmp << " has no left child." << endl;
    cout << "Enter a character to find its right child: ";
    cin >> tmp;
    char rightChild = tree.right_child(tmp);
    if (rightChild != '~') cout << "Right child of " << tmp << " is: " << rightChild << endl;
    else cout << tmp << " has no right child." << endl;
    cout << "Enter a character to delete its left child: ";
    cin >> tmp;
    tree.delete_left(tmp);
    cout << "After deleting left child of " << tmp << ", the tree is:" << endl;
    tree.output();
    cout << "Tree size: " << tree.tree_size() << endl;
    cout << "Tree height: " << tree.tree_height() << endl;
    cout << "Enter a character to delete its right child: ";
    cin >> tmp;
    tree.delete_right(tmp);
    cout << "After deleting right child of " << tmp << ", the tree is:" << endl;
    tree.output();
    cout << "Tree size: " << tree.tree_size() << endl;
    cout << "Tree height: " << tree.tree_height() << endl;
}

# endif