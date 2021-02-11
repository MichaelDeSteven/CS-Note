#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
struct node {
    int a, b;
} edg[N];
int e[N], ne[N], h[N], inx;
int n, m, cnt, scc_cnt;
int dfn[N], low[N], outd[N], id[N];
int in_stk[N];
stack<int> stk;
int com[N];

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;     
}

void tarjan(int u) {
    dfn[u] = low[u] = ++cnt;
    stk.push(u);
    in_stk[u] = true;
    
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!dfn[j]) {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        } else if (in_stk[j]) {
            low[u] = min(low[u], dfn[j]);
        }
    }
    if (dfn[u] == low[u]) {
        ++scc_cnt;
        int t;
        do {
            t = stk.top();
            stk.pop();
            in_stk[t] = false;
            id[t] = scc_cnt;
            com[scc_cnt]++;
        } while (t != u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        edg[i] = {a, b};
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    // for (int i = 1; i <= n; i++) cout << i << ' ' << dfn[i] << ' ' << low[i] << endl;
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b;
        if (id[a] != id[b]) outd[id[a]]++;
    }
    
    int res = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!outd[i]) {
            if (!res) res = i;
            else {
                cout << 0 << endl;
                return 0;
            }
        }
    }
    cout << com[res] << endl;
    return 0;
}
