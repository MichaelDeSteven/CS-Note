#include<bits/stdc++.h>

using namespace std;
const int N = 3010;
typedef long long LL;
LL f[N], v, n, m;
// f[i][j]表示前i种面值的货币选择若干件，恰好组成面值为j的方案数
int main() {
    cin >> n >> m;
    f[0] = 1;
    for (int i = 0; i < n; i++) {
        cin >> v;
        for (int j = v; j <= m; j++)
            f[j] += f[j - v];
    }
            
    cout << f[m] << endl;
    return 0;
}
