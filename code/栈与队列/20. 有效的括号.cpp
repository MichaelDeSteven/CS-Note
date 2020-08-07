class Solution {
public:
    bool isValid(string s) {
        // 用栈来匹配最近的括号，匹配则出栈，不匹配提前返回false
        stack<char> stk;
        for (auto i : s) {
            if (i == '(' || i == '{' || i == '[' || stk.empty()) stk.push(i);
            else if (!stk.empty()) {
                if (stk.top() == '(' && i == ')') stk.pop();
                else if (stk.top() == '[' && i == ']') stk.pop();
                else if (stk.top() == '{' && i == '}') stk.pop();
                else return false;
            }
        }

        return stk.empty();
    }
};
