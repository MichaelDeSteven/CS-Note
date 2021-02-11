#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
LL n, d, x, y, u, v;

LL exgcd(LL a, LL b, LL &u, LL &v) {
    if (!b) {
        u = 1, v = 0;
        return a;
    }
    LL x1 = u, y1 = v;
    LL gcd = exgcd(b, a % b, x1, y1);
    u = y1, v = x1 - a / b * y1;
    return gcd;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> d >> x >> y;
        LL gcd = exgcd(d, n, u, v);
        if ((y - x) % gcd) cout << "Impossible" << endl;
        else {
            u *= (y - x) / gcd;
            n /= gcd;
            cout << ((u % n) + n) % n << endl;
        }
    }
    return 0;
}
