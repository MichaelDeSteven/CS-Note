#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 510;
int st[N], n, m, dist[N];
int g[N][N];
#define INF 0x3f3f3f3f
void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        }
        
        st[t] = 1;
        for (int j = 1; j <= n; j++) {
            if (dist[j] > dist[t] + g[t][j]) dist[j] = dist[t] + g[t][j];
        }
    }
    if (dist[n] == INF) cout << "-1" << endl;
    else cout << dist[n] << endl;
}
int main() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
    }
    
    dijkstra();
    return 0;
}
