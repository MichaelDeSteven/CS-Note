#include<bits/stdc++.h>

using namespace std;

const int N = 1010;
int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
int g[N][N], st[N][N], n, maxv, minv;
bool flag;

void dfs(int u, int v, int mode) {
    st[u][v] = 1;
    
    for (int i = 0; i < 8; i++) {
        int x = u + dx[i], y = v + dy[i];
        if (x <= 0 || y <= 0 || x > n || y > n) continue;
        if (g[x][y] != g[u][v]) {
            if (mode == 1 && g[x][y] > g[u][v]) flag = false;
            if (mode == 2 && g[x][y] < g[u][v]) flag = false;
            continue;
        }
        if (st[x][y]) continue;
        dfs(x, y, mode);
    }
}

int main() {
    cin >> n;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> g[i][j];
            
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!st[i][j]) {
                flag = true;
                dfs(i, j, 1);
                if (flag) maxv++;
            }
            
    memset(st, 0, sizeof st);
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!st[i][j]) {
                flag = true;
                dfs(i, j, 2);
                if (flag) minv++;
            }
    
    cout << maxv << ' ' << minv << endl;
    return 0;
}
