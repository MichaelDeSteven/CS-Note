// 暴力代码
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
    bool exist(TreeNode* root, TreeNode* target) {
        if (!root) return false;
        if (root == target) return true;
        return exist(root->left, target) || exist(root->right, target);
    }
    TreeNode* dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return NULL;
        if (root == p || root == q) return root;
        bool lp = exist(root->left, p), lq = exist(root->left, q);
        if (lp && lq) return dfs(root->left, p, q);
        else if (!lp && !lq) return dfs(root->right, p, q);
        else return root;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return dfs(root, p, q);
    }
};


// 优化后的代码
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || p == root || q == root) return root;
        TreeNode *ll = lowestCommonAncestor(root->left, p, q), *rr = lowestCommonAncestor(root->right, p, q);
        if (ll && rr) return root;
        // 左右子树均没有pq
        if (!ll && !rr) return NULL;
        // 左子树存在p或q
        if (ll) return ll;
        else return rr;
    }
};
