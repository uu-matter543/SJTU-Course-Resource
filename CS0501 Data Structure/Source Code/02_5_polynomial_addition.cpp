#include <iostream>

using namespace std;

class polynomial_node
{
private:
    int coef;
    int exp;
    polynomial_node *next;
public:
    polynomial_node(int c, int e, polynomial_node *n = nullptr) : coef(c), exp(e), next(n) {}
    ~polynomial_node() { delete next; }
    friend void print_polynomial(polynomial_node *p);
    friend polynomial_node* get_polynomial();
    friend polynomial_node* polynomials_addition(polynomial_node *p1, polynomial_node *p2);
};

void print_polynomial(polynomial_node *p)
{
    polynomial_node *temp = p->next;
    while (temp != nullptr)
    {
        cout << temp->coef << "x^" << temp->exp;
        if (temp->next != nullptr)
            cout << " + ";
        temp = temp->next;
    }
    cout << endl;
}

polynomial_node* get_polynomial()
{
    int n;
    cout << "Enter the number of terms in the polynomial: ";
    cin >> n;
    polynomial_node *head = new polynomial_node(0, 0);
    polynomial_node *temp = head;
    for (int i = 0; i < n; i++)
    {
        int coef, exp;
        cout << "Enter coefficient and exponent: ";
        cin >> coef >> exp;
        temp->next = new polynomial_node(coef, exp);
        temp = temp->next;
    }
    temp->next = nullptr;
    return head;
}

polynomial_node* polynomials_addition(polynomial_node *A, polynomial_node *B)
{
    polynomial_node *R = new polynomial_node(0, 0);
    polynomial_node *res = R;
    polynomial_node *a = A->next;
    polynomial_node *b = B->next;
    while(a != nullptr && b != nullptr)
    {
        if (a->exp == b->exp)
        {
            if (a->coef + b->coef != 0)
            {
                res->next = new polynomial_node(a->coef + b->coef, a->exp);
                res = res->next;
            }
            a = a->next;
            b = b->next;
        }
        else if (a->exp < b->exp)
        {
            res->next = new polynomial_node(a->coef, a->exp);
            a = a->next;
        }
        else if (a->exp > b->exp)
        {
            res->next = new polynomial_node(b->coef, b->exp);
            b = b->next;
        }
        if (res->next) res = res->next;
    }
    while (a != nullptr)
    {
        res->next = new polynomial_node(a->coef, a->exp);
        a = a->next;
        res = res->next;
    }
    while (b != nullptr)
    {
        res->next = new polynomial_node(b->coef, b->exp);
        b = b->next;
        res = res->next;
    }
    res->next = nullptr;
    return R;
}

void polynomial_addition_example()
{
    cout << "Enter the first polynomial (of exponents in increasing order):" << endl;
    polynomial_node *p1 = get_polynomial();
    cout << "Enter the second polynomial (of exponents in increasing order):" << endl;
    polynomial_node *p2 = get_polynomial();
    
    cout << "First polynomial: ";
    print_polynomial(p1);
    cout << "Second polynomial: ";
    print_polynomial(p2);
    
    polynomial_node *result = polynomials_addition(p1, p2);
    
    cout << "Resultant polynomial: ";
    print_polynomial(result);
    
    delete p1;
    delete p2;
    delete result;
}