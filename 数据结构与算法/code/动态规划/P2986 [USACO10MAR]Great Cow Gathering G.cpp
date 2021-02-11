#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 2e5 + 10;
int e[N], ne[N], h[N], w[N], inx;
int n;
LL f[N], sz[N], cnt[N], sum; // cnt[i]表示结点i的所有子结点总数
void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs1(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs1(j, u);
        cnt[u] += cnt[j] + sz[j];
        f[u] += f[j] + (cnt[j] + sz[j]) * w[i];
    }
}

void dfs2(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        f[j] = f[u] + (sum - sz[j] - cnt[j]) * w[i] - (sz[j] + cnt[j]) * w[i];
        dfs2(j, u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> sz[i];
        sum += sz[i];
    }
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    dfs1(1, -1);
    dfs2(1, -1);
    
    LL res = 0x3f3f3f3f3f3f3f3f;
    for (int i = 1; i <= n; i++) res = min(res, f[i]);
    
    cout << res << endl;
    return 0;
}
