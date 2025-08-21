#include <stack>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

string in_to_suf_form(string str)
{
    int i = 0;
    stack<char> s;
    string result;
    while (str[i] != '\0')
    {
        if ('0' <= str[i] && str[i] <='9')
        {
            string num = "";
            while ('0' <= str[i] && str[i] <= '9')
            {
                num += str[i];
                i++;
            }
            result += num + " ";
        }
        else if (str[i] == '(')
        {
            s.push(str[i]);
            i++;
        }
        else if (str[i] == ')')
        {
            while(!s.empty() && s.top() != '(')
            {
                result += s.top();
                result += " ";
                s.pop();
            }
            if (!s.empty() && s.top() == '(') s.pop();
            i++;
        }
        else if (str[i] == '*' || str[i] == '/')
        {
            while (!s.empty() && (s.top() == '*' || s.top() == '/'))
            {
                result += s.top();
                result += " ";
                s.pop();
            }
            s.push(str[i]);
            i++;
        }
        else if (str[i] == '+' || str[i] == '-')
        {
            while (!s.empty() && (s.top() == '*' || s.top() == '/' || s.top() == '+' || s.top() == '-'))
            {
                result += s.top();
                result += " ";
                s.pop();
            }
            s.push(str[i]);
            i++;
        }
        else i++;
    }
    while (!s.empty())
    {
        result += s.top();
        result += " ";
        s.pop();
    }
    return result;
}

int calc_post(string str)
{
    int i = 0;
    stack<int> s;
    while (str[i] != '\0')
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            int num = 0;
            while ('0' <= str[i] && str[i] <= '9')
            {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            s.push(num);
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            int res;
            switch (str[i])
            {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/':
                    if (b == 0)
                    {
                        cout << "Error: Division by zero." << endl;
                        return INT_MAX;
                    }
                    res = a / b; break;
            }
            s.push(res);
            i++;
        }
        else i++;
    }
    if (s.empty())
    {
        cout << "Error: No result found." << endl;
        return INT_MAX;
    }
    int result = s.top();
    s.pop();
    if (!s.empty())
    {
        cout << "Error: Extra values in stack." << endl;
        return INT_MAX;
    }
    return result;
}

int main()
{
    string expression;
    cout << "Enter an infix expression: " << endl;
    getline(cin, expression);
    string suf_form = in_to_suf_form(expression);
    cout << "Infix Expression: " << expression << endl;
    cout << "Postfix Expression: " << suf_form << endl;
    int result = calc_post(suf_form);
    if (result != INT_MAX) cout << "Result: " << result << endl;
    else cout << "Calculation failed." << endl;
    return 0;
}