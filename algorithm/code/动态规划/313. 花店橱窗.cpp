#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N][N], n, m, val[N][N];
/*
    f[i][j]表示第i朵花放在第j个花瓶获得的最大价值
    f[i][j] = f[i - 1][k] + val[i][j], k < j 
*/
vector<int> vec;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> val[i][j];
    
    memset(f, -0x3f, sizeof f);
    for (int j = 0; j <= m; j++) f[0][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= m - (n - i); j++) {
            int maxv = -0x3f3f3f3f;
            for (int k = i - 1; k < j; k++)
                maxv = max(maxv, f[i - 1][k]);
            f[i][j] = maxv + val[i][j];
        }
    
    int res = -0x3f3f3f3f;
    for (int j = 1; j <= m; j++) res = max(res, f[n][j]);

    cout << res << endl;
    
    int u = n, v = m;
    while (u && v) {
        if (f[u][v] == res) {
            for (int i = 1; i <= v; i++)
                if (f[u][i] == res) {
                    v = i;
                    break;
                }
            vec.push_back(v);
            res -= val[u][v];
            u--;
        }
        v--;
    }
    
    reverse(vec.begin(), vec.end());
    
    for (auto t : vec) cout << t << ' ';
    return 0;
}
