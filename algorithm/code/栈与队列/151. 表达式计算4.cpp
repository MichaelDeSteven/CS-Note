#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
using namespace std;

string str;
// 操作数栈
stack<int> nums;
// 操作符栈
stack<char> ops;

void cal() {
    int a = nums.top(); 
    nums.pop();
    int b = nums.top(); 
    nums.pop();
    char op = ops.top(); 
    ops.pop();

    if (op == '+') nums.push(b + a);
    else if (op == '-') nums.push(b - a);
    else if (op == '*') nums.push(b * a);
    else if (op == '/') nums.push(b / a);
    else if (op == '^') {
        int res = 1;
        while (a--) res *= b;
        nums.push(res);
    }
}
int main() {
    cin >> str;
    str = "(" + str + ")";
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        
        if (c == '(') ops.push('(');
        else if (isdigit(c)) {
            int j = i, cnt = 0;
            while (j < str.size() && isdigit(str[j])) cnt = cnt * 10 + str[j++] - '0';
            i = j - 1;
            nums.push(cnt);
        } else if (c == '-' && (!i || str[i - 1] == '(')) {                 // 判断负数的情况
            int j = i + 1, cnt = 0;
            while (j < str.size() && isdigit(str[j])) cnt = cnt * 10 + str[j++] - '0';
            i = j - 1;
            nums.push(cnt*-1);            
        } else if (c == '+' || c == '-') {
            while (ops.top() != '(') cal();
            ops.push(c);
        } else if (c == '*' || c == '/') {
            while (ops.top() == '*' || ops.top() == '/' || ops.top() == '^') cal();
            ops.push(c);
        } else if (c == '^') {
            while (ops.top() == '^') cal();
            ops.push(c);
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') cal();
            if (!ops.empty()) ops.pop();
        }
    }
    
    cout << nums.top() << endl;
    return 0;
}
