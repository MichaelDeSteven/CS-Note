#include<bits/stdc++.h>

using namespace std;

const int N = 1e6;

int n, k, st[N], res;

void bfs() {
    queue<int> q;
    q.push(n);
    st[n] = true;
    
    while (!q.empty()) {
        int sz = q.size();
        
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            if (t == k) return;
            if (t - 1 > 0 && !st[t - 1]) st[t - 1] = true, q.push(t - 1);
            if (!st[t + 1]) st[t + 1] = true, q.push(t + 1);
            if (2 * t < N && !st[2 * t]) st[2 * t] = true, q.push(2 * t);
        }
        res++;
    }
}
int main() {
    cin >> n >> k;
    
    bfs();
    
    cout << res << endl;
    return 0;
}
