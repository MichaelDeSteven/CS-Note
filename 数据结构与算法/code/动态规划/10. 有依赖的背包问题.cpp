#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N][N], n, m, father, v[N], w[N];
int e[N], ne[N], h[N], inx;

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int son = e[i];
        dfs(son);
        for (int j = m; j >= v[son]; j--)
            for (int k = 0; k <= j; k++)
                f[u][j] = max(f[u][j], f[u][j - k] + f[son][k]);
    }
    
    // 根节点u的物品没有算上，因此需要将状态转移方程左移
    for (int i = m; i >= v[u]; i--)
        f[u][i] = f[u][i - v[u]] + w[u];
    for (int i = 0; i < v[u]; i++) f[u][i] = 0;
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        int fa;
        cin >> v[i] >> w[i] >> fa;
        if (fa != -1) add(fa, i);
        else father = i;
    }
    
    dfs(father);
    
    cout << f[father][m] << endl;
    return 0;
}
