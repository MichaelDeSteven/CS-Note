#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 2e5 + 10, p = 1e9 + 7;

LL fact[N], inv[N], n;

LL qmi(LL u, LL v) {
    LL res = 1;
    while (v) {
        if (v & 1) res = (res * u) % p;
        u = (u * u) % p;
        v >>= 1;
    }
    return res;
}

int main() {
    cin >> n;
    
    fact[0] = inv[0] = 1;
    for (int i = 1; i <= 2*n; i++) {
        fact[i] = (fact[i - 1] * i) % p;
        inv[i] = (inv[i - 1] * qmi(i, p - 2)) % p;
    }
    
    cout <<  (((fact[2 * n] * inv[n]) % p) * inv[n + 1]) % p << endl;
    return 0;
}
