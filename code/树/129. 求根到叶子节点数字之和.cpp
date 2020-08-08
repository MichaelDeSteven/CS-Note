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
    void dfs(TreeNode* root, int cnt) {
        if (!root) return;
        if (!root->left && !root->right) {
            sum += cnt * 10 + root->val;
            return;
        }
        dfs(root->left, cnt * 10 + root->val);
        dfs(root->right, cnt * 10 + root->val);
    }
    int sumNumbers(TreeNode* root) {
        dfs(root, 0);
        return sum;
    }
};
