#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
LL a, b, p, fact[N], inv[N];

LL qmi(LL u, LL v) {
    LL res = 1;
    while (v) {
        if (v & 1) res = (res * u) % p;
        u = (u * u) % p;
        v >>= 1;
    }
    return res;
}

LL C(LL a, LL b, LL p) {
    LL res = 1;
    for (int i = 1, j = a; i <= b; j--, i++) {
        res = (res * j) % p;
        res = (res * qmi(i, p - 2)) % p;
    }
    return res;
}

LL lucas(LL a, LL b, LL p) {
    if (a < p && b < p) return C(a, b, p) % p;
    return (C(a % p, b % p, p) * lucas(a / p, b / p, p)) % p;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b >> p;
        cout << lucas(a, b, p) << endl;
    }
    
    return 0;
}
