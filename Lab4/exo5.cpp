#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

typedef TreeNode N;

//////
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
//////

N *min_avl(int n, int &nb){
    if(n == 0) return nullptr;
    if(n == 1) return new N{nb++};
    N *left_tree = min_avl(n-1, nb);
    int root = nb++;
    N *right_tree = min_avl(n-2, nb);
    return new N{root, left_tree, right_tree};
}

// Time Complexity O(phi^n)

int main(){
    int cache = 1;
    auto tree = min_avl(5, cache);
    printTree(tree);
}