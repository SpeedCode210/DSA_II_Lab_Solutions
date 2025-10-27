#include <iostream>
typedef long long ll;
using namespace std;

int sz = 0;

struct Node
{
    Node *next = nullptr;
    int val;

    Node(int v, Node *n = nullptr)
    {
        val = v;
        next = n;
    }
};
Node *stack = nullptr;

int top()
{
    if (sz == 0)
        throw new exception();
    return stack->val;
}

void pop()
{
    if (sz == 0)
        throw new exception();
    Node *s = stack;
    stack = stack->next;
    delete s;
    sz--;
}

void push(int n)
{
    stack = new Node(n, stack);
    sz++;
}

signed main()
{

    push(1);
    push(3);
    push(2);
    cout << top() << '\n';
    pop();
    cout << top() << '\n';
    pop();
    cout << top() << '\n';
    pop();

    while (sz)
    {
        Node *n = stack;
        stack = stack->next;
        delete n;
        sz--;
    }
}