#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long LL;
int main() {
    LL a, b, p;
    cin >> a >> b >> p;
    LL res = 1, base = a;
    while (b) {
        if (b & 1) res = (res * base) % p;
        base = (base * base) % p;
        b >>= 1;
    }
    cout << res % p << endl;
    return 0;
}
