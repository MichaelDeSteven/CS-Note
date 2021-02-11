#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
LL a, b, p;

void get() {
    LL base = a, t = b, res = 1;
    while (t) {
        if (t & 1) res = (res * base) % p;
        base = (base * base) % p;
        t >>= 1;
    }
    cout << res % p << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b >> p;
        get();
    }
    return 0;
}
