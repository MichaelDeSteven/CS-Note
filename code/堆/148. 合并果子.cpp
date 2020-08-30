#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 10010;
int n, res;

int main() {
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> h;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        h.push(x);
    }
    
    for (int i = 1; i <= n - 1; i++) {
        int a = 0;
        a += h.top(), h.pop();
        a += h.top(), h.pop();
        h.push(a);
        res += a;
    }
    
    cout << res << endl;
    return 0;
}
