#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
typedef pair<int, int> PII;
int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, -1, 0, 1, 1, -1, 1, -1};
int g[N][N], st[N][N], n, m, res;

void bfs(int u, int v) {
    queue<PII> q;
    q.push({u, v});
    st[u][v] = 1;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        int x = t.first, y = t.second;
        for (int i = 0; i < 8; i++) {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx <= 0 || yy <= 0 || xx > n || yy > m || st[xx][yy] || !g[xx][yy]) continue;
            st[xx][yy] = 1;
            q.push({xx, yy});
        }
    }
    res++;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == 'W') g[i][j] = 1;
        }
    }
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (g[i][j] && !st[i][j]) bfs(i, j);
    
    cout << res << endl;
    return 0;
}
