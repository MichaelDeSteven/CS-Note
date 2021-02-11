#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 110;
#define INF 0x3f3f3f3f
int n, m, g[N][N], dist[N], st[N], cnt, lev[N], res = INF;

void dijkstra(int left, int right) {
    memset(st, 0, sizeof st);
    memset(dist, 0x3f, sizeof dist);
    dist[0] = 0;

    for (int i = 0; i <= n; i++) {
        int t = -1;
        for (int j = 0; j <= n; j++) 
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        
        st[t] = true;
        for (int j = 0; j <= n; j++)
            if (lev[j] >= left && lev[j] <= right)
                if (dist[j] > dist[t] + g[t][j]) dist[j] = dist[t] + g[t][j];
    }
    res = min(res, dist[1]);
}
int main() {
    cin >> m >> n;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= n; i++) {
        int p, l, x;
        cin >> p >> l >> x;
        g[0][i] = min(g[0][i], p), lev[i] = l;
        for (int j = 1; j <= x; j++) {
            int t, v;
            cin >> t >> v;
            g[t][i] = min(g[t][i], v);
        }
    }
    for(int lv = lev[1] - m; lv <= lev[1]; lv++)
        dijkstra(lv, lv + m);
    cout << res << endl;
    return 0;
}
