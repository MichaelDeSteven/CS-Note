#include<bits/stdc++.h>

using namespace std;
const int N = 11;
/*
    分析：N×N，步长为2N，若已知人在i行，则人位于列2N-i

f[i][j][k]表示前i步中，a走到j行，b走到k行所能获得的最大价值
    j == k, f[i][j][k] = max{f[i - 1][j][k - 1], f[i - 1][j - 1][k]} + f[j][i - j]
    f[i][j][k] = f[i - 1][j][k] + g[j][i - j] + g[k][i - k]
*/

int f[2*N][N][N], g[N][N], n;

int main() {
    int a, b, c;        
    cin >> n;
    while (cin >> a >> b >> c) {
        if (!a && !b && !c) break;
        g[a][b] = c;
    }
    
    memset(f, -0x3f, sizeof f);
    f[0][0][0] = 0;
    for (int i = 1; i < 2*n; i++)
        for (int j = 1; j <= i && j <= n; j++)
            for (int k = 1; k <= i && k <= n; k++) {
                int w = j == k ? g[j][i - j + 1] : g[j][i - j + 1] + g[k][i - k + 1];
                f[i][j][k] = max(f[i - 1][j - 1][k], max(f[i - 1][j][k - 1], 
                max(f[i - 1][j - 1][k - 1], f[i - 1][j][k]))) + w;
            }
    
    cout << f[2*n - 1][n][n] << endl;
    return 0;
}
