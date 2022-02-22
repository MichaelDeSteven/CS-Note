#include<bits/stdc++.h>

using namespace std;
const int N = 20, M = 1 << N;
int f[N][M], g[N][N], n;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> g[i][j];

    memset(f, 0x3f, sizeof f);
    f[0][1] = 0;
    
    for (int stat = 0; stat < (1 << n); stat++) {
        for (int i = 0; i < n; i++) {
            if (((stat >> i) & 1) == 0) continue;
            for (int j = 0; j < n; j++) {
                if ((stat >> j) & 1) {
                    f[i][stat] = min(f[i][stat], f[j][stat - (1 << i)] + g[j][i]);
                }
            }
        }
    }
    
    int res = 0x3f3f3f3f;
    for (int i = 0; i < n; i++) {
        res = min(res, f[i][(1 << n) - 1] + g[i][0]);
    }
    cout << res << endl;
    
    return 0;
}
