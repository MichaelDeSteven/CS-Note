#include<bits/stdc++.h>

using namespace std;
const int N = 10010, M = 2*N;
int e[M], ne[M], h[M], w[M], inx;
int n, d[N];

void add(int a, int b, int c) {
    e[inx] = b, w[inx] = c, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa, int val) {
    d[u] = val;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u, val + w[i]);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    int u = 0;
    dfs(1, -1, 0);
    for (int i = 1; i <= n; i++)
        if (d[u] < d[i]) u = i;
        
    dfs(u, -1, 0);
    for (int i = 1; i <= n; i++)
        if (d[u] < d[i]) u = i;
        
    cout << d[u] << endl;
    
    return 0;
}
