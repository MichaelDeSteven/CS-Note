#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>


using namespace std;
const int N = 1010;
#define INF 0x3f3f3f3f
int g[N][N], n, m, k, f[N][N], dist[N], st[N];

int dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[1] = 0;
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        st[t] = true;
        for (int j = 1; j <= n; j++)
            if (dist[j] > dist[t] + f[t][j]) dist[j] = dist[t] + f[t][j];
    }
    return dist[n];
}
bool check(int x) {
    memcpy(f, g, sizeof f);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (f[i][j] != INF)
                if (f[i][j] > x) f[i][j] = 1;
                else f[i][j] = 0;
                
    if (dijkstra() <= k) return true;
    return false;
}

int main() {
    memset(g, 0x3f, sizeof g);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
        g[b][a] = min(g[b][a], c);
    }
    int ll = 0, rr = 1e6 + 10;
    while (ll < rr) {
        int mid = ll + rr >> 1;
        if (check(mid)) rr = mid;
        else ll = mid + 1;
    }
    if (ll > 1e6) ll = -1;
    cout << ll << endl;
    return 0;
}
