#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N][N], n, s, a, b;
/*
记操作集合为G = {a, b}

x + G + x + 2G + x + ... + (n - 1)G + x = s
由于后一项是由前一项增加a或者减少b操作得来的，因此将相同的操作合并 
nx + G + 2G + ... + (n - 1)G = s
nx = s - (G + 2G + ... + (n - 1)G)
记m = (G + 2G + ... + (n - 1)G)
nx = s - m，x为任意整数则s与m对模n同余x
f(i, j)表示前i项和模n同余j的所有方案数
*/
int main() {
    cin >> n >> s >> a >> b;
    f[0][0] = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f[i][j] = (f[i - 1][((j - a) % n + n) % n] + f[i - 1][(j + b) % n]) % 100000007;
        }
    }
    
    cout << f[n - 1][((s % n) + n) % n] << endl;
    return 0;
}
