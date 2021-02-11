#include<bits/stdc++.h>

using namespace std;
const int N = 5010, MOD = 1e9 + 7, M = 8200;
int f[2][M], n, v;
// f[j] 表示前i个数组成的所有集合中，异或和为j的子集数
// 选a，f[i - 1][j^a]，不选a，f[i - 1][j]
// f[j ^ a] = (f[j] + f[j ^ a]) % MOD

bool is_prime(int x) {
    for (int i = 2; i < x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

int main() {
    cin >> n;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        for (int j = 0; j < M; j++) {
            f[i & 1][j] = f[(i - 1) & 1][j];
            if ((j ^ v) < M) f[i & 1][j] = (f[(i - 1) & 1][j^v] + f[i & 1][j]) % MOD;
        }
    }
    
    int res = 0;
    for (int i = 2; i < M; i++) {
        if (is_prime(i)) res = (res + f[n & 1][i]) % MOD;
    }
    cout << res << endl;
    return 0;
}
