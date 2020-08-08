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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            int val = INT_MIN;
            for (int i = 0; i < sz; i++) {
                root = q.front();
                q.pop();
                val = max(val, root->val);
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
            }
            res.push_back(val);
        }
        return res;         
    }
};
