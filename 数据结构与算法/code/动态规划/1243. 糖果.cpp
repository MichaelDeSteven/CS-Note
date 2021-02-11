#include<bits/stdc++.h>

using namespace std;
const int N = 110, M = 1 << 20;
int n, m, k, st[N], f[M];  // st[i]代表每一包糖果第i种糖果的状态

int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        int stat = 0;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            x--;
            stat |= 1 << x;
        }
        st[i] = stat;
    }
            
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << m); j++) {
            f[j | st[i]] = min(f[j] + 1, f[j | st[i]]);
        }
    }
    
    int res = f[(1 << m) - 1] >= 0x3f3f3f3f ? -1 : f[(1 << m) - 1];
    
    cout << res << endl;
    return 0;
}
