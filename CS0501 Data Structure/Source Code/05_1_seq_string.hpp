#ifndef seq_string_h
#define seq_string_h

#include <iostream>

using namespace std;

class seq_string{
private:
    char* str = nullptr;
    int len = 0;

public:
    seq_string(const char* s = "")
    { 
        len = 0;
        while (s[len] != '\0') len++;
        str = new char[len + 1];
        for (int i = 0; i < len; i++) str[i] = s[i];
        str[len] = '\0';
    }

    seq_string(const seq_string &other)
    {
        len = other.len;
        str = new char[len + 1];
        for (int i = 0; i <= len; i++) str[i] = other.str[i];
    }

    ~seq_string()
    {
        delete[] str;
    }

    int length() const
    {
        return len;
    }

    seq_string substr(int start, int num) const
    {
        if(start < 0 || start > len) return "";
        seq_string sub;
        sub.len = (start + num > len) ? len - start : num;
        delete[] sub.str;
        sub.str = new char[sub.len + 1];
        for (int i = 0; i < sub.len; i++) sub.str[i] = str[start + i];
        sub.str[sub.len] = '\0';
        return sub;
    }

    void insert(int pos, const seq_string &s)
    {
        char *tmp = str;
        int i;
        if (pos < 0 || pos > len) return;
        len += s.len;
        str = new char[len + 1];
        for (i = 0; i < pos; i++) str[i] = tmp[i];
        for (i = 0; i < s.len; i++) str[pos + i] = s.str[i];
        for (i = pos; i < len - s.len; i++) str[i + s.len] = tmp[i];
        str[len] = '\0';
        delete tmp;
    }

    void remove(int pos, int count)
    {
        if (pos < 0 || pos > len) return;
        if (pos + count > len)
        {
            str[pos] = '\0';
            len = pos;
        }
        else
        {
            for (len = pos; str[len + count] != '\0'; len++) str[len] = str[len + count];
            str[len] = '\0';
        }
    }

    friend bool operator==(const seq_string &s1, const seq_string &s2)
    {
        if (s1.len != s2.len) return false;
        for (int i = 0; i < s1.len; i++) if (s1.str[i] != s2.str[i]) return false;
        return true;
    }

    friend bool operator!=(const seq_string &s1, const seq_string &s2)
    {
        return !(s1 == s2);
    }

    friend bool operator>(const seq_string &s1, const seq_string &s2)
    {
        for (int i = 0; i < s1.len; i++)
        {
            if (s1.str[i] > s2.str[i]) return true;
            if (s1.str[i] < s2.str[i]) return false;
        }
        return false;
    }

    friend bool operator<(const seq_string &s1, const seq_string &s2)
    {
        return !(s1 > s2) && (s1 != s2);
    }

    friend bool operator>=(const seq_string &s1, const seq_string &s2)
    {
        return !(s1 < s2);
    }

    friend bool operator<=(const seq_string &s1, const seq_string &s2)
    {
        return !(s1 > s2);
    }

    friend ostream& operator<<(ostream &os, const seq_string &s)
    {
        os << s.str;
        return os;
    }

    friend seq_string operator+(const seq_string &s1, const seq_string &s2)
    {
        seq_string result;
        result.len = s1.len + s2.len;
        result.str = new char[result.len + 1];
        for (int i = 0; i < s1.len; i++) result.str[i] = s1.str[i];
        for (int i = 0; i < s2.len; i++) result.str[s1.len + i] = s2.str[i];
        result.str[result.len] = '\0';
        return result;
    }
};

void seq_string_test()
{
    seq_string s1("Hello");
    seq_string s2("World");
    seq_string s3 = s1 + s2;
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    seq_string tmp(", ");
    s1.insert(5, tmp);
    s1.insert(7, s2);
    cout << "After insert: " << s1 << endl;
    s1.remove(5, 1);
    cout << "After remove: " << s1 << endl;
    cout << "s3 (s1 + s2): " << s3 << endl;
    cout << "s1 length: " << s1.length() << endl;
    cout << "s2 length: " << s2.length() << endl;
    cout << "s3 length: " << s3.length() << endl;
    cout << "s1 == s2: " << (s1 == s2 ? "True" : "False") << endl;
    cout << "s1 != s2: " << (s1 != s2 ? "True" : "False") << endl;
    cout << "s1 > s2: " << (s1 > s2 ? "True" : "False") << endl;
    cout << "s1 < s2: " << (s1 < s2 ? "True" : "False") << endl;
    cout << "s1 >= s2: " << (s1 >= s2 ? "True" : "False") << endl;
    cout << "s1 <= s2: " << (s1 <= s2 ? "True" : "False") << endl;
    seq_string sub = s1.substr(2, 7);
    cout << "Substring of s1: " << sub << endl;
    seq_string s4(s1);
    cout << "s4 (copy of s1): " << s4 << endl;
    cout << "s4 length: " << s4.length() << endl;
}

#endif
