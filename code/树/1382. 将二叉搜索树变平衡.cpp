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
    vector<TreeNode*> nums;
    TreeNode* merge(int ll, int rr) {
        if (ll > rr) return NULL;
        int mid = ll + rr >> 1;
        TreeNode* root = nums[mid];
        root->left = merge(ll, mid - 1);
        root->right = merge(mid + 1, rr);
        return root;
    }

    void inorder(TreeNode* root) {
        if (!root) return;
        inorder(root->left);
        nums.push_back(root);
        inorder(root->right);
    }
    TreeNode* balanceBST(TreeNode* root) {
        inorder(root);
        return merge(0, nums.size() - 1);
    }
};
