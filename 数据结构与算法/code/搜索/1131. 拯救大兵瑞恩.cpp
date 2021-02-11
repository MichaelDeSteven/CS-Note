#include<bits/stdc++.h>

using namespace std;
const int N = 12;
typedef pair<pair<int, int>, int> PIII;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int n, m, p;
int key[N][N], door[N][N][N][N];
int res;
int st[N][N][1 << N];

bool bfs() {
    queue<PIII> q;
    q.push({{1, 1}, key[1][1]});
    st[1][1][key[1][1]] = 1;
    
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front(); q.pop();
            int u = t.first.first, v = t.first.second, stat = t.second;
            if (u == n && v == m) return true;
            for (int j = 0; j < 4; j++) {
                int x = dx[j] + u, y = dy[j] + v;
                if (x <= 0 || y <= 0 || x > n || y > m) continue;
                int type = door[u][v][x][y], getKey = stat | key[x][y];
                if (st[x][y][getKey] || type == -1 || (type && (stat >> type & 1) == 0)) continue;
                st[x][y][getKey] = true;
                q.push({{x, y}, getKey});
            }
        }
        res++;
    }
    return false;
}
int main() {
    cin >> n >> m >> p;
    int k;
    cin >> k;
    while (k--) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        door[a][b][c][d] = door[c][d][a][b] = e;
        if (!e) door[a][b][c][d] = door[c][d][a][b] = -1;
    }
    cin >> k;
    while (k--) {
        int a, b, c;
        cin >> a >> b >> c;
        key[a][b] |= 1 << c;
    }
    
    if(!bfs()) res = -1;
    
    cout << res << endl;
    return 0;
}
