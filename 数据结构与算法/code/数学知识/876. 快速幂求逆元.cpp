#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
int n, p;

int qmi(int n, int p) {
    LL base = n, res = 1, mod = p + 2;
    while (p) {
        if (p & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> p;
        if (n % p == 0) cout << "impossible" << endl;
        else cout << qmi(n, p - 2) << endl;
    }
    return 0;
}
