#include<bits/stdc++.h>

using namespace std;
const int N = 55;
int f[2*N][N][N], g[N][N], n, m;
/*
    f[i][j][k]，表示走到i步后, a处于j行，b处于k行所能获得的最大价值
*/
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> g[i][j];
    
    memset(f, -0x3f, sizeof f);       
    f[1][1][1] = g[1][1];
    
    for (int i = 1; i < n + m; i++) {
        for (int j = 1; j <= n && j <= i; j++) {
            for (int k = 1; k <= n && k <= i; k++) {
                if (j == k && j != n) continue;
                int maxv = max(f[i - 1][j][k], max(f[i - 1][j - 1][k], 
                    max(f[i - 1][j][k - 1], f[i - 1][j - 1][k - 1])));
                int w = j == k ? g[j][i - j + 1] : g[j][i - j + 1] + g[k][i - k + 1];
                f[i][j][k] = maxv + w;
            }
        }
    }
    
    cout << f[n + m - 1][n][n] << endl;
            
    
    return 0;
}
