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
    int res = INT_MAX;
    void dfs(TreeNode* root, int cnt) {
        if (!root) return;
        if (!root->left && !root->right) {
            res = min(cnt + 1, res);
            return;
        }
        dfs(root->left, cnt + 1);
        dfs(root->right, cnt + 1);
    }
    int minDepth(TreeNode* root) {
        dfs(root, 0);
        return res == INT_MAX ? 0 : res;
    }
};
