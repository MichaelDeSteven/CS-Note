#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
typedef long long LL;
int e[N], ne[N], h[N], inx;
LL w[N], n, f[N];

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    LL res = w[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        if (f[j] > 0) res += f[j];
    }
    f[u] = res;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs(1, -1);
    
    LL res = -1e7;
    for (int i = 1; i <= n; i++)
        res = max(res, f[i]);
        
    cout << res << endl;
    
    return 0;
}
