#include <queue>
#include <iostream>
#include <vector>

using namespace std;

void carriage_rearrange(int a[], int n, int size) {
    queue<int> q;
    for (int i = 0; i < n; i++) q.push(a[i]);

    vector<queue<int>> buffer(size);

    while(!q.empty())
    {
        int available = -1, max = 0;
        int in = q.front(); q.pop();
        for (int i = 0; i < size; i++)
        {
            if (buffer[i].empty()) { 
                if (available == -1) available = i;
            }
            else if (buffer[i].back() < in) 
                if (buffer[i].back() < in && buffer[i].size() > max) {
                    max = buffer[i].back();
                    available = i;
                }
        }
        if (available == -1) {
            cout << "No available buffer found." << endl;
            return;
        }
        buffer[available].push(in);
        cout << "Carriage " << in << " added to buffer " << available + 1 << endl;
    }
    cout << "Carriages rearranged successfully." << endl;
}

void carriage_rearrange_example() {
    int n;
    cout << "Enter the number of carriages: ";
    cin >> n;
    int a[n];
    cout << "Enter the carriages: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int k;
    cout << "Enter the number of buffers: ";
    cin >> k;
    carriage_rearrange(a, n, k);
}
