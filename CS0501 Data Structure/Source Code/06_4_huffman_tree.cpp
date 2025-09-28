#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class huffman_tree
{
private:
    struct h_node
    {
        char data;
        int freq;
        h_node *left;
        h_node *right;

        h_node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
        h_node(h_node* l, h_node* r) : data('\0'), freq(l->freq + r->freq), left(l), right(r) {}
        ~h_node() {
            if (left) delete left;
            if (right) delete right;
        }
    };
    h_node *root;
    vector<char> data;
    vector<string> code;

public:
    huffman_tree() : root(nullptr) {}

    ~huffman_tree()
    {
        delete root;
    }

    void build_tree(const string &data, const vector<int> &freq)
    {
        int tmp=data.size();
        vector<h_node*> nodes;
        for (int i = 0; i < tmp; ++i) nodes.push_back(new h_node(data[i], freq[i]));
        while (nodes.size() > 1)
        {
            int size = nodes.size();
            h_node *min1 = nullptr, *min2 = nullptr;
            int pos1 = -1, pos2 = -1;
            for (int i=0; i<size; i++)
            {
                if (min1 == nullptr || nodes[i]->freq < min1->freq)
                {
                    min2 = min1;
                    pos2 = pos1;
                    min1 = nodes[i];
                    pos1 = i;
                }
                else if (min2 == nullptr || nodes[i]->freq < min2->freq)
                {
                    min2 = nodes[i];
                    pos2 = i;
                }
            }
            h_node *new_node = new h_node(min1, min2);
            nodes.erase(nodes.begin()+pos1);
            nodes.erase(nodes.begin()+pos2-(pos2>pos1));
            nodes.push_back(new_node);
        }
        root = nodes[0];
    }

    void generate_codes()
    {
        data.clear();
        code.clear();
        queue<h_node*> q;
        q.push(root);
        queue<string> str;
        str.push("");
        while(!q.empty())
        {
            h_node* cur_node = q.front();
            q.pop();
            string cur_str = str.front();
            str.pop();
            if (cur_node->left)
            {
                q.push(cur_node->left);
                str.push(cur_str+"0");
            }
            if (cur_node->right)
            {
                q.push(cur_node->right);
                str.push(cur_str+"1");
            }
            if (cur_node->data!='\0')
            {
                data.push_back(cur_node->data);
                code.push_back(cur_str);
            }
        }
    }

    void display_codes()
    {
        int size = data.size();
        for (int i=0; i<size; i++) cout << "The Huffman code of character \"" << data[i] << "\" is: " << code[i] << endl;
    }
};

int main()
{
    huffman_tree tree;
    int n;
    string str;
    int tmp;
    vector<int> freq;
    cout << "Please enter the number of characters: ";
    cin >> n;
    char placeholder;
    cin.get(placeholder);
    cout << "Please enter the characters in a string: ";
    getline(cin,str);
    while (str.length()!=n)
    {
        cout << "The number of characters does not matches with the length of string. Please try again: ";
        getline(cin,str);
    }
    cout << "Please enter the frequency of each character: ";
    for(int i=0; i<n; i++)
    {
        cin >> tmp;
        freq.push_back(tmp);
    }

    tree.build_tree(str, freq);
    tree.generate_codes();
    tree.display_codes();
    return 0;
}
