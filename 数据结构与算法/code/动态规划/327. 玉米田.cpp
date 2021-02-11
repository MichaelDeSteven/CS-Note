#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 13, M = 1 << 13, MOD = 100000000;
LL f[N][M], n, m, g[N][N], h[N][M];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
    
    for (int i = 1; i <= n; i++) {
        for (int stat = 1; stat < (1 << m); stat++) {
            int cnt = 0;
            for (int j = 1; j <= m; j++) {
                if ((stat >> (j - 1) & 1)) {
                    cnt++;
                    if (!g[i][j] || cnt > 1) {
                        h[i][stat] = true;
                        break;
                    }
                } else {
                    cnt = 0;
                }
            }
        }
    }
    
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int stat = 0; stat < (1 << m); stat++) {
            if (h[i][stat]) continue;
            for (int t = 0; t < (1 << m); t++) {
                if (t & stat || h[i - 1][t]) continue;
                f[i][stat] = (f[i][stat] + f[i - 1][t]) % MOD;
            }
        }
    }
    
    LL res = 0;
    for (int stat = 0; stat < (1 << m); stat++) {
        res = (res + f[n][stat]) % MOD;
    }
    
    cout << res << endl;
    
    return 0;
}
