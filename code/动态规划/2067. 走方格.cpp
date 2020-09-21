#include<bits/stdc++.h>

using namespace std;
const int N = 35;
int n, m, f[N][N];
int main() {
    cin >> n >> m;
    f[0][1] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (i % 2 || j % 2) f[i][j] = f[i - 1][j] + f[i][j - 1];
            
    cout << f[n][m] << endl;
    return 0;
}
