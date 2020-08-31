#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 2010;

int n, m, a, b, st[N];
double dist[N], g[N][N];

void dijkstra() {
    dist[a] = 1;
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] < dist[j])) t = j;
        st[t] = true;

        for (int j = 1; j <= n; j++)
            if (dist[j] < dist[t]*g[t][j]) dist[j] = dist[t]*g[t][j];
    }
    
    printf("%.8lf\n", 100.0 / dist[b]);
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = g[y][x] = 1.0 - z*0.01;
    }
    cin >> a >> b;
    dijkstra();
    
    return 0;
}
