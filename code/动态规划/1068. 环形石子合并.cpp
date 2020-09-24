#include<bits/stdc++.h>

using namespace std;
const int N = 420;
int f[N][N], g[N][N], s[N], n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) s[n + i] = s[i];
    for (int i = 1; i <= 2*n; i++) s[i] += s[i - 1];
    
    memset(f, 0x3f, sizeof f);
    memset(g, -0x3f, sizeof g);
    for (int len = 1; len <= 2*n; len++) {
        for (int ll = 1; ll + len - 1 <= 2*n; ll++) {
            int rr = ll + len - 1;
            for (int k = ll; k <= rr; k++) {
                if (ll == rr) {
                    g[ll][rr] = f[ll][rr] = 0;
                    break;
                }
                f[ll][rr] = min(f[ll][rr], f[ll][k] + f[k + 1][rr] + s[rr] - s[ll - 1]);
                g[ll][rr] = max(g[ll][rr], g[ll][k] + g[k + 1][rr] + s[rr] - s[ll - 1]);
            }
        }
    }
    int minv = 0x3f3f3f3f, maxv = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        minv = min(minv, f[i][i + n - 1]);
        maxv = max(maxv, g[i][i + n - 1]);
    }
    cout << minv << endl << maxv << endl;
    
    
    return 0;
}
