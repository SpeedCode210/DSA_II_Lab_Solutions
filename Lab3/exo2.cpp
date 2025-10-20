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

class List
{
private:
    Node *head;

public:
    List()
    {
        head = new Node(-1);
    }

    ~List()
    {
        Node *curr = head;
        while (curr != nullptr)
        {
            Node *h = curr;
            curr = curr->next;
            delete h;
        }
    }

    int size() // O(n)
    {
        Node *curr = head;
        for (int i = 0;; i++)
        {
            curr = curr->next;

            if (curr == nullptr)
                return i;
        }
    }

    void print() // O(n)
    {
        Node *curr = head;
        for (int i = 0;; i++)
        {
            curr = curr->next;

            if (curr == nullptr)
            {
                cout << '\n';
                return;
            }

            cout << curr->val << ' ';
        }
    }

    bool exists(int x) // O(n)
    {
        Node *curr = head;
        for (int i = 0;; i++)
        {
            curr = curr->next;

            if (curr == nullptr)
            {
                return false;
            }

            if (curr->val == x)
                return true;
        }
    }

    void push_front(int x) // O(1)
    {
        Node *curr = new Node(x);
        curr->next = head->next;
        head->next = curr;
    }

    void push_back(int x) // O(n)
    {
        Node *curr = head;
        for (int i = 0;; i++)
        {

            if (curr->next == nullptr)
            {
                curr->next = new Node(x);
                return;
            }

            curr = curr->next;
        }
    }

    void remove_first(int x) // O(n)
    {
        Node *curr = head;
        for (int i = 0;; i++)
        {
            if (curr->next == nullptr)
            {
                return;
            }

            if (curr->next->val == x)
            {
                Node *h = curr->next;
                curr->next = h->next;
                delete h;
                return;
            }

            curr = curr->next;
        }
    }
};

int main()
{
    List list;

    list.push_front(5);
    list.push_front(4);
    list.push_front(3);
    list.print();
    list.push_front(2);
    list.push_front(1);
    list.print();
    list.push_back(6);
    list.push_front(0);
    list.print();
    cout << list.exists(5) << '\n';
    cout << list.exists(7) << '\n';
    list.remove_first(4);
    list.print();
    cout << list.size() << '\n';
}