#include<bits/stdc++.h>

using namespace std;
const int N = 21, M = 1 << 21;
int f[M][N], n, g[N][N];
/*
    f[stat][i]表示当前的状态为stat每个点恰好经过一次，且最后的终点为i
    stat不包含i，则f[stat][i] = INF
    stat包含i，枚举stat中某个点到i的最短路
*/
int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];
            
    memset(f, 0x3f, sizeof f);
    
    f[1][0] = 0;
    for (int stat = 0; stat < (1 << n); stat++) {
        for (int i = 0; i < n; i++) {
            if (((stat >> i) & 1) == 0) continue;
            for (int j = 0; j < n; j++) {
                if ((stat >> j) & 1) {
                    f[stat][i] = min(f[stat][i], f[stat - (1 << i)][j] + g[j][i]);
                }
            }
        }
    }
    
    cout << f[(1 << n) - 1][n - 1] << endl;
    return 0;
}
