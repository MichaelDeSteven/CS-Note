#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int f[N][3], a[N], n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memset(f, -0x3f, sizeof f);
    f[0][0] = 0;
    
    for (int i = 1; i <= n; i++) {
        f[i][0] = max(f[i - 1][0], f[i - 1][2]);
        f[i][1] = max(f[i - 1][1], f[i - 1][0] - a[i]);
        f[i][2] = f[i - 1][1] + a[i];
    }
    
    cout << max(f[n][0], f[n][2]) << endl;
    
    return 0;
}
