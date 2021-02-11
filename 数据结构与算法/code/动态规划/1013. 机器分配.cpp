#include<bits/stdc++.h>

using namespace std;
const int N = 20;
int f[N][N], g[N][N], n, m, res[N];
// f[j] 表示前i个公司分配了j台机器能获得的最大利润
// 公司为组、每个机器的数量为组内物品=》分组背包问题
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> g[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 0; k <= m; k++)
                if (j >= k) f[i][j] = max(f[i][j], f[i - 1][j - k] + g[i][k]);
            
    cout << f[n][m] << endl;
    
    int u = n, v = m;
    while (u && v) {
        for (int j = 0; j <= v; j++)
            if (f[u][v] == f[u - 1][v - j] + g[u][j]) {
                v -= j, res[u] += j;
                break;
            }
        u--;
    }
    for (int i = 1; i <= n; i++) cout << i << ' ' << res[i] << endl;
    return 0;
}
