#include<bits/stdc++.h>

using namespace std;
const int N = 10010;
int p[N], n, m, w, c[N], d[N];
int f[N];

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

int main() {
    cin >> n >> m >> w;
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        cin >> c[i] >> d[i];
    }
    
    for (int i = 1; i <= m; i++) {
        int a, b, x, y;
        cin >> a >> b;
        x = find(a), y = find(b);
        if (x != y) {
            c[y] += c[x], d[y] += d[x];
            p[x] = y;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (p[i] != i) continue;
        for (int j = w; j >= c[i]; j--)
            f[j] = max(f[j], f[j - c[i]] + d[i]);
    }
    
    cout << f[w] << endl;
    
    return 0;
    
}
