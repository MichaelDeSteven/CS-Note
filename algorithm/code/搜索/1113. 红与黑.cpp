#include<bits/stdc++.h>

using namespace std;

const int N = 25;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int g[N][N], st[N][N], n, m, s, e;
int res;

void dfs(int u, int v) {
    if (u < 0 || v < 0 || u >= n || v >= m || st[u][v] || !g[u][v]) return;
    st[u][v] = 1, res++;
    
    for (int i = 0; i < 4; i++) {
        int x = dx[i] + u, y = dy[i] + v;
        dfs(x, y);
    }
}
int main() {
    while (cin >> m >> n, n && m) {
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < m; j++) {
                if (str[j] == '@') g[i][j] = 1, s = i, e = j;
                else if (str[j] == '.') g[i][j] = 1;
                else g[i][j] = 0;
            }
        }
        memset(st, 0, sizeof st);
        res = 0;
        dfs(s, e);
        cout << res << endl;
    }
    
    return 0;
}
