#include<bits/stdc++.h>

using namespace std;
const int N = 1010, M = 510;
int f[N][M], n, m, k, v, w, c, r;
// f[i][j]表示一共有i个精灵球，皮卡丘受到的伤害不超过j能收服的最大精灵数
int main() {
    cin >> n >> m >> k;
    while (k--) {
        cin >> v >> w;
        for (int i = n; i >= v; i--)
            for (int j = m; j >= w; j--)
                f[i][j] = max(f[i][j], f[i - v][j - w] + 1);
    }
    
    c = f[n][m - 1];
    for (int j = 0; j < m; j++)
        if (c == f[n][j]) {
            r = j;
            break;
        }
        
    cout << c << ' ' << m - r << endl;
    
    return 0;
}
