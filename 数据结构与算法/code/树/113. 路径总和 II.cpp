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
    vector<vector<int>> res;
    void dfs(TreeNode* root, int sum, vector<int> tmp) {
        if (!root) return;
        tmp.push_back(root->val);
        if (!root->left && !root->right) {
            if (root->val == sum) res.push_back(tmp);
            return;
        }
        dfs(root->left, sum - root->val, tmp);
        dfs(root->right, sum - root->val, tmp);
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        dfs(root, sum, {});
        return res;
    }
};
