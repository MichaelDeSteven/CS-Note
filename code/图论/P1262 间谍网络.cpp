#include<bits/stdc++.h>

using namespace std;
const int N = 1e5;
int e[N], ne[N], h[N], inx;
int n, p, r, w[N];
int dfn[N], low[N], cnt, scc_cnt;
vector<int> com[N];
stack<int> stk;
int instk[N], id[N], ind[N];

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
        int y;
        do {
            y = stk.top();
            stk.pop();
            id[y] = scc_cnt;
            com[scc_cnt].push_back(y);
            instk[y] = false;
        } while (y != u);
    }
}

int main() {
    memset(w, -1, sizeof w);
    memset(h, -1, sizeof h);
    cin >> n >> p;
    for (int i = 1; i <= p; i++) {
        int a, b;
        cin >> a >> b;
        w[a] = b;
    }
    cin >> r;
    for (int i = 1; i <= r; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i); 

    for (int i = 1; i <= n; i++) {
        for (int j = h[i]; j != -1; j = ne[j]) {
            if (id[i] == id[e[j]]) continue;            // 在同一个强连通分量
            int k = e[j], num = id[k];
            ind[num]++;
        }
    }
    
    int res = 0, a = -1;
    bool flag = true;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!ind[i]) {
            int val = -1;
            for (auto t : com[i]) {
                if (w[t] != -1) {
                    if (val == -1 || w[t] < val) val = w[t];
                }
                if (w[t] == -1 && (a == -1 || t < a)) a = t;
            }
            if (val == -1) flag = false;
            else res += val;
        } else {
            
        }
    }
    if (flag) cout << "YES" << endl << res << endl;
    else cout << "NO" << endl << a << endl;
    return 0;
}
