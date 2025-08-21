#include <vector>
#include <list>
#include <iostream>

using namespace std;

void vector_example()
{
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Initial vector elements: ";
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " "; cout << endl;
    // size(), capacity(), max_size()
    cout << "Vector size: " << vec.size() << endl;
    cout << "Vector capacity: " << vec.capacity() << endl;
    cout << "Vector max size: " << vec.max_size() << endl;
    // front(), back(), at(), operator[]
    cout << "Vector front element: " << vec.front() << endl;
    cout << "Vector back element: " << vec.back() << endl;
    cout << "Vector at index 2 using 'at' function: " << vec.at(2) << endl;
    cout << "Vector at index 2 using operator[]: " << vec[2] << endl;
    // push_back(), pop_back()
    vec.push_back(6);
    cout << "Vector after push_back(6): ";
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " "; cout << endl;
    vec.pop_back();
    cout << "Vector after pop_back(): ";
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " "; cout << endl;
    // insert(), erase()
    vec.insert(vec.begin() + 2, 10);
    cout << "Vector after insert(10) at index 2: ";
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " "; cout << endl;
    vec.erase(vec.begin() + 2);
    cout << "Vector after erase() at index 2: ";
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " "; cout << endl;
    // reserve()
    vec.reserve(10);
    cout << "Vector capacity after reserve(10): " << vec.capacity() << endl;
    // itrators and const_itrators
    vector<int>::iterator it;
    vector<int>::const_iterator c_it;
    it = vec.begin();
    cout << "Let iterator point to front: " << *it << endl;
    it++;
    cout << "Let iterator point to next element: " << *it << endl;
    it--;
    cout << "Let iterator point to previous element: " << *it << endl;
    it = vec.end() - 1;
    cout << "Let iterator point to back: " << *it << endl;
    c_it = vec.cbegin();
    cout << "Let const_iterator point to front: " << *c_it << endl;
    cout << "Are const_iterator and iterator same? " << (it == c_it ? "Yes" : "No") << endl;
    cout << "Are const_iterator and iterator different? " << (it != c_it ? "Yes" : "No") << endl;
    // clear(), empty()
    cout << "Is vector empty? " << (vec.empty() ? "Yes" : "No") << endl;
    vec.clear();
    cout << "Is vector empty after clear()? " << (vec.empty() ? "Yes" : "No") << endl;
}

void list_example()
{
    list<int> lst = {1, 2, 3, 4, 5};
    cout << "Initial list elements: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    // size(), max_size()
    cout << "List size: " << lst.size() << endl;
    cout << "List max size: " << lst.max_size() << endl;
    // front(), back()
    cout << "List front element: " << lst.front() << endl;
    cout << "List back element: " << lst.back() << endl;
    // push_front(), push_back()
    lst.push_front(0);
    cout << "List after push_front(0): ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    lst.push_back(6);
    cout << "List after push_back(6): ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    // pop_front(), pop_back()
    lst.pop_front();
    cout << "List after pop_front(): ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    lst.pop_back();
    cout << "List after pop_back(): ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    // insert(), erase()
    list<int>::iterator it;
    it = lst.begin();
    advance(it, 2);
    lst.insert(it, 10);
    cout << "List after insert(10) at index 2: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    it = lst.begin();
    advance(it, 2);
    lst.erase(it);
    cout << "List after erase() at index 2: ";
    for (auto it = lst.begin(); it != lst.end(); ++it) cout << *it << " "; cout << endl;
    // clear(), empty()
    cout << "Is list empty? " << (lst.empty() ? "Yes" : "No") << endl;
    lst.clear();
    cout << "Is list empty after clear()? " << (lst.empty() ? "Yes" : "No") << endl;
}

int main()
{
    cout << "Vector Example:" << endl;
    vector_example();
    cout << endl;
    cout << "List Example:" << endl;
    list_example();
    return 0;
}