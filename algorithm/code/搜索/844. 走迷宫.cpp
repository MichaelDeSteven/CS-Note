#include<bits/stdc++.h>

using namespace std;
const int N = 110;
typedef pair<int, int> PII;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int g[N][N], st[N][N], n, m;

void bfs() {
    queue<PII> q;
    q.push({1, 1});
    st[1][1] = 1;
    int res = 0;
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            int u = t.first, v = t.second;
            if (u == n && v == m) {
                cout << res << endl;
                return;
            }
            for (int j = 0; j < 4; j++) {
                int xx = u + dx[j], yy = v + dy[j];
                if (xx <= 0 || yy <= 0 || xx > n || yy > m || g[xx][yy] || st[xx][yy]) continue;
                st[xx][yy] = 1;
                q.push({xx, yy});
            }
        }
        res++;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> g[i][j];
    
    bfs();
    
    return 0;
}
