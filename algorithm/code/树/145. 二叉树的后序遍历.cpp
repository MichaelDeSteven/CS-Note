// 递归版
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
    vector<int> res;
    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->left);
        dfs(root->right);
        res.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        dfs(root);
        return res;
    }
};


// 非递归版1
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        if (root) stk.push(root);
        while (!stk.empty()) {
            TreeNode* t = stk.top();
            stk.pop();
            if (t->left) stk.push(t->left);
            if (t->right) stk.push(t->right);
            res.push_back(t->val);
        }

        reverse(res.begin(), res.end());

        return res;
    }
};

// 非递归版2
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> stk;
        while (root || !stk.empty()) {
            while (root) {
                stk.push(root);
                res.push_back(root->val);
                root = root->right;
            }
            root = stk.top()->left;
            stk.pop();
        }

        reverse(res.begin(), res.end());

        return res;
    }
};
