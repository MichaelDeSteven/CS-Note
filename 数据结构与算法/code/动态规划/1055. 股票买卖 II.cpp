#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int f[N][2], n, a[N];
// f[i][j]表示第i天状态为j，前i天所能最大利润
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    f[0][0] = 0;
    f[0][1] = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        f[i][0] = f[i][1] = -0x3f3f3f3f;
        f[i][0] = max(f[i - 1][0], f[i - 1][1] + a[i]);
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - a[i]);
    }
    cout << max(f[n][0], 0) << endl;
    return 0;
}
