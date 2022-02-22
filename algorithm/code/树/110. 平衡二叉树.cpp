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
    bool flag = true;
    int dfs(TreeNode* root) {
        if (!root) return 0;
        int lmax = dfs(root->left), rmax = dfs(root->right);
        if (abs(lmax - rmax) > 1) flag = false;
        return max(lmax, rmax) + 1;
    }
    bool isBalanced(TreeNode* root) {
        dfs(root);
        return flag;
    }
};
