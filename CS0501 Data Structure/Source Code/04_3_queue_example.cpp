#include <queue>
#include <iostream>

using namespace std;

void queue_example()
{
    queue<int> q;
    // push(), pop(), front(), back()
    q.push(1);
    q.push(2);
    q.push(3);
    cout << "Queue front after pushing 1, 2, 3: ";
    cout << q.front() << endl;
    cout << "Queue back after pushing 1, 2, 3: ";
    cout << q.back() << endl;
    q.pop();
    cout << "Queue front after popping: ";
    cout << q.front() << endl;
    cout << "Queue back after popping: ";
    cout << q.back() << endl;
    // size()
    cout << "Queue size: " << q.size() << endl;
    // empty()
    cout << "Is queue empty? " << (q.empty() ? "Yes" : "No") << endl;
}

int main()
{
    queue_example();
    return 0;
}