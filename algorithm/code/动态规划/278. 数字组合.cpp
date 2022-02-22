#include<bits/stdc++.h>

using namespace std;
const int N = 10010;
int f[N], n, m, v;
// f[j]表示前i个数恰好凑成j的方案数
int main() {
    cin >> n >> m;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        for (int j = m; j >= v; j--) f[j] += f[j - v];
    }
    
    cout << f[m] << endl;
    
    return 0;
}
