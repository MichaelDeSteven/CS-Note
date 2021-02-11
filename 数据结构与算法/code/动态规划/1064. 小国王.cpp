#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 11, M = 1 << N;
LL f[N][N*N][M], h[M], g[M], n, k;  
// h[stat]为1说明状态不合法， g[stat]统计该状态放了多少个棋子
// f[i][j][stat]表示前i行放了j个棋子，其中第i行棋子状态为stat

int main() {
    cin >> n >> k;
    for (int stat = 0; stat < M; stat++) {
        int cnt = 0, tot = 0;
        for (int j = 0; j < n; j++) {
            if (stat >> j & 1) {
                cnt++, tot++;
                if (cnt > 1) h[stat] = true;
            } else {
                cnt = 0;
            }
        }
        g[stat] = tot;
    }
    f[0][0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int stat = 0; stat < (1 << n); stat++) {
                if (h[stat]) continue;
                for (int t = 0; t < (1 << n); t++) {
                    if (stat & t || h[stat | t] || j < g[stat]) continue;
                    f[i][j][stat] += f[i - 1][j - g[stat]][t];
                }
            }
        }
    }
    
    LL res = 0;
    for (int stat = 0; stat < (1 << n); stat++)
        res += f[n][k][stat];
        
    cout << res << endl;
    
    return 0;
}
