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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> res;
        queue<TreeNode*> q;
        if (root) q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            double cnt = 0;
            for (int i = 0; i < sz; i++) {
                root = q.front();
                q.pop();
                cnt += root->val;
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            res.push_back(cnt / sz);
        }
        return res;
    }
};
