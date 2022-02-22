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
    int res = 0;
    void dfs(TreeNode* root, int cnt) {
        if (root == NULL) {
            res = max(cnt, res);
            return;
        }
        dfs(root->left, cnt + 1);
        dfs(root->right, cnt + 1);
    }
    int maxDepth(TreeNode* root) {
        dfs(root, 0);
        return res;
    }
};
