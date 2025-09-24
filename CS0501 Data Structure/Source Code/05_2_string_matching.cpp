#include <string>
#include <iostream>

using namespace std;

int bf_match(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    
    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++) if (text[i + j] != pattern[j]) break;
        if (j == m) return i;
    }
    return -1;
}

void next_array(const string &pattern, int next[]) {
    int m = pattern.size();
    next[0] = -1;
    int j = -1;

    for (int i = 1; i < m; i++)
    {
        while (j >= 0 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) j++;
        next[i] = j;
    }
}

int kmp_match(const string &text, const string &pattern) {
    int n = text.size();
    int m = pattern.size();
    int next[m];
    next_array(pattern, next);
    
    int j = -1;
    for (int i = 0; i < n; i++)
    {
        while (j >= 0 && pattern[j + 1] != text[i]) j = next[j];
        if (pattern[j + 1] == text[i]) j++;
        if (j == m - 1) return i - m + 1;
    }
    return -1;
}

int main()
{
    cout << "Enter text: ";
    string text;
    getline(cin, text);
    cout << "Enter pattern: ";
    string pattern;
    getline(cin, pattern);

    int bf_result = bf_match(text, pattern);
    int kmp_result = kmp_match(text, pattern);

    cout << "Brute Force Match Index: " << bf_result << endl;
    cout << "KMP Match Index: " << kmp_result << endl;
    return 0;
}