#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 510, M = 1e5;
typedef long long LL;
int p[N], n, m, dist1[N][N], dist2[N][N];
int w[M], e[M], ne[M], h[M], inx;
struct node {
    int a, b, c;
    bool f;
    bool operator < (const node& t) const {
        return c < t.c;
    }
}edg[M];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}

void dfs(int u, int fa, int maxd1, int maxd2, int d1[], int d2[]) {
    d1[u] = maxd1, d2[u] = maxd2;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != fa) {
            int t1 = maxd1, t2 = maxd2;
            if (w[i] > t1) t2 = t1, t1 = w[i];
            else if (w[i] < t1 && w[i] > t2) t2 = w[i];
            dfs(j, u, t1, t2, d1, d2);
        }
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edg[i] = {a, b, c, false};
    }
    LL sum = 0;
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(edg + 1, edg + 1 + m);
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        sum += c, p[x] = y;
        add(a, b, c), add(b, a, c);
        edg[i].f = true;
    }
    for (int i = 1; i <= n; i++) dfs(i, -1, -1, -1, dist1[i], dist2[i]);
    LL res = 1e18;
    for (int i = 1; i <= m; i++) {
        if (!edg[i].f) {
            LL t;
            int a = edg[i].a, b = edg[i].b, c = edg[i].c;
            if (c > dist1[a][b]) {
                t = sum - dist1[a][b] + c;
            } else if (c > dist2[a][b]) {
                t = sum - dist2[a][b] + c;
            }
            res = min(t, res);
        }
    }
    cout << res << endl;
    return 0;
}
