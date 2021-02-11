#include<bits/stdc++.h>

using namespace std;
const int N = 110, M = 25010;
int f[M], a[N], n;
// f[i][j] 表示前i个数组合能否凑成数j
// f[i][j] |= f[i - 1][j]
// f[i][j] |= f[i - 1][j - a[i]]
int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(f, 0, sizeof f);
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 1, a + 1 + n);
        
        int res = 0;
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (!f[a[i]]) res++;
            f[a[i]] = 1;
            for (int j = 0; j <= 25000; j++) {
                if (j >= a[i]) f[j] |= f[j - a[i]];
            }
        }
        
        cout << res << endl;
    }
    return 0;
}
