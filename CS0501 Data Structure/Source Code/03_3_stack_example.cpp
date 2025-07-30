#include <stack>
#include <iostream>

using namespace std;

void stack_example()
{
    stack<int> s;
    // push(), pop(), top()
    s.push(1);
    s.push(2);
    s.push(3);
    cout << "Stack top after pushing 1, 2, 3: ";
    cout << s.top() << endl;
    s.pop();
    cout << "Stack top after popping: ";
    cout << s.top() << endl;
    // empty()
    cout << "Is stack empty? " << (s.empty() ? "Yes" : "No") << endl;
    s.pop();
    s.pop();
    cout << "Is stack empty after popping all elements? " << (s.empty() ? "Yes" : "No") << endl;
}