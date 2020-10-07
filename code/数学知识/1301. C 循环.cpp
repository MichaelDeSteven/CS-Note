#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
LL A, B, C, k, x, y;

LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    LL x1 = x, y1 = y;
    LL d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}
int main() {
    while (cin >> A >> B >> C >> k) {
        if (!(A + B + C + k)) break;
        k = (1ll << k);
        LL d = exgcd(C, k, x, y);
        if ((B - A) % d) cout << "FOREVER" << endl;
        else {
            x = x * (B - A) / d;
            k /= d;
            cout << ((x % k) + k) % k << endl;
        }
    }
    
    return 0;
}
