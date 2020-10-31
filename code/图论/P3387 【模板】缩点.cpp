#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct node {
    int a, b;
} edg[N];
int e[N], ne[N], h[N], inx;
int dfn[N], low[N], instk[N], cnt, scc_cnt;
stack<int> stk;
int n, m, w[N];
int all[N], ind[N], f[N], id[N];
// 已知拓扑序
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    stk.push(u);
    instk[u] = true;
    
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (instk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }
    
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int t;
        do {
            t = stk.top();
            stk.pop();
            id[t] = scc_cnt;
            instk[t] = false;
            all[scc_cnt] += w[t];
        } while (t != u);
    }
}

void topsort() {
    int res = 0;
    queue<int> q;
    for (int i = 1; i <= scc_cnt; i++)
        if (!ind[i]) {
            q.push(i);
            f[i] = all[i];
        }
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            for (int j = h[t]; j != -1; j = ne[j]) {
                int k = e[j];
                if (--ind[k] == 0) q.push(k);
                f[k] = max(f[k], f[t] + all[k]);
            }
        }
    }
    
    for (int i = 1; i <= scc_cnt; i++) res = max(res, f[i]);
    cout << res << endl;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        edg[i] = {a, b};
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    
    inx = 0;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b;
        if (id[a] != id[b]) {
            ind[id[b]]++;
            add(id[a], id[b]);
        }
    }
    
    topsort();
    return 0;
}
