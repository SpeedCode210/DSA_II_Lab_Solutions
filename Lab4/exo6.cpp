#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    int height = 1;
    int weight = 0;
};

#pragma region stack
int sz = 0;

struct Node
{
    Node *next = nullptr;
    TreeNode *val;

    Node(TreeNode *v, Node *n = nullptr)
    {
        val = v;
        next = n;
    }
};
Node *stack = nullptr;

TreeNode *top()
{
    if (sz == 0)
        throw new exception();
    return stack->val;
}

void pop()
{
    if (sz == 0)
        throw new exception();
    Node *s = stack;
    stack = stack->next;
    delete s;
    sz--;
}

void push(TreeNode *n)
{
    stack = new Node(n, stack);
    sz++;
}
#pragma endregion

int h(TreeNode *n)
{
    return n == nullptr ? 0 : n->height;
}

void compute_stats(TreeNode *n)
{
    n->height = max(h(n->left), h(n->right)) + 1;
    n->weight = h(n->left) - h(n->right);
}

void left_to_right_rotation(TreeNode *n)
{
    auto a = n->left;
    auto b = n;
    auto A = a->left;
    auto B = a->right;
    auto C = b->right;

    swap(a->val, b->val);

    b->left = A;
    b->right = a;
    a->left = B;
    a->right = C;

    compute_stats(a);
    compute_stats(b);
}

void right_to_left_rotation(TreeNode *n)
{
    auto a = n->right;
    auto b = n;
    auto A = a->left;
    auto B = a->right;
    auto C = b->left;

    swap(a->val, b->val);

    b->left = a;
    b->right = B;
    a->left = C;
    a->right = A;

    compute_stats(a);
    compute_stats(b);
}

TreeNode *insert(TreeNode *root, int val)
{
    if (root == nullptr)
        return new TreeNode{val, nullptr, nullptr, 1, 0};
    TreeNode *newNode = new TreeNode{val, nullptr, nullptr, 1, 0};
    push(root);
    while (true)
    {
        if (val < top()->val)
        {
            if (top()->left == nullptr)
            {
                top()->left = newNode;
                push(newNode);
                break;
            }
            else
            {
                push(top()->left);
            }
        }
        else
        {
            if (top()->right == nullptr)
            {
                top()->right = newNode;
                push(newNode);
                break;
            }
            else
            {
                push(top()->right);
            }
        }
    }

    while (sz)
    {
        compute_stats(top());
        if (top()->weight <= 1 and top()->weight >= -1)
        {
            pop();
        }
        else if (top()->weight == 2)
        {
            if (top()->left->weight == -1)
                right_to_left_rotation(top()->left);
            left_to_right_rotation(top());
        }
        else
        {
            if (top()->right->weight == 1)
                left_to_right_rotation(top()->right);
            right_to_left_rotation(top());
        }
    }

    return root;
}


TreeNode *findInOrderPredecessor(TreeNode* root, int key){
    if(root == nullptr) return nullptr;
    if(root->val == key) return nullptr;
    if(key < root->val) return findInOrderPredecessor(root->left, key);
    auto k = findInOrderPredecessor(root->right, key);
    return k == nullptr ? root : k;
}


int main()
{
    TreeNode *tree = nullptr;
    tree = insert(tree, 40);
    tree = insert(tree, 20);
    tree = insert(tree, 60);
    tree = insert(tree, 10);
    tree = insert(tree, 50);
    tree = insert(tree, 70);
    tree = insert(tree, 15);
    tree = insert(tree, 5);
    tree = insert(tree, 12);
    tree = insert(tree, 65);
    
}