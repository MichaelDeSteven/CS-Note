#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
#define INF 0x3f3f3f3f
int e[N], ne[N], h[N], inx;
int n, f[N];
// f[i]存储删除结点i得到的最大连通块点数
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}
int dfs(int u, int fa) {
    int cnt = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        int ans = dfs(j, u);
        f[u] = max(ans, f[u]);
        cnt += ans;
    }
    f[u] = max(f[u], n - cnt - 1);
    return cnt + 1;
}

int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    
    dfs(1, -1);
    
    int res = INF;
    for (int i = 1; i <= n; i++) res = min(res, f[i]);
    
    cout << res << endl;
    return 0;
}
