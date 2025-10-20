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

Node *insert(Node *list_tail, int val)
{
    list_tail->next = new Node(val);
    return list_tail->next;
}

int main()
{
    Node *headL;
    Node *tailL;
    Node *headP;
    Node *tailP;

    tailL = headL = new Node(0);
    for (int i = 1; i < 100; i++)
        tailL = insert(tailL, i);

    tailP = headP = new Node(1);

    tailP = insert(tailP, 3);
    tailP = insert(tailP, 4);
    tailP = insert(tailP, 6);

    int j = 0;
    for (Node *l = headL, *p = headP; p != nullptr and l != nullptr; l = l->next)
    {
        if (p->val == j)
        {
            cout << l->val << '\n';
            p = p->next;
        }

        j++;
    }

    Node *curr = headL;
    while (curr != nullptr)
    {
        Node *h = curr;
        curr = curr->next;
        delete h;
    }

    curr = headP;
    while (curr != nullptr)
    {
        Node *h = curr;
        curr = curr->next;
        delete h;
    }
}

// Time Complexity : O(n)