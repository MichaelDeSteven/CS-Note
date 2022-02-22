#include<bits/stdc++.h>

using namespace std;

const int N = 11;
int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};

int st[N][N], n, m, x, y;
int res;

void dfs(int u, int v, int cnt) {
    if (cnt >= n * m) {
        res++;
        return;
    }
    
    
    for (int i = 0; i < 8; i++) {
        int xx = dx[i] + u, yy = dy[i] + v;
        if (xx < 0 || yy < 0 || xx >= n || yy >= m || st[xx][yy]) continue;
        st[xx][yy] = 1;
        dfs(xx, yy, cnt + 1);
        st[xx][yy] = 0;
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> x >> y;
        res = 0;
        st[x][y] = 1;
        dfs(x, y, 1);
        st[x][y] = 0;
        cout << res << endl;
    }
    return 0;
}
