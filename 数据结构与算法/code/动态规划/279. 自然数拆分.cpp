#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL MOD = 2147483648;
const int N = 4010;
LL f[N], n;
// f[j]表示凑成j的方案数，f[j] += f[j - i]
int main() {
    cin >> n;
    f[0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = i; j <= n; j++) 
            f[j] = (f[j] + f[j - i]) % MOD;
    }
    cout << f[n] << endl;
    
    return 0;
}
