#include<bits/stdc++.h>

using namespace std;
const int N = 2010;
int n, m, v, w, s;
int V[100*N], W[100*N], cnt, f[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v >> w >> s;
        if (v > m) continue;
        int base = 1;
        while (s) {
            V[++cnt] = v * base, W[cnt] = w * base, s -= base;
            base <<= 1;
            if (s < base) base = 1;
        }
    }

    for (int i = 1; i <= cnt; i++)
        for (int j = m; j >= V[i]; j--)
            f[j] = max(f[j], f[j - V[i]] + W[i]);
    
    cout << f[m] << endl;
    return 0;
}
