#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 10, M = 1e5 + 10;
int e[N], ne[N], h[N], inx;
int n, m, x;
int dfn[M], low[M], cnt, scc;
stack<int> stk;
int instk[M];
int com[M];
int ind[M], outd[M], id[M];
int f[M], cnn[M];
vector<int> g[M];
unordered_map<int, int> ma;
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
    
    if (low[u] == dfn[u]) {
        scc++;
        int y;
        do {
            y = stk.top();
            stk.pop();
            instk[y] = false;
            id[y] = scc;
            com[scc]++;
        } while (y != u);
    } 
}

void topsort() {
    queue<int> q;
    int res = 0;
    for (int i = 1; i <= scc; i++)
        if (!ind[i]) {
            f[i] = com[i];
            cnn[i] = 1;
            q.push(i);
            res = max(res, com[i]);
        }
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            for (auto k : g[t]) {
                if (--ind[k] == 0) q.push(k);
                if (f[k] < com[k] + f[t]) {
                    cnn[k] = cnn[t];
                    f[k] = com[k] + f[t];
                    res = max(f[k], res);
                } else if (f[k] == com[k] + f[t]) {
                    cnn[k] = (cnn[k] + cnn[t]) % x;
                }
            }
        }
    }
    
    int tot = 0;
    for (int i = 1; i <= scc; i++)
        if (res == f[i]) tot = (tot + cnn[i]) % x;
    cout << res << endl << tot << endl;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m >> x;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
        
    for (int i = 1; i <= n; i++) {
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            if (id[i] == id[k]) continue;
            int hash = id[i] * N + id[k];
            if (!ma.count(hash)) {
                ma[hash]++;
                ind[id[k]]++, outd[id[i]]++;
                g[id[i]].push_back(id[k]);
            }
        }
    }
    
    topsort();
    return 0;
}
