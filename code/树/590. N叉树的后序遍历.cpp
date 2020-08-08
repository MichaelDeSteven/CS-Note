// 非递归版
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
    vector<int> postorder(Node* root) {
        vector<int> res;
        stack<Node*> stk;
        if (root) stk.push(root);
        while (!stk.empty()) {
            Node* t = stk.top();
            stk.pop();
            for (auto i : t->children) stk.push(i);
            res.push_back(t->val);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
