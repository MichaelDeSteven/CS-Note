#include<bits/stdc++.h>

using namespace std;
const int N = 10;

int g[N][N], backup[N][N];
int n, cnt;
// 由于每个开关最多按1次（按两次等于没按）且按的开关与顺序无关
// 因此可以用递推思想，先枚举第一行所有情况并往后逐行设置为全1

void solve() {
    cnt = 10;
    memcpy(backup, g, sizeof g);
    
    for (int i = 0; i < 1 << 5; i++) {
        int res = 0;
        memcpy(g, backup, sizeof g);
        int t = i, j = 5;
        while (j >= 1) {
            if (t & 1) {
                g[1][j] ^= 1, g[2][j] ^= 1, g[1][j - 1] ^= 1, g[1][j + 1] ^= 1;
                res++;
            }
            j--, t >>= 1;
        }
        
        for (j = 2; j <= 5; j++)
            for (int k = 1; k <= 5; k++) {
                if (!g[j - 1][k]) {
                    g[j - 1][k] ^= 1, g[j][k] ^= 1, g[j + 1][k] ^= 1, g[j][k + 1] ^= 1, g[j][k - 1] ^= 1;
                    res++;
                }   
            }
        
        bool flag = true;
        for (j = 1; j <= 5; j++) if (!g[5][j]) flag = false;
        if (flag) cnt = min(cnt, res);
    }
}
int main() {
    cin >> n;
    while (n--) {
        for (int i = 1; i <= 5; i++) 
            for (int j = 1; j <= 5; j++) {
                char c;
                cin >> c;
                if (c == '0') g[i][j] = 0;
                else g[i][j] = 1;
            }
        
        solve();
        if(cnt <= 6) cout << cnt << endl;
        else cout << -1 << endl;
    }
    
    return 0;
}
