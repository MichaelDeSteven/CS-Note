#include<bits/stdc++.h>

using namespace std;
const int N = 20010;

int f[N], m, n, v;
// f[i]表示体积为i的箱子能塞多大体积物品

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        for (int j = m; j >= v; j--)
            f[j] = max(f[j], f[j - v] + v);
    }
    cout << m - f[m] << endl;
    return 0;
}
