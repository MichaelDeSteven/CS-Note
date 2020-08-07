#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
const int N = 100010;
// int que[N], hh, tt = -1;
int main() {
    int n;
    cin >> n;
    string op;
    int num;
    // stack<int> stk;  push pop top empty 
    // vector<int> vec push_back pop_back back !size()
    // vector<int> stk;
    queue<int> que;         // push pop front back empty(size)
    
    for (int i = 1; i <= n; i++) {
        cin >> op;
        if (op == "push") {
            cin >> num;
            que.push(num);
        } else if (op == "query") {
            
            cout << que.front() << endl;
            
        } else if (op == "empty") {
            
            if (!que.empty()) cout << "NO" << endl;
            else cout << "YES" << endl;
            
        } else {
            que.pop();
        }
    }
    return 0;
}
