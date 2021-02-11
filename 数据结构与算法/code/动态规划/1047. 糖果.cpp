#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N][N], n, k, v;
// f[i][j] 表示从前i件物品拿走若干件物品的所有方案中总数最多且总数s % k = j
// f[i][j] = max{f[i - 1][j], f[i - 1][(((j - v) % k) + k) % k]}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        for (int j = 0; j < k; j++) {
            f[i][j] = f[i - 1][j];
            int x = ((j - v) % k + k) % k;
            if ((f[i - 1][x] + v) % k == j) f[i][j] = max(f[i][j], f[i - 1][x] + v);
        }
    }
    
    cout << f[n][0] << endl;
}
