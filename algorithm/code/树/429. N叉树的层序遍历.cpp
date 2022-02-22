/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        queue<Node*> q;
        if (root) q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            vector<int> tmp;
            for (int i = 0; i < sz; i++) {
                root = q.front();
                q.pop();
                tmp.push_back(root->val);
                for (auto i : root->children) q.push(i);
            }
            res.push_back(tmp);
        }
        return res;        
    }
};
