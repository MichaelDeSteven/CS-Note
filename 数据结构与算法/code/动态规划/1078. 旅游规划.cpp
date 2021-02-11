#include<bits/stdc++.h>

using namespace std;
const int N = 1e6;
int e[N], ne[N], h[N], inx;
int n, f[N][3], maxd, st[N];

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        int v = f[j][0] + 1;
        if (v > d1) d2 = d1, d1 = v;
        else if (v > d2) d2 = v;
    }
    f[u][0] = d1, f[u][1] = d2;
    maxd = max(maxd, f[u][0] + f[u][1]);
}

void dfs1(int u, int fa) {
    int vec[3] = {f[u][0], f[u][1], f[u][2]};
    sort(vec, vec + 3);
    if (vec[1] + vec[2] == maxd) st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        if (f[j][0] + 1 == f[u][0]) f[j][2] = max(f[u][2], f[u][1]) + 1;
        else f[j][2] = max(f[u][2], f[u][0]) + 1;
        dfs1(j, u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    
    dfs(0, -1);
    dfs1(0, -1);
    for (int i = 0; i < n; i++)
        if (st[i]) cout << i << endl;
    return 0;
}
