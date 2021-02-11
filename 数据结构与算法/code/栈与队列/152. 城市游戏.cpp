#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1010;
char g[N][N];
int n, m, f[N], res;
int ll[N], rr[N];

void cal(int bound[N]) {
    int stk[N], hh = 0;
    stk[hh] = 0;
    for (int i = 1; i <= m; i++) {
        while (hh && f[i] <= f[stk[hh]]) hh--;
        bound[i] = stk[hh];
        stk[++hh] = i;
    }
}

void solve() {
    cal(ll);
    reverse(f + 1, f + 1 + m);
    cal(rr);
    reverse(f + 1, f + 1 + m);
    reverse(rr + 1, rr + 1 + m);
    
    for (int i = 1; i <= m; i++) {
        int len = (m - rr[i]) - ll[i];
        res = max(res, 3 * len * f[i]);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= m; j++) cin >> g[i][j];
        
    for (int i = 1; i <= n; i++) {
        // 以每一行为x轴，统计每一列的高度，那么就变成了直方图最大矩形问题
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'R') f[j] = 0;
            else f[j]++;
        }
        solve();
    }
    
    cout << res << endl;
}
