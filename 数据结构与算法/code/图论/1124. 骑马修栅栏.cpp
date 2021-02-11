#include<bits/stdc++.h>

using namespace std;
const int N = 510, M = 1e4;
int g[N][N];
int cnt, res[M], m, d[N];

void dfs(int u) {
    for (int i = 1; i <= 500; i++) {
        if (g[u][i]) {
            g[u][i]--, g[i][u]--;
            dfs(i);
        }
    }
    res[++cnt] = u;
}

int main() {
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a][b]++, g[b][a]++;
        d[a]++, d[b]++;
    }
    
    int start = 1;
    
    for (int i = 1; i <= 500; i++) {
        if (d[i] & 1) {
            start = i;
            break;
        }
    }

    dfs(start);

    for (int i = cnt; i; i--) {
        cout << res[i] << endl;
    }

    return 0;
}
