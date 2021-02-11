#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 55, M = 14, MOD = 1000000007;
LL f[N][N][M][M], g[N][N], n, m, k;
/*
    g[i][j]为价值，v = 0表示未拿到东西
    f[i][j][u][v]表示在i，j位置上，之前已经拿到了u件物品，且拿到的最大价值为v的所有方案数
    第u件物品哪里拿的
    之前拿的, f[i][j][u][v] = f[i - 1][j][u][v] + f[i][j - 1][u][v]
    g[i][j] == v则可以第u件物品可以在当前位置拿, 
    f[i][j][u][v] = f[i - 1][j][u - 1][w] + f[i][j - 1][u - 1][w]
*/

int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
            g[i][j]++;
        }
    f[1][1][1][g[1][1]] = 1;
    f[1][1][0][0] = 1;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (i == 1 && j == 1) continue;
            for (int u = 0; u <= k; u++) {
                for (int v = 0; v <= 13; v++) {
                    f[i][j][u][v] = (f[i][j][u][v] + f[i - 1][j][u][v] + f[i][j - 1][u][v]) % MOD;
                    if (u > 0 && g[i][j] == v) {
                        for (int w = 0; w < v; w++)
                            f[i][j][u][v] 
                                = (f[i][j][u][v] + f[i - 1][j][u - 1][w] + f[i][j - 1][u - 1][w]) % MOD;
                    }
                }
            }
        }
                
    LL res = 0;
    for (int v = 0; v <= 13; v++) {
        res = (res + f[n][m][k][v]) % MOD;
    }
    
    cout << res << endl;
    
    return 0;
}



// 记忆化搜索版本
#include<bits/stdc++.h>

using namespace std;
const int N = 14, M = 55, MOD = 1000000007;
typedef long long LL;
int n, m, k, g[M][M];
LL f[M][M][N][N];

LL dfs(int u, int v, int keep, int maxV) {
    if (f[u][v][keep][maxV] != -1) return f[u][v][keep][maxV];
    if (u == n && v == m) {
        return f[u][v][keep][maxV] = (keep == k || (keep == k - 1 && g[u][v] > maxV)) ? 1 : 0; 
    }
    
    LL res = 0;
    
    if (u + 1 <= n) {
        res = (res + dfs(u + 1, v, keep, maxV)) % MOD;
        if (g[u][v] > maxV) res = (res + dfs(u + 1, v, keep + 1, g[u][v])) % MOD;
    }
    if (v + 1 <= m) {
        res = (res + dfs(u, v + 1, keep, maxV)) % MOD;
        if (g[u][v] > maxV) res = (res + dfs(u, v + 1, keep + 1, g[u][v])) % MOD;
    }
        
    return f[u][v][keep][maxV] = res % MOD;
}
int main() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            cin >> g[i][j];
            g[i][j]++;
        }
    
    
    memset(f, -1, sizeof f);
    
    cout << dfs(1, 1, 0, 0) << endl;
        
    return 0;
}
