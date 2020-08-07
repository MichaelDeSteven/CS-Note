#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;

stack<int> stk;
vector<int> vec;
int n, res = 20;

void dfs(int cnt) {
    if (!res) return;
    // 火车都出栈了
    if (cnt > n) {
        if (vec.size() == n) {
            for (auto i : vec) cout << i;
            cout << endl;
            res--;
        }
        return;
    }

    if (!stk.empty()) {
        // 栈顶火车出栈
        vec.push_back(stk.top());
        stk.pop();
        dfs(cnt);
        stk.push(vec.back());
        vec.pop_back();
    }
    
    // 新火车入栈
    stk.push(cnt + 1);
    dfs(cnt + 1);
    stk.pop();
}

int main() {
    cin >> n;
    dfs(0);
    
    return 0;
}
