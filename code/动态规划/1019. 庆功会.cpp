#include<bits/stdc++.h>

using namespace std;
const int N = 6010;
int f[N], g[N], n, m, v, w, s;
int q[N], hh, tt;

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> v >> w >> s;
        memcpy(g, f, sizeof f);
        for (int j = 0; j < v; j++) {
            int hh = 0, tt = -1;
            for (int k = j; k <= m; k += v) {
                if (tt >= hh && q[hh] < k - s * v) hh++;
                while (tt >= hh && g[q[tt]] - (q[tt] - j) / v * w <= g[k] - (k - j) / v * w) tt--;
                q[++tt] = k;
                f[k] = max(f[k], g[q[hh]] + (k - q[hh]) / v * w);
            }
        }
    }
    cout << f[m] << endl;
    
    return 0;
}
