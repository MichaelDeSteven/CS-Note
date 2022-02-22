#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 100010, M = 4*N;
int e[M], ne[M], h[M], inx;
int fa[N][18], dep[N], d[N];
int n, m;

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void bfs() {
    memset(dep, 0x3f, sizeof dep);
    dep[0] = 0, dep[1] = 1;
    queue<int> q;
    q.push(1);

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dep[j] > dep[t] + 1) {
                dep[j] = dep[t] + 1;
                q.push(j);

                fa[j][0] = t;
                for (int k = 1; k < 18; k++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int k = 17; k >= 0; k--) 
        if (dep[fa[a][k]] >= dep[b]) a = fa[a][k];
    if (a == b) return a;

    for (int k = 17; k >= 0; k--)
        if (fa[a][k] != fa[b][k]) {
            a = fa[a][k], b = fa[b][k];
        }

    return fa[a][0];
}

void dfs(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        d[u] += d[j];
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    bfs();
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        d[a]++, d[b]++, d[lca(a, b)] -= 2;
    }

    dfs(1, -1);
    int res = 0;
    for (int i = 2; i <= n; i++) {
        if (d[i] == 1) res++;
        else if (!d[i]) res += m;
    }

    cout << res << endl;
    return 0;
}
