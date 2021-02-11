#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10, M = 110;
int f[N][2][M], n, m, a[N];
// f[i][j][k]表示第i天状态为j，前i天所能最大利润, 卖出次数为k
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(f, -0x3f, sizeof f);
    for (int i = 0; i <= n; i++) f[i][0][0] = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i && j <= m; j++) {
            if (j) f[i][0][j] = max(f[i - 1][0][j], f[i - 1][1][j - 1] + a[i]);
            f[i][1][j] = max(f[i - 1][1][j], f[i - 1][0][j] - a[i]);
            res = max(res, max(f[i][0][j], f[i][1][j]));
        }
    }
    cout << res << endl;
    return 0;
}
