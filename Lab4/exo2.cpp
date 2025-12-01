#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

typedef TreeNode N;

N *removeLeaves(N *root)
{
    if (root == nullptr or (root->left == nullptr and root->right == nullptr))
        return nullptr;
    root->left = removeLeaves(root->left);
    root->right = removeLeaves(root->right);
    return root;
}

void preorder(N *root)
{
    if (root == nullptr)
        return;
    cout << root->val;
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    N *tree2 = new N{2, new N{4, nullptr, nullptr}, new N{5, nullptr, nullptr}};

    preorder(tree2);
    cout << '\n';
    tree2 = removeLeaves(tree2);
    preorder(tree2);
    cout << '\n';
}