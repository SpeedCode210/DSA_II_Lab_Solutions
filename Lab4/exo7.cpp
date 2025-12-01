#include <iostream>
typedef long long ll;
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
};

TreeNode *findInOrderPredecessor(TreeNode* root, int key){
    if(root == nullptr) return nullptr;
    if(root->val == key) return nullptr;
    if(key < root->val) return findInOrderPredecessor(root->left, key);
    auto k = findInOrderPredecessor(root->right, key);
    return k == nullptr ? root : k;
}

signed main() {
   
}