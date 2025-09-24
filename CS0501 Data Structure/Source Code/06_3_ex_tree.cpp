#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ex_tree{
private:
    struct ex_node {
        string token;
        ex_node *left;
        ex_node *right;
        ex_node(string t) : token(t), left(nullptr), right(nullptr) {}
        ex_node() : token(""), left(nullptr), right(nullptr) {}
    };
    ex_node *root = nullptr;

public:
    ex_tree() : root(nullptr) {}
    ~ex_tree()
    {
        delete_node(root);
    }

    void delete_node(ex_node *node)
    {
        if (node) {
            delete_node(node->left);
            delete_node(node->right);
            delete node;
        }
    }

    ex_node* create_tree(vector<string> tokens)
    {
        ex_node *tmp_root = nullptr;
        ex_node *current = nullptr;
        ex_node *tmp_node = nullptr;
        int tmp = tokens.size();
        if (tmp == 0) {
            tmp_root = nullptr;
            return nullptr;
        }
        for (int i=0; i<tmp; i++)
        {
            if (tokens[i] == "(")
            {
                int j=i+1;
                int count=1;
                while (count > 0)
                {
                    if (tokens[j] == "(") count++;
                    if (tokens[j] == ")") count--;
                    j++;
                }
                tmp_node = create_tree(vector<string>(tokens.begin() + i + 1, tokens.begin() + j - 1));
                i = j-1;
                if (!tmp_root)
                {
                    tmp_root = new ex_node(tokens[++i]);
                    tmp_root->left = tmp_node;
                }
                else
                {
                    current = tmp_root;
                    while (current->right) current = current->right;
                    current->right = tmp_node;
                }
            }
            else if (tokens[i] == "*" || tokens[i] == "/")
            {
                if (tmp_root->token == "*" || tmp_root->token == "/")
                {
                    tmp_node = new ex_node(tokens[i]);
                    tmp_node->left = tmp_root;
                    tmp_root = tmp_node;
                }
                else if (tmp_root->token == "+" || tmp_root->token == "-")
                {
                    tmp_node = new ex_node(tokens[i]);
                    tmp_node->left = tmp_root->right;
                    tmp_root->right = tmp_node;
                }
                else
                {
                    tmp_node = new ex_node(tokens[i]);
                    tmp_node->left = tmp_root;
                    tmp_root = tmp_node;
                }
            }
            else if (tokens[i] == "+" || tokens[i] == "-")
            {
                tmp_node = new ex_node(tokens[i]);
                tmp_node->left = tmp_root;
                tmp_root = tmp_node;
            }
            else
            {
                tmp_node = new ex_node(tokens[i]);
                if (!tmp_root)
                {
                    tmp_node->left = tmp_root;
                    tmp_root = tmp_node;
                }
                else
                {
                    current = tmp_root;
                    while (current->right) current = current->right;
                    current->right = tmp_node;
                }
            }
        }
        return tmp_root;
    }

    void set_root(vector<string> tokens)
    {
        root = create_tree(tokens);
    }

    int calc(ex_node* t)
    {
        switch (t->token[0])
        {
            case '+':
                return calc(t->left)+calc(t->right);
            case '-':
                return calc(t->left)-calc(t->right);
            case '*':
                return calc(t->left)*calc(t->right);
            case '/':
                return calc(t->left)/calc(t->right);
            default:
                return stoi(t->token);
        }
        return INT_MIN;
    }

    int result()
    {
        return calc(root);
    }
};

vector<string> tokenize(string expression)
{
    int n = expression.size();
    vector<string> tokens;
    string current_token;
    for (int i=0; i<n; i++)
    {
        current_token = "";
        if (expression[i] == '(' || expression[i] == ')' || expression[i] == '+' || 
            expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
        {
            current_token += expression[i];
            tokens.push_back(current_token);
        }
        else
        {
            while (i<n && expression[i] >= '0' && expression[i] <= '9')
            {
                current_token += expression[i];
                i++;
            }
            tokens.push_back(current_token);
            i--;
        }
    }
    return tokens;
}

int main()
{
    string expression;
    cout << "Enter an expression: " << endl;
    cout << "(Please ensure the divisor divides the dividend, i.e. the remainder is 0)" << endl;
    cout << "(Please do not enter unnecessary brackets, e.g. brackets including the whole expression)" << endl;
    getline(cin, expression);
    vector<string> tokens = tokenize(expression);
    
    ex_tree tree;
    tree.set_root(tokens);
    cout << "The result is: " << tree.result();
    return 0;
}