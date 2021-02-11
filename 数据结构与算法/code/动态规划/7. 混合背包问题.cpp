#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N], g[N], q[N], v, w, s, n, m;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v >> w >> s;
        if (s == -1) {
            for (int j = m; j >= v; j--) f[j] = max(f[j], f[j - v] + w);
        } else if (s == 0) {
            for (int j = v; j <= m; j++) f[j] = max(f[j], f[j - v] + w);
        } else {
            memcpy(g, f, sizeof f);
            for (int j = 0; j < v; j++) {
                int hh = 0, tt = -1;
                for (int k = j; k <= m; k += v) {
                    if (tt >= hh && q[hh] < k - v * s) hh++;
                    while (tt >= hh && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) tt--;
                    q[++tt] = k;
                    f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w);
                }
            }
        }
    }
    cout << f[m] << endl;
    return 0;
}
