/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool dfs(TreeNode* r1, TreeNode* r2) {
        if (!r1 && !r2) return true;
        if (!r1 || !r2 || r1->val != r2->val) return false;
        return dfs(r1->left, r2->right) && dfs(r1->right, r2->left);
    }
    bool isSymmetric(TreeNode* root) {
        return dfs(root, root);
    }
};
