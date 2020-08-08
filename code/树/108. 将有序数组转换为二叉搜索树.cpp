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
    TreeNode* merge(int ll, int rr, vector<int>& nums) {
        if (ll > rr) return NULL;
        int mid = ll + rr >> 1;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = merge(ll, mid - 1, nums);
        root->right = merge(mid + 1, rr, nums);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return merge(0, nums.size() - 1, nums);
    }
};
