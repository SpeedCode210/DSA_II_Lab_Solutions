#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

typedef TreeNode N;

N *generate_method1(int n)
{
    int arr[n];

    for (int i = 0; i < n; i++)
        arr[i] = i + 1;

    for (int i = 0; i < n; i++)
    {
        int a = rand() % n;
        int b = rand() % n;
        swap(arr[a], arr[b]);
    }

    N *root = new N{arr[0], nullptr, nullptr};

    for (int i = 1; i < n; i++)
    {
        N *curr = root;
        while (true)
        {
            if (arr[i] < curr->val)
            {
                if (curr->left == nullptr)
                {
                    curr->left = new N{arr[i], nullptr, nullptr};
                    break;
                }
                curr = curr->left;
            }
            else
            {
                if (curr->right == nullptr)
                {
                    curr->right = new N{arr[i], nullptr, nullptr};
                    break;
                }
                curr = curr->right;
            }
        }
    }

    return root;
}

N *generate_method2(int lb, int ub)
{
    if (lb == ub)
        return new N{lb, nullptr, nullptr};
    if (lb > ub)
        return nullptr;

    int key = rand() % (ub - lb);

    return new N{lb + key, generate_method2(lb, lb + key - 1), generate_method2(lb + key + 1, ub)};
}

void preorder(N *root)
{
    if (root == nullptr)
        return;
    cout << root->val;
    preorder(root->left);
    preorder(root->right);
}

void printTree(N *root, int space = 0)
{
    if (root == nullptr)
    {
        space += 1;

        for (int i = 1; i < space; i++)
            cout << "  |";
        if (space > 1)
            cout << "__";
        cout << "*" << "\n";

        return;
    }

    space += 1;

    for (int i = 1; i < space; i++)
        cout << "  |";
    if (space > 1)
        cout << "__";
    cout << root->val << "\n";

    printTree(root->left, space);

    printTree(root->right, space);
}

int main()
{
    srand(time(0));

    N *test = generate_method1(14); // O(N)

    printTree(test);
}