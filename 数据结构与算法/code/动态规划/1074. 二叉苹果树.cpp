#include<bits/stdc++.h>

using namespace std;
const int N = 210;
int e[N], ne[N], h[N], w[N], inx;
int n, q, f[N][N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        for (int v = q; v; v--)
            for (int k = 0; k + 1 <= v; k++)
                f[u][v] = max(f[u][v], f[u][k] + f[j][v - k - 1] + w[i]);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    dfs(1, -1);
    
    cout << f[1][q] << endl;
    return 0;
}
