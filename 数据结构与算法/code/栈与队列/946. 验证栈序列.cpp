class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;
        for (int i = 0, j = 0; i < pushed.size(); ) {
            // 值不重复，那么碰到栈顶元素与当前弹出序列相同时，应当停止压入
            while (i < pushed.size() && (stk.empty() || popped[j] != stk.top())) stk.push(pushed[i++]);
            // 栈非空时，栈顶元素与当前弹出序列不相同时，应当停止弹出
            while (j < popped.size() && !stk.empty() && popped[j] == stk.top()) stk.pop(), j++;
        }
        return stk.empty();
    }
};
