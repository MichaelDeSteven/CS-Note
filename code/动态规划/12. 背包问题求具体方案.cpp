#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N][N], n, m, v[N], w[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> v[i] >> w[i];
    for (int i = n; i >= 1; i--) {
        for (int j = 0; j <= m; j++) {
            f[i][j] = f[i + 1][j];
            if (j >= v[i]) f[i][j] = max(f[i][j], f[i + 1][j - v[i]] + w[i]);
        }
    }
    
    int i = 1, j = m;
    while (i <= n) {
        if (j >= v[i] && f[i][j] == f[i + 1][j - v[i]] + w[i]) {
            cout << i << ' ';
            j -= v[i];
        }
        i++;
    }
    return 0;
}
