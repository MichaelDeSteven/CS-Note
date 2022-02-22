#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

const int N = 100010;
stack<int> stk;
string str;
int main() {
    cin >> str;
    int res = 0;
    // 初始化
    stk.push(-1);
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        // 左括号直接入栈
        if (c == '(' || c == '[' || c == '{') stk.push(i);
        else {
            // 匹配
            if (c == ')' && str[stk.top()] == '(' || c == ']' && str[stk.top()] == '[' || c == '}' && str[stk.top()] == '{') {
                stk.pop();
                // 满足条件的长度，stk.top()表示美观的子段开始的位置
                res = max(res, i - stk.top());
            } else stk.push(i);
        }
    }
    cout << res << endl;
    return 0;
}
