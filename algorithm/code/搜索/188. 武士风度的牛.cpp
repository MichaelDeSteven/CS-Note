#include<bits/stdc++.h>

using namespace std;

const int N = 155;
int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};
typedef pair<int, int> PII;
int g[N][N], st[N][N], n, m;
int s1, e1, s2, e2;
int res;

void bfs() {
    queue<PII> q;
    q.push({s1, e1});
    st[s1][e1] = true;
    
    while (!q.empty()) {
        int sz = q.size();
        
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            int u = t.first, v = t.second;
            if (u == s2 && v == e2) return;
            for (int j = 0; j < 8; j++) {
                int x = u + dx[j], y = v + dy[j];
                if (x <= 0 || y <= 0 || x > n || y > m || st[x][y] || !g[x][y]) continue;
                st[x][y] = true;
                q.push({x, y});
            }
        }
        res++;
    }
}
int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c != '*') g[i][j] = 1;
            if (c == 'K') s1 = i, e1 = j;
            if (c == 'H') s2 = i, e2 = j;
        }
    
    bfs();
    
    cout << res << endl;
    return 0;
}
