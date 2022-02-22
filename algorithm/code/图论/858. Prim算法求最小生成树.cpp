#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 510;
#define INF 0x3f3f3f3f
int g[N][N], dist[N], st[N], n, m;

int prim() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        st[t] = true;
        if (dist[t] == INF) return INF;
        
        res += dist[t];
        for (int j = 1; j <= n; j++)
            dist[j] = min(dist[j], g[t][j]);
    }
    return res;
}

int main() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
        g[b][a] = min(g[b][a], c);
    }
    int res = prim();
    if (res == INF) cout << "impossible" << endl;
    else cout << res << endl;
    return 0;
}
