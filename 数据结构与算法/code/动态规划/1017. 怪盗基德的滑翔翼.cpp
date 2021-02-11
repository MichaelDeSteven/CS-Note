#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N][2], h[N], n, k;

int main() {
    cin >> k;
    while (k--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> h[i];
        int res = 0;
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i++) {
            f[i][0] = 1;
            for (int j = 1; j < i; j++)
                if (h[i] < h[j]) f[i][0] = max(f[i][0], f[j][0] + 1);
            res = max(res, f[i][0]);
        }
        
        for (int i = n; i >= 1; i--) {
            f[i][1] = 1;
            for (int j = n; j > i; j--)
                if (h[i] < h[j]) f[i][1] = max(f[i][1], f[j][1] + 1);
            res = max(res, f[i][1]);
        }
        cout << res << endl;
    }
    return 0;
}
