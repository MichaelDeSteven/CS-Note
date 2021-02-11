#include<bits/stdc++.h>

using namespace std;
const int N = 100010, p = 1e9 + 7;
typedef long long LL;
LL fact[N], inv[N], n, a, b;

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
    fact[0] = 1, inv[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = (fact[i - 1] * i) % p;
        inv[i] = (inv[i - 1] * qmi(i, p - 2)) % p;
    }
    
    cin >> n;
    
    while (n--) {
        cin >> a >> b;
        cout << ((fact[a] * inv[b] % p) * inv[a - b]) % p << endl;
    }
    
    return 0;
}
