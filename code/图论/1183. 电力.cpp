#include<bits/stdc++.h>

using namespace std;
const int N = 300010;
int e[N], ne[N], h[N], inx;
int dfn[N], low[N], cnt, dcc;
int root;
int block[N];
int n, m;
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;    
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    int flag = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        ++flag;
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if (low[j] >= dfn[u]) {
                dcc++;
                block[u]++;
            }
        } else {
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (u != root) block[u]++;
}

int main() {
    while (cin >> n >> m) {
        if (!n && !m) break;
        memset(h, -1, sizeof h);
        inx = 0;
        for (int i = 1; i <= m; i++) {
            int a, b;
            cin >> a >> b;
            add(a, b), add(b, a);
        }
        cnt = 0, dcc = 0;
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        memset(block, 0, sizeof block);
        int tot = 0;
        for (int i = 0; i < n; i++)
            if (!dfn[i]) {
                root = i;
                tarjan(i);
                tot++;
            }
        int res = 0;
        for (int i = 0; i < n; i++)
            res = max(res, tot + block[i] - 1);
            
        cout << res << endl;
    }
    return 0;
}
