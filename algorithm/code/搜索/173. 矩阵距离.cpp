#include<bits/stdc++.h>

using namespace std;

const int N = 1010;
typedef pair<int, int> PII;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int g[N][N], res[N][N], st[N][N], n, m;

void bfs() {
    queue<PII> q;
    int cnt = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (g[i][j]) {
                q.push({i, j});
                st[i][j] = 1;
            }

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            
            int u = t.first, v = t.second;
            for (int j = 0; j < 4; j++) {
                int x = u + dx[j], y = v + dy[j];
                if (x <= 0 || y <= 0 || x > n || y > m || st[x][y]) continue;
                res[x][y] = cnt;
                st[x][y] = 1;
                q.push({x, y});
            }
        }
        cnt++;
    }
}

int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == '1') g[i][j] = 1;
        }
    }
    
    bfs();
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) cout << res[i][j] << ' ';
        cout << endl;
    }
    return 0;
}
