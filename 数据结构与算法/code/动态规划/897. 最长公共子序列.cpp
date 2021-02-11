#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N][N], n, m;
char a[N], b[N];
/*
a1...i,b1...j中的最长公共子序列
*/
int main() {
    cin >> n >> m;
    cin >> a + 1 >> b + 1;
    
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            f[i][j] = max(f[i][j - 1], f[i - 1][j]);
            if (a[i] == b[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
        
    cout << f[n][m] << endl;
    return 0;
}
