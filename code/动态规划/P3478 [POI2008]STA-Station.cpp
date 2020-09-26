#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 2e6 + 10;
int e[N], ne[N], h[N], inx;
int n;
LL f[N], dep[N], sz[N];  // f[i][0]表示以i为根节点的深度和
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs1(int u, int fa) {
    sz[u] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dep[j] = dep[u] + 1;
        dfs1(j, u);
        sz[u] += sz[j];
    }
}

void dfs2(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        f[j] = f[u] - sz[j] + n - sz[j];
        dfs2(j, u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs1(1, -1);
    for (int i = 1; i <= n; i++) f[1] += dep[i];
    dfs2(1, -1);
    
    LL res = -0x3f3f3f3f;
    int idx = -1;
    for (int i = 1; i <= n; i++) {
        if (res < f[i]) {
            res = f[i];
            inx = i;
        }
    }
    
    cout << inx << endl;
    return 0;
}
