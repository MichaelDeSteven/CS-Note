#include<bits/stdc++.h>

using namespace std;
const int N = 41, M = 351;
int score[M], type[5], n, m;
int f[N][N][N][N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> score[i];
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        type[x]++;
    }
    f[0][0][0][0] = score[1];
    for (int i = 0; i <= type[1]; i++)
        for (int j = 0; j <= type[2]; j++)
            for (int k = 0; k <= type[3]; k++)
                for (int u = 0; u <= type[4]; u++) {
                    if (!i && !j && !k && !u) continue;
                    int len = i + j*2 + k*3 + u*4;
                    int maxv = f[i][j][k][u];
                    if (i > 0) maxv = max(maxv, f[i - 1][j][k][u]);
                    if (j > 0) maxv = max(maxv, f[i][j - 1][k][u]);
                    if (k > 0) maxv = max(maxv, f[i][j][k - 1][u]);
                    if (u > 0) maxv = max(maxv, f[i][j][k][u - 1]);
                    f[i][j][k][u] = maxv + score[len + 1];
                }
    
    cout << f[type[1]][type[2]][type[3]][type[4]] << endl;
    return 0;
}
