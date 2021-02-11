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
    TreeNode* merge(vector<int>& pre, vector<int>& ino, int pl, int pr, int il, int ir) {
        if (pl > pr || il > ir) return NULL;
        TreeNode* root = new TreeNode(pre[pl]);
        // 中序序列找根节点位置
        int inx = ma[pre[pl]];
        root->left = merge(pre, ino, pl + 1, pl + 1 + inx - il - 1, il, inx - 1);
        root->right = merge(pre, ino, pl + 1 + inx - il, pr, inx + 1, ir);
        return root;
    }
    TreeNode* buildTree(vector<int>& pre, vector<int>& ino) {
        for (int i = 0; i < ino.size(); i++) ma[ino[i]] = i;
        return merge(pre, ino, 0, pre.size() - 1, 0, ino.size() - 1);
    }
};
