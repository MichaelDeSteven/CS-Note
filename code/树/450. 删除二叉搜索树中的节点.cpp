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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return root;
        else if (root->val > key) root->left = deleteNode(root->left, key);
        else if (root->val < key) root->right = deleteNode(root->right, key);
        else {
            if (root->left && root->right) {
                TreeNode* t = root->left;
                while (t->right) t = t->right;
                root->val = t->val;
                root->left = deleteNode(root->left, root->val);
            } else {
                if (root->left) return root->left;
                else return root->right;
            }
        }
        return root;
    }
};
