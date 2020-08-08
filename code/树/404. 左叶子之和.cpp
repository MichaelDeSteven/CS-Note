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
    int sum = 0;
    void dfs(TreeNode* root, bool left) {
        if (!root) return;
        if (!root->left && !root->right) {
            if (left) sum += root->val;
            return;
        }
        dfs(root->left, true);
        dfs(root->right, false);
    }
    int sumOfLeftLeaves(TreeNode* root) {
        dfs(root, false);
        return sum;
    }
};
