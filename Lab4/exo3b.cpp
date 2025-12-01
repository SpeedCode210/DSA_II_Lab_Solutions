#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

struct ListNode{
    int val;
    ListNode* next;
};

typedef ListNode L;
typedef TreeNode N;

L* flattenBst(N* root, L* stack = nullptr){
    if(root == nullptr) return stack;

    stack = flattenBst(root->left, stack);
    stack = new L{root->val, stack};
    stack = flattenBst(root->right, stack);
    return stack;
}


N *createNode(int val)
{
    return new N{val, nullptr, nullptr};
}

bool validate(N *root)
{
    L* stack = flattenBst(root);

    while(stack && stack->next){
        if (stack->next->val >= stack->val) return false;
        stack = stack->next;
    }
    return true;
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