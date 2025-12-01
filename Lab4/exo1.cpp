#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

typedef TreeNode N;

int numberOfNodes(N *root) // O(n)
{
    if (root == nullptr)
        return 0;
    return 1 + numberOfNodes(root->left) + numberOfNodes(root->right);
}

int numberOfLeaves(N *root) // O(n)
{
    if (root == nullptr)
        return 0;
    if (root->left == nullptr and root->right == nullptr)
        return 1;
    return numberOfLeaves(root->left) + numberOfLeaves(root->right);
}

int numberOfFullNodes(N *root) // O(n)
{
    if (root == nullptr)
        return 0;
    return (root->left == nullptr or root->right == nullptr ? 0 : 1) + numberOfFullNodes(root->left) + numberOfFullNodes(root->right);
}

int depth(N *root) // O(n)
{
    if (root == nullptr)
        return 0;
    return 1 + max(depth(root->left), depth(root->right));
}

void preorder(N *root) // O(n)
{
    if (root == nullptr)
        return;
    cout << root->val;
    preorder(root->left);
    preorder(root->right);
}

void postorder(N *root) // O(n)
{
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val;
}


int main()
{
    N* tree1 = new N{1, nullptr, nullptr};
    N* tree2 = new N{2, new N{4, nullptr, nullptr}, new N{5, nullptr, nullptr}};
    N* tree3 = new N{3, new N{6, new N{7, nullptr, nullptr}, nullptr}, nullptr};

    cout << "Tree1 - Nodes: " << numberOfNodes(tree1) << ", Leaves: " << numberOfLeaves(tree1)
         << ", Full Nodes: " << numberOfFullNodes(tree1) << ", Depth: " << depth(tree1) << "\n";
    cout << "Preorder: ";
    preorder(tree1);
    cout << "\nPostorder: ";
    postorder(tree1);
    cout << "\n\n";

    cout << "Tree2 - Nodes: " << numberOfNodes(tree2) << ", Leaves: " << numberOfLeaves(tree2)
         << ", Full Nodes: " << numberOfFullNodes(tree2) << ", Depth: " << depth(tree2) << "\n";
    cout << "Preorder: ";
    preorder(tree2);
    cout << "\nPostorder: ";
    postorder(tree2);
    cout << "\n\n";

    cout << "Tree3 - Nodes: " << numberOfNodes(tree3) << ", Leaves: " << numberOfLeaves(tree3)
         << ", Full Nodes: " << numberOfFullNodes(tree3) << ", Depth: " << depth(tree3) << "\n";
    cout << "Preorder: ";
    preorder(tree3);
    cout << "\nPostorder: ";
    postorder(tree3);
    cout << "\n";

    delete tree1;
    delete tree2->left;
    delete tree2->right;
    delete tree2;
    delete tree3->left->left;
    delete tree3->left;
    delete tree3;

    return 0;
}