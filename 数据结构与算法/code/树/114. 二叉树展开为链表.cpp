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
    vector<TreeNode*> res;
    void dfs(TreeNode* root) {
        if (!root) return;
        res.push_back(root);
        dfs(root->left);
        dfs(root->right);
        root->left = NULL, root->right = NULL;
    }
    void flatten(TreeNode* root) {
        dfs(root);
        for (int i = 0; i + 1 < res.size(); i++) {
            res[i]->right = res[i + 1];
        }
    }
};
