#include<bits/stdc++.h>

using namespace std;
const int N = 310;
int dx[4] = {0, 1, -1, 0};
int dy[4] = {1, 0, 0, -1};
int g[N][N], f[N][N], n, m;

int dfs(int u, int v) {
    if (f[u][v] != -1) return f[u][v];
    
    f[u][v] = 1;
    for (int i = 0; i < 4; i++) {
        int xx = u + dx[i], yy = v + dy[i];
        if (xx <= 0 || yy <= 0 || xx > n || yy > m) continue;
        int h = g[u][v] - g[xx][yy];
        if (h <= 0) continue;
        
        f[u][v] = max(f[u][v], dfs(xx, yy) + 1);
    }
    return f[u][v];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
    
    memset(f, -1, sizeof f);
    
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) 
            res = max(res, dfs(i, j));
    
    cout << res << endl;
    
    return 0;
}
