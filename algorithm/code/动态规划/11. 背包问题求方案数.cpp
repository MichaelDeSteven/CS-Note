#include<bits/stdc++.h>

using namespace std;
const int N = 1010, MOD = 1e9 + 7;
int f[N], cnt[N], n, m, v, w;

int main() {
    cin >> n >> m;
    for (int i = 0; i <= m; i++) cnt[i] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> v >> w;
        for (int j = m; j >= v; j--) {
            if (j >= v) {
                if (f[j - v] + w > f[j]) cnt[j] = cnt[j - v];
                else if (f[j - v] + w == f[j]) cnt[j] = (cnt[j] + cnt[j - v]) % MOD;
                f[j] = max(f[j], f[j - v] + w);
            }
        }
    }
    cout << cnt[m] << endl;
    return 0;
}
