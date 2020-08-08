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
    vector<TreeNode*> dfs(int ll, int rr) {
        if (ll > rr) return {NULL};
        vector<TreeNode*> res;
        for (int i = ll; i <= rr; i++) {
            auto l = dfs(ll, i - 1), r = dfs(i + 1, rr);
            for (auto j : l) {
                for (auto k : r) {
                    TreeNode* root = new TreeNode(i);
                    root->left = j, root->right = k;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
    vector<TreeNode*> generateTrees(int n) {
        if (!n) return {};
        return dfs(1, n);
    }
};
