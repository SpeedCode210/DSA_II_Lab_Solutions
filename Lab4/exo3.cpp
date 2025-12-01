#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    int min;
    int max;
};

typedef TreeNode N;

bool validate(N *root)
{
    if (root == nullptr)
        return true;

    if (!validate(root->right) or !validate(root->left))
        return false;

    if (root->right && root->right->min <= root->val)
        return false;
    if (root->left && root->left->max >= root->val)
        return false;

    root->min = root->max = root->val;
    if (root->left != nullptr)
    {
        root->min = min(root->left->min, root->min);
        root->max = max(root->left->max, root->max);
    }

    if (root->right != nullptr)
    {
        root->min = min(root->right->min, root->min);
        root->max = max(root->right->max, root->max);
    }

    return true;
}

N *createNode(int val)
{
    return new N{val, nullptr, nullptr};
}

int main()
{
    // BST with 7 nodes
    N *bst = createNode(10);
    bst->left = createNode(5);
    bst->right = createNode(15);
    bst->left->left = createNode(2);
    bst->left->right = createNode(7);
    bst->right->left = createNode(13);
    bst->right->right = createNode(17);

    // Non-BST with 6 nodes
    N *non_bst = createNode(10);
    non_bst->left = createNode(12); // breaks BST property here
    non_bst->right = createNode(15);
    non_bst->left->left = createNode(9);
    non_bst->left->right = createNode(8);
    non_bst->right->right = createNode(16);

    cout << validate(bst) << validate(non_bst) << '\n'; // should output 10

    //teacher example
    cout << validate(new N{7, new N{4, new N{2}, new N{3}}, new N{9, new N{1}, new N{10}}}) << '\n'; //should be 0 
}