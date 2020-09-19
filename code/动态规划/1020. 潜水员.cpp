#include<bits/stdc++.h>

using namespace std;
const int N = 100;
int f[N][N], n, m, k, a, b, c;
// f[j][k]表示选择前i个气缸满足潜水员工作条件所有方案中重量最低

int main() {
    cin >> n >> m >> k;
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    while (k--) {
        cin >> a >> b >> c;
        for (int i = n; i >= 0; i--)
            for (int j = m; j >= 0; j--)
                f[i][j] = min(f[i][j], f[max(i - a, 0)][max(j - b, 0)] + c);
    }
    
    cout << f[n][m] << endl;
    
    return 0;
}
