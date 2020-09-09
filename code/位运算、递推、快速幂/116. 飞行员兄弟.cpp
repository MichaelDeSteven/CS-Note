#include<bits/stdc++.h>

using namespace std;
const int N = 10;
int g[N][N], backup[N][N];
int n, res = 20, ways;

// 每个开关按0次或1次，两次等于没按因此无意义
// 用位运算枚举每个开关按或不按，按从小到大枚举则符合题目所说的优先级
void open(int u, int v) {
    for (int j = 1; j <= 4; j++) g[u][j] ^= 1, g[j][v] ^= 1;
    g[u][v] ^= 1;
}

void solve(int way) {
    memcpy(g, backup, sizeof g);
    int cnt = 0, t = way;
    for (int i = 1; i <= 16; i++) {
        if (way & 1) {
            int u = (i - 1) / 4, v = (i - 1) % 4;
            open(u + 1, v + 1);
            cnt++;
        }
        way >>= 1;
    }    
    bool flag = true;
    for (int i = 1; i <= 4; i++)
        for (int j = 1; j <= 4; j++)
            if (!g[i][j]) flag = false;
    if (flag && res > cnt) res = cnt, ways = t;
}

int main() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            char c;
            cin >> c;
            if (c == '-') g[i][j] = 1;
            else g[i][j] = 0;
        }
    }
    memcpy(backup, g, sizeof g);
    for (int i = 0; i < 1 << 16; i++) solve(i);
    
    cout << res << endl;
    for (int i = 1; i <= 16; i++) {
        if (ways & 1) {
            int u = (i - 1) / 4, v = (i - 1) % 4;
            cout << u + 1 << ' ' << v + 1 << endl;
        }
        ways >>= 1;
    }
    return 0;
}
