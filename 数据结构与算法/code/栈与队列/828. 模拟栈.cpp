#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
const int N = 100010;
// int stk[N], hh;
int main() {
    int n;
    cin >> n;
    string op;
    int num;
    // stack<int> stk;  push pop top empty 
    // vector<int> vec push_back pop_back back !size()
    vector<int> stk;
    
    for (int i = 1; i <= n; i++) {
        cin >> op;
        if (op == "push") {
            cin >> num;
            stk.push_back(num);
        } else if (op == "query") {
            
            cout << stk.back() << endl;
            
        } else if (op == "empty") {
            
            if (stk.size()) cout << "NO" << endl;
            else cout << "YES" << endl;
            
        } else {
            stk.pop_back();
        }
    }
    return 0;
}
