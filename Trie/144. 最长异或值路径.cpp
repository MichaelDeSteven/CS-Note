#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 100010, M = 5e6;
int n, d[N]; // d[i]表示根节点到i路径的异或值, d[i]^d[j]表示
int son[M][2], cnt[M], inx;
int ne[2*N], e[2*N], w[2*N], h[2*N], idx;

void add(int a, int b, int c) {
    w[idx] = c, e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int fa, int u, int val) {
    d[u] = d[fa] ^ val;
    
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (d[j] == -1) {
            dfs(u, j, w[i]);
        }
    }
}

void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1;
        if (!son[p][u]) son[p][u] = ++inx;
        p = son[p][u];
    }
    cnt[p]++;
}

int find(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int u = x >> i & 1;
        if (son[p][!u]) {
            res += 1 << i;
            p = son[p][!u];
        } else {
            p = son[p][u];
        }
    }
    return res;
}


int main() {
    cin >> n;
    memset(d, -1, sizeof d);
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    d[0] = 0;
    dfs(0, 0, 0);
    for (int i = 0; i < n; i++) insert(d[i]);
    
    int res = 0;
    for (int i = 0; i < n; i++) {
        res = max(res, find(d[i]));
    }
    
    cout << res << endl;
    return 0;
}
