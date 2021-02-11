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
    int res = 0;
    void dfs(TreeNode* root, int sum) {
        if (!root) return;
        if (root->val == sum) res++;
        dfs(root->left, sum - root->val);
        dfs(root->right, sum - root->val);
    }
    void preorder(TreeNode* root, int sum) {
        if (!root) return;
        dfs(root, sum);
        preorder(root->left, sum);
        preorder(root->right, sum);
    }
    int pathSum(TreeNode* root, int sum) {
        preorder(root, sum);
        return res;
    }
};
