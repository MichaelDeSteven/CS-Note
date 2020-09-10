#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int g[N][N], n, ha, la, hb, lb, st[N][N];
bool flag;

void dfs(int u, int v) {
    if (u < 0 || v < 0 || u >= n || v >= n || st[u][v] || !g[u][v]) return;
    st[u][v] = 1;
    if (u == hb && v == lb) {
        flag = true;
        return;
    }
    
    if (!flag) {
        for (int i = 0; i < 4; i++) {
            int x = u + dx[i], y = v + dy[i];
            dfs(x, y);
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < n; j++) {
                if (str[j] == '.') g[i][j] = 1;
                else g[i][j] = 0;
            }
        }
        cin >> ha >> la >> hb >> lb;
        
        flag = false;
        memset(st, 0, sizeof st);
        dfs(ha, la);
        if (!flag) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    
    return 0;
}
