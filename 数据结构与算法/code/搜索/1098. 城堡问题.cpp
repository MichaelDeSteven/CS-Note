#include<bits/stdc++.h>

using namespace std;

const int N = 55;
int dx[4] = {0, -1, 0, 1};
int dy[4] = {-1, 0, 1, 0};

int g[N][N], st[N][N], n, m;
int res, maxv, cnt;

void dfs(int u, int v) {
    st[u][v] = 1;

    for (int i = 0; i < 4; i++) {
        if (g[u][v] >> i & 1) continue;
        int x = dx[i] + u, y = dy[i] + v;
        if (x <= 0 || y <= 0 || x > n || y > m || st[x][y]) continue;
        cnt++;
        dfs(x, y);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
            
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!st[i][j]) {
                res++, cnt = 1;
                dfs(i, j);
                maxv = max(maxv, cnt);                
            }
    
    cout << res << endl;
    cout << maxv << endl;
    
    return 0;
}
