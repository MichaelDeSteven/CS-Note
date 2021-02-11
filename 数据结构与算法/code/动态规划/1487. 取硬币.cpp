#include<bits/stdc++.h>

using namespace std;
const int N = 100010, MOD = 1e9 + 7;

int f[N], n1, n2, m, x;

int main() {
    cin >> n1 >> n2 >> m;
    f[0] = 1;
    for (int i = 1; i <= n1; i++) {
        cin >> x;
        for (int j = x; j <= m; j++)
            f[j] = (f[j] + f[j - x]) % MOD;
    }
    
    for (int i = 1; i <= n2; i++) {
        cin >> x;
        for (int j = m; j >= x; j--)
            f[j] = (f[j] + f[j - x]) % MOD;
    }
    
    cout << f[m] << endl;
    
    
    return 0;
}
