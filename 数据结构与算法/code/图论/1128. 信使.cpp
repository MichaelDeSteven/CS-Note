#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>

using namespace std;
const int N = 110;
#define INF 0x3f3f3f3f
int g[N][N], n, m, dist[N], st[N];

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        st[t] = 1;
        for (int j = 1; j <= n; j++)
            if (dist[j] > dist[t] + g[t][j]) dist[j] = dist[t] + g[t][j];
    }
    
    bool flag = false;
    int maxv = 0;
    for (int i = 1; i <= n; i++) 
        if (dist[i] == INF) flag = true;
        else maxv = max(maxv, dist[i]);
    if (flag) cout << "-1" << endl;
    else cout << maxv << endl;
}

int main() {
    cin >> n >> m;
    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = g[y][x] = z; 
    }
    
    dijkstra();
    
    return 0;
}
