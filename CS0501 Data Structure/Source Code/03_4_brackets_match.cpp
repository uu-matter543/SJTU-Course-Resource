#include <iostream>
#include <stack>
#include <string>

using namespace std;

void checkBrackets(const string& expression)
{
    stack<char> s;
    for (char ch : expression)
    {
        if (ch == '(' || ch == '{' || ch == '[') s.push(ch);
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (s.empty())
            {
                cout << "Unmatched closing bracket: " << ch << endl;
                return;
            }
            char top = s.top();
            s.pop();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '['))
            {
                cout << "Mismatched brackets: " << top << " and " << ch << endl;
                return;
            }
        }
    }
    if (!s.empty()) cout << "Unmatched opening bracket: " << s.top() << endl;
    else cout << "All brackets are matched." << endl;
}

void brackets_match_example()
{
    string expression;
    cout << "Enter an expression with brackets: ";
    getline(cin, expression);
    checkBrackets(expression);
}