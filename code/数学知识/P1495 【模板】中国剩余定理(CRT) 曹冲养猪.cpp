#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 11;
int a[N], m[N], n;
LL M = 1, res = 0, x, y;

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
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> m[i] >> a[i];
        M *= m[i];     
    }
    
    for (int i = 1; i <= n; i++) {
        LL Mi = M / m[i];
        LL d = exgcd(Mi, m[i], x, y);
        LL t = (x / d + m[i]) % m[i];
        res = (res + a[i] * Mi * t) % M;
    }
    
    cout << res << endl;
    
    return 0;
}
