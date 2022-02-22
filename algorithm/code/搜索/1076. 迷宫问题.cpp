#include<bits/stdc++.h>

using namespace std;

const int N = 1010;
typedef pair<int, int> PII;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int g[N][N], st[N][N], n, res;
vector<PII> path;
PII dist[N][N];

void bfs() {
    queue<PII> q;
    q.push({0, 0});
    st[0][0] = 1;
    
    while (!q.empty()) {
        int sz = q.size();
        
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            int u = t.first, v = t.second;
            for (int j = 0; j < 4; j++) {
                int x = u + dx[j], y = v + dy[j];
                if (x < 0 || y < 0 || x >= n || y >= n || st[x][y] || g[x][y]) continue;
                st[x][y] = 1;
                dist[x][y] = t;
                q.push({x, y});
            }
        }
        res++;
    }
    
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> g[i][j];
        
    bfs();
    
    int u = n - 1, v = n - 1;
    while (u || v) {
        int i = u, j = v;
        path.push_back({i, j});
        u = dist[i][j].first, v = dist[i][j].second;
    }
    
    reverse(path.begin(), path.end());
    cout << 0 << ' ' << 0 << endl;
    for (auto t : path) {
        cout << t.first << ' ' << t.second << endl;
    }
    return 0;
}
