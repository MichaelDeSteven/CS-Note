/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int cnt, res;
    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->left);
        if (--cnt == 0) {
            res = root->val;
            return;
        }
        dfs(root->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        cnt = k;
        dfs(root);
        return res;
    }
};
