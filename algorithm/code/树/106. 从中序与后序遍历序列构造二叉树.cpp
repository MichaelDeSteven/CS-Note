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
    unordered_map<int, int> ma;
    TreeNode* dfs(vector<int>& inorder, vector<int>& postorder, int il, int ir, int pl, int pr) {
        if (il > ir) return NULL;
        int inx = ma[postorder[pr]];
        TreeNode* root = new TreeNode(postorder[pr]);
        root->left = dfs(inorder, postorder, il, inx - 1, pl, pl + inx - il - 1);
        root->right = dfs(inorder, postorder, inx + 1, ir, pl + inx - il, pr - 1);
        return root;
    }
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++) {
            ma[inorder[i]] = i;
        }
        return dfs(inorder, postorder, 0, inorder.size() - 1, 0, postorder.size() - 1);
    }
};
