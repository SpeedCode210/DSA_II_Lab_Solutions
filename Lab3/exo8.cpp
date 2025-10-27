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
Node *queue = nullptr;
Node *queue_tail = nullptr;

int front()
{
    if (sz == 0)
        throw new exception();
    return queue->val;
}

void pop()
{
    if (sz == 0)
        throw new exception();
    Node *s = queue;
    queue = queue->next;
    delete s;
    sz--;
    if(!sz) queue_tail = nullptr;
}

void push(int n)
{
    if (sz)
    {
        queue_tail->next = new Node(n, queue);
        queue_tail = queue_tail->next;
    }
    else
    {
        queue_tail = queue = new Node(n, nullptr);
    }
    sz++;
}

signed main()
{

    push(1);
    push(3);
    push(2);
    cout << front() << '\n';
    pop();
    cout << front() << '\n';
    pop();
    cout << front() << '\n';
    pop();

    while (sz)
    {
        Node *n = queue;
        queue = queue->next;
        delete n;
        sz--;
    }
}