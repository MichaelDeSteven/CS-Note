#include<bits/stdc++.h>

using namespace std;
const int N = 110;
typedef pair<int, int> PII;
int dx[8] = {1, 1, -1, -1, 0, 0, 1, -1};
int dy[8] = {1, -1, 1, -1, 1, -1, 0, 0};

int g[N][N], st[N][N], n, m, mx, my, res;

void bfs() {
    queue<PII> q;
    q.push({mx, my});
    st[mx][my] = 1;
    
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            int u = t.first, v = t.second;
            for (int i = 0; i < 8; i++) {
                int x = u + dx[i], y = v + dy[i];
                if (x <= 0 || y <= 0 || x > n || y > m || st[x][y] || !g[x][y]) continue;
                q.push({x, y});
                st[x][y] = 1;
            }
        }
        res++;
    }
}

int main() {
    cin >> m >> n >> my >> mx;
    
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == '.') g[i][j] = 1;
        }
    }
    
    bfs();
    
    cout << res - 1 << endl;
    
    return 0;
}
