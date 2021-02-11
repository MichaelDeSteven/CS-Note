#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 1010;
#define INF 0x3f3f3f3f
int g[N][N], dist[N], st[N], n, m, w, s;

void dijkstra() {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;
    
    for (int i = 0; i <= n; i++) {
        int t = -1;
        for (int j = 0; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        st[t] = true;
        
        for (int j = 0; j <= n; j++)
            if (dist[j] > dist[t] + g[t][j]) dist[j] = dist[t] + g[t][j];
    }

}
int main() {
    while (cin >> n >> m >> s) {
        memset(g, 0x3f, sizeof g);
        for (int i = 1; i <= m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            g[a][b] = min(g[a][b], c);
        }
        int res = INF;
        cin >> w;
        for (int i = 1; i <= w; i++) {
            int x;
            cin >> x;
            g[0][x] = 0;
        }
        dijkstra();
        res = min(res, dist[s]);
        if (res == INF) res = -1;
        cout << res << endl;
    }
    return 0;
}
