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
    int res = INT_MIN;
    int dfs(TreeNode* root) {
        if (!root) return 0;
        int lmax = max(dfs(root->left), 0), rmax = max(dfs(root->right), 0);
        res = max(res, lmax + rmax + root->val);
        return max(lmax, rmax) + root->val;
    }
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return res;
    }
};
