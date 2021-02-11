#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 5010, M = 1e6 + 10, MOD = 80112002;
int e[M], ne[M], h[M], inx;
int n, m, indeg[N], outdeg[N];
LL f[N];

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) {
            q.push(i);
            f[i] = 1;
        }
    }
    
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            for (int j = h[t]; j != -1; j = ne[j]) {
                int k = e[j];
                f[k] = (f[k] + f[t]) % MOD;
                if (--indeg[k] == 0) q.push(k);
            }
        }
    }
    
    LL res = 0;
    for (int i = 1; i <= n; i++)
        if (!outdeg[i])
            res = (res + f[i]) % MOD;
    cout << res << endl;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b);
        indeg[b]++, outdeg[a]++;
    }
    
    topsort();
    
    return 0;
}
