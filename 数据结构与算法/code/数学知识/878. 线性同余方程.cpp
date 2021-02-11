#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
int a, b, m, x, y;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    int x1 = x, y1 = y;
    int d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b >> m;
        int z = exgcd(a, m, x, y);
        if (b % z == 0) cout << (LL)x * b / z % m << endl;
        else cout << "impossible" << endl;
    }
    return 0;
}
