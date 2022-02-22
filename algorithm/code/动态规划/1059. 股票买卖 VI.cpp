#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int f[N][2], n, m, a[N];
// f[i][j]表示第i天状态为j，前i天所能最大利润
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(f, -0x3f, sizeof f);
    f[0][0] = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        f[i][0] = max(f[i - 1][0], f[i - 1][1] + a[i]);
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - a[i] - m);
        res = max(res, max(f[i][0], f[i][1]));
    }
    cout << res << endl;
    return 0;
}
