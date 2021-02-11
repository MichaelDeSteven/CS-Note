class Solution {
public:
    stack<int> num;
    void cal(string op) {
        int a = num.top();
        num.pop();
        int b = num.top();
        num.pop();
        if (op == "+") num.push(b + a);
        else if (op == "-") num.push(b - a);
        else if (op == "*") num.push(b * a);
        else num.push(b / a);
    }
    int evalRPN(vector<string>& tokens) {
        for (auto i : tokens) {
            if (i == "+" || i == "-" || i == "*" || i == "/") {
                cal(i);
            } else {
                num.push(stoi(i));
            }
        }
        return num.top();
    }
};
