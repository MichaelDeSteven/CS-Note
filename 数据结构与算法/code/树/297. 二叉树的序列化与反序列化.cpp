/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "null ";
        string res = to_string(root->val) + " ";
        res = res + serialize(root->left) + serialize(root->right);
        return res;
    }

    TreeNode* dfs(int& cnt, vector<string>& vec) {
        if (cnt > vec.size() || vec[cnt] == "null") return NULL;
        TreeNode* node = new TreeNode(stoi(vec[cnt]));
        cnt++;
        node->left = dfs(cnt, vec);
        cnt++;
        node->right = dfs(cnt, vec);
        return node;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> vec;
        for (int i = 0; i < data.size();) {
            int j = i;
            while (j < data.size() && data[j] != ' ') j++;
            string tmp = data.substr(i, j - i);
            vec.push_back(tmp);
            i = j + 1;
        }
        int cnt = 0;
        return dfs(cnt, vec);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
