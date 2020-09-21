#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N][N], g[N][N], n, m;

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) cin >> g[i][j];
        memset(f, -0x3f, sizeof f);
        f[0][1] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                f[i][j] = max(f[i - 1][j], f[i][j - 1]) + g[i][j];
        cout << f[n][m] << endl;
    }
    
    return 0;
}
