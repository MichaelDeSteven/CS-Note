#include<bits/stdc++.h>

using namespace std;
const int N = 12, M = 1 << N;
typedef long long LL;
LL f[N][M], h[M], n, m;

int main() {
    while (cin >> n >> m, n && m) {
        memset(h, 0, sizeof h);
        memset(f, 0, sizeof f);
        for (int stat = 0; stat < (1 << n); stat++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (stat >> j & 1) {
                    if (cnt % 2) h[stat] = true;
                } else {
                    cnt++;
                }
            }
            if (cnt % 2) h[stat] = true;
        }

        f[0][0] = 1;
        for (int i = 1; i <= m; i++) {
            for (int stat = 0; stat < (1 << n); stat++) {
                for (int t = 0; t < (1 << n); t++) {
                    if ((stat & t) || h[stat | t]) continue;
                    f[i][stat] += f[i - 1][t]; 
                }
            }
        }
        cout << f[m][0] << endl;
    }
    
    return 0;
}
