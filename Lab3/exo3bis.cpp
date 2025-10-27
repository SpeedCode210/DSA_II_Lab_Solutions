#include <iostream>
using namespace std;

// Swapping 2 nodes of a doubly-linked list

struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
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

void print_rev(Node *tail)
{
    Node *curr = tail;
    for (int i = 0;; i++)
    {
        if (curr == nullptr)
        {
            cout << '\n';
            return;
        }
        cout << curr->val << ' ';
        curr = curr->prev;
    }
}

Node *push_front(Node *head, int x)
{
    Node *curr = new Node(x);
    curr->next = head;
    head->prev = curr;
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

Node *swap_from(Node *node1, Node *node2, Node *head)
{
    Node *node;
    if (node1->next == node2)
    {
        node = node1;
    }
    else if (node2->next == node1)
    {
        node = node2;
    }
    else
    {
        throw exception();
    }
    
    if (node == head)
    {
        if (head->next == nullptr)
            return head;
        Node *s = head->next;
        Node *t = head->next->next;
        head->next = t;
        s->next = head;
        t->prev = head;
        head->prev = s;
        s->prev = nullptr;
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
            s->prev = curr;
            f->prev = s;
            if(t != nullptr) t->prev = f;
            return head;
        }
        curr = curr->next;
    }

    return head;
}

int main()
{

    Node *b = new Node(14);
    Node* tail = b;
    b = push_front(b, 12);
    b = push_front(b, 10);
    b = push_front(b, 8);
    b = push_front(b, 6);
    Node *to_swap = b;
    b = push_front(b, 4);
    b = push_front(b, 2);
    b = push_front(b, 0);

    b = swap_from(to_swap, to_swap->next, b);
    b = swap_from(b, b->next, b);
    print(b);
    print_rev(tail);

    del(b);
}