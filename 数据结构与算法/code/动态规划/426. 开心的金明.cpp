#include<bits/stdc++.h>

using namespace std;
const int N = 30010;
int f[N], n, m, v, p;

int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> v >> p;
        for (int j = m; j >= v; j--) f[j] = max(f[j], f[j - v] + v*p);
    }
    cout << f[m] << endl;
    return 0;
}
