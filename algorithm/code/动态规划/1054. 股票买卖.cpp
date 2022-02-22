#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int f[N][2][2], n, a[N];

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    f[0][0][0] = 0;
    f[0][1][0] = f[0][0][1] = f[0][1][1] = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        f[i][0][0] = f[i][0][1] = f[i][1][0] = -0x3f3f3f3f;
        f[i][0][0] = f[i - 1][0][0];
        f[i][1][0] = max(f[i - 1][1][0], f[i - 1][0][0] - a[i]);
        f[i][0][1] = max(f[i - 1][0][1], f[i - 1][1][0] + a[i]);
    }
    cout << max(f[n][0][1], 0) << endl;
    return 0;
}
