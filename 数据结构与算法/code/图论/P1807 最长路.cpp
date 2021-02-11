#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 1510, M = 1e5 + 10;
int e[M], ne[M], h[M], w[M], inx;
int n, m, indeg[N];
LL f[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        f[i] = -1e9;
    f[1] = 0;
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) q.push(i);
    }
    
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            for (int j = h[t]; j != -1; j = ne[j]) {
                int k = e[j];
                f[k] = max(f[k], f[t] + w[j]);
                if (--indeg[k] == 0) q.push(k);
            }
        }
    }
    
    if (f[n] == -1e9) cout << -1 << endl;
    else cout << f[n] << endl;
}

int main() {
    memset(h, -1, sizeof h);
    
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        indeg[b]++;
    }
    
    topsort();
    
    return 0;
}
