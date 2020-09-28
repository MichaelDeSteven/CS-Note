#include<bits/stdc++.h>

using namespace std;
const int N = 110, M = 1 << 11;
int g[N], n, m, f[3][3][M][M];
int h1[N][M], h2[M], ma[M];
// h1[i][j]表示第i行状态为j是否合法，h2表示多个状态与运算是否为1， ma统计某状态下1的数量

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int v = 0;
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            if (c == 'H') v += 1 << j;
        }
        g[i] = v;
    }
    
    for (int stat = 0; stat < (1 << m); stat++) {
        int cnt = 2, tot = 0;
        for (int j = 0; j < m; j++) {
            if (stat >> j & 1) {
                tot++;
                if (cnt < 2) h2[stat] = true; 
                cnt = 0;
            } else {
                cnt++;
            }
        }
        for (int i = 1; i <= n; i++) {
            if (g[i] & stat) h1[i][stat] = true;
        }
        ma[stat] = tot;
    }
    
    for (int st1 = 0; st1 < (1 << m); st1++) {
        if (h1[1][st1]) continue;
        f[1 % 3][0 % 3][st1][0] = ma[st1];
    }
    
    int res = 0;
    
    for (int i = 2; i <= n; i++) {
        for (int st1 = 0; st1 < (1 << m); st1++) {
            if (h1[i][st1] || h2[st1]) continue;
            for (int st2 = 0; st2 < (1 << m); st2++) {
                if (h1[i - 1][st2] || st1 & st2 || h2[st2]) continue;
                for (int st3 = 0; st3 < (1 << m); st3++) {
                    if (h1[i - 2][st3] || st1 & st2 || st1 & st3 || h2[st3]) continue;
                    f[i % 3][(i - 1) % 3][st1][st2] = max(f[i % 3][(i - 1) % 3][st1][st2], 
                        f[(i - 1) % 3][(i - 2) % 3][st2][st3] + ma[st1]);
                    res = max(res, f[i % 3][(i - 1) % 3][st1][st2]);
                }
            }
        }
    }
    
    cout << res << endl;
    
    return 0;
}
