#include <iostream>
using namespace std;

// Swapping 2 nodes of a singly-linked list

struct Node
{
    Node *next = nullptr;
    int val;

    Node(int val)
    {
        this->val = val;
    }
};

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

Node *swap_from(Node *node, Node *head)
{
    if (node == head)
    {
        if (head->next == nullptr)
            return head;
        Node *t = head->next->next;
        Node *s = head->next;
        head->next = t;
        s->next = head;
        return s;
    }
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->next == node and curr->next->next != nullptr)
        {
            Node *f = curr->next;
            Node *s = curr->next->next;
            Node *t = curr->next->next->next;
            curr->next = s;
            s->next = f;
            f->next = t;
            return head;
        }
        curr = curr->next;
    }

    return head;
}

int main()
{

    Node *b = new Node(14);
    b = push_front(b, 12);
    b = push_front(b, 10);
    b = push_front(b, 8);
    b = push_front(b, 6);
    Node *to_swap = b;
    b = push_front(b, 4);
    b = push_front(b, 2);
    b = push_front(b, 0);

    b = swap_from(to_swap, b);
    b = swap_from(b, b);
    print(b);

    del(b);
}