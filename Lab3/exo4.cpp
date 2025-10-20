#include <iostream>
using namespace std;

struct Node
{
    Node *next = nullptr;
    int val;

    Node(int val)
    {
        this->val = val;
    }
};

Node *intersect(Node *a, Node *b)
{
    Node *res = new Node(0);
    Node *curr = res;
    while (a != nullptr and b != nullptr)
    {
        if (a->val == b->val)
        {
            curr->next = new Node(a->val);
            curr = curr->next;
            int v = a-> val;
            a = a->next;
            b = b->next;
            while(a != nullptr and a->val == v) a = a->next; // Avoid repetition
        }
        else if (a->val < b->val)
        {
            a = a->next;
        }
        else
        {
            b = b->next;
        }
    }

    Node *h = res;
    res = res->next;
    delete h;
    return res;
}

void print(Node *head)
{
    Node *curr = head;
    for (int i = 0;; i++)
    {
        if (curr == nullptr)
        {
            cout << '\n';
            return;
        }
        cout << curr->val << ' ';
        curr = curr->next;
    }
}

Node *push_front(Node *head, int x)
{
    Node *curr = new Node(x);
    curr->next = head;
    return curr;
}

void del(Node *head)
{
    Node *curr = head;
    while (curr != nullptr)
    {
        Node *h = curr;
        curr = curr->next;
        delete h;
    }
}

int main()
{
    Node *a = new Node(15);
    a = push_front(a, 12);
    a = push_front(a, 9);
    a = push_front(a, 6);
    a = push_front(a, 3);
    a = push_front(a, 0);

    Node *b = new Node(14);
    b = push_front(b, 12);
    b = push_front(b, 10);
    b = push_front(b, 10);
    b = push_front(b, 8);
    b = push_front(b, 6);
    b = push_front(b, 4);
    b = push_front(b, 2);
    b = push_front(b, 0);

    Node *c = intersect(a, b);
    cout << c << '\n';
    print(c);

    del(a);
    del(b);
    del(c);
}