#include<bits/stdc++.h>

using namespace std;
const int N = 3010;
int a[N], b[N], f[N][N], n;
/*
    f[i][j]表示a[1...i]与b[1...j]的公共子序列中，以b[j]为结尾的最长公共上升子序列
    不选a[i]，则为f[i - 1][j]
    a[i] == b[j]时，若b[k] < b[j], k < j
    则为f[i - 1][k] + 1
*/
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    
    for (int i = 1; i <= n; i++) {
        int maxv = 1;
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j];
            if (a[i] == b[j]) f[i][j] = max(f[i][j], maxv);
            if (a[i] > b[j]) maxv = max(maxv, f[i - 1][j] + 1);
        }
    }
    
    int res = 0;
    for(int i = 1; i <= n; i++) res = max(res, f[n][i]);
    cout << res << endl;
    return 0;
}
