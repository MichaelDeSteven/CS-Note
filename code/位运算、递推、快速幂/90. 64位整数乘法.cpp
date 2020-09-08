#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
typedef long long LL;
LL a, b, p;

int main() {
    cin >> a >> b >> p;
    LL res = 0;
    a %= p, b %= p;
    while (b) {
        if (b & 1) res = (res + a) % p;
        b >>= 1, a = (a << 1) % p;
    }
    
    cout << res << endl;
    return 0;
}
