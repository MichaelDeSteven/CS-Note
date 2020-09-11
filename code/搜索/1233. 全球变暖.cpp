#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int g[N][N], st[N][N], n, over, tot;
bool flag;

void dfs(int u, int v) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        int x = dx[i] + u, y = dy[i] + v;
        if (x <= 0 || y <= 0 || x > n || y > n || !g[x][y]) continue;
        cnt++;
        if (st[x][y]) continue;
        st[x][y] = true;
        dfs(x, y);
    }
    if (cnt == 4) flag = true;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '#') g[i][j] = 1;
        }
        
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!st[i][j] && g[i][j]) {
                tot++;
                flag = false;
                dfs(i, j);
                if (flag) over++;
            }
            
    cout << tot - over << endl;
    return 0;
}
