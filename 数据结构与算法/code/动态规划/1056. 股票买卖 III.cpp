#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int f[N][2][3], n, a[N];
// f[i][j][k]表示第i天状态为j，前i天所能最大利润, 卖出次数为k
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(f, -0x3f, sizeof f);
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i][0][0] = f[i - 1][0][0];
        f[i][1][0] = max(f[i - 1][1][0], f[i - 1][0][0] - a[i]);
        f[i][0][1] = max(f[i - 1][0][1], f[i - 1][1][0] + a[i]);
        if (i >= 2) {
            f[i][1][1] = max(f[i - 1][1][1], f[i - 1][0][1] - a[i]);
            f[i][0][2] = max(f[i - 1][0][2], f[i - 1][1][1] + a[i]);
        }
    }
    cout << max(0, max(f[n][0][1], f[n][0][2])) << endl;
    return 0;
}
