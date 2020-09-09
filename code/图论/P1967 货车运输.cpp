#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1e4 + 10, M = 1e5 + 10;
#define INF 0x3f3f3f3f
int e[M], ne[M], w[M], h[M], inx;
int n, m, q;
int p[N];
int fa[N][18], dep[N], minv[N][18];

struct edg {
    int a, b, c;
    bool operator < (const edg& t) const {
        return c > t.c;
    }
}edg[M];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;    
}

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}

void kruskal() {
    for (int i = 1; i <= n; i++) p[i] = i;
    
    sort(edg + 1, edg + 1 + m);
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        p[x] = y;
        add(a, b, c), add(b, a, c);
    }
}

void bfs() {
    memset(dep, 0x3f, sizeof dep);
    memset(minv, 0x3f, sizeof minv);
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
                
                fa[j][0] = t, minv[j][0] = w[i];
                for (int k = 1; k < 18; k++) {
                    int anc = fa[j][k - 1];
                    fa[j][k] = fa[anc][k - 1];
                    minv[j][k] = min(minv[anc][k - 1], minv[j][k - 1]);
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (find(a) != find(b)) return -1;
    int res = INF;
    if (dep[a] < dep[b]) swap(b, a);
    for (int k = 17; k >= 0; k--)
        if (dep[fa[a][k]] >= dep[b]) {
            res = min(res, minv[a][k]);
            a = fa[a][k];
        }
    if (a != b) {
        for (int k = 17; k >= 0; k--)
            if (fa[a][k] != fa[b][k]) {
                res = min(res, min(minv[a][k], minv[b][k]));
                a = fa[a][k], b = fa[b][k];
            }
        res = min(res, min(minv[a][0], minv[b][0]));
    }
    return res;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edg[i] = {a, b, c};
    }
    
    kruskal();
    
    bfs();
    cin >> q;
    
    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << endl;
    }
    
    return 0;
}
