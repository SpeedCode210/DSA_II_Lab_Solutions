#include <iostream>
typedef long long ll;
using namespace std;

struct Node
{
    Node *next = nullptr;
    char val;

    Node(char v, Node *n = nullptr)
    {
        val = v;
        next = n;
    }
};

Node *queue = new Node('d');
int sz = 0;

signed main()
{
    string s;
    cout << "Enter your string : ";
    cin >> s;
    bool good = true;
    for (auto &c : s)
    {
        if (!good)
            break;

        switch (c)
        {
        case ')':
            if (sz == 0 or queue->val != '(')
            {
                good = false;
            }
            else
            {
                Node *n = queue;
                queue = queue->next;
                delete n;
                sz--;
            }
            break;
        case ']':
            if (sz == 0 or queue->val != '[')
            {
                good = false;
            }
            else
            {
                Node *n = queue;
                queue = queue->next;
                delete n;
                sz--;
            }
            break;

        default:
            if (c != '(' and c != '['){
                good = false;
                break;
            }
            Node *n = new Node(c, queue);            
            queue = n;
            sz++;
            break;
        }
    }

    good &= sz == 0;

    while(queue != nullptr){
        Node *n = queue;
        queue = queue->next;
        delete n;
    }

    cout << (good ? "Good string\n" : "Bad string\n");

    
}