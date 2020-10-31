#include<bits/stdc++.h>

using namespace std;
const int N = 110, M = N * N;
int n;
int e[M], ne[M], h[M], inx;
int dfn[N], low[N], scc_cnt, cnt;
stack<int> stk;
int id[N], instk[N];
int ind[N], outd[N];
vector<int> com[N];

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
        ++scc_cnt;
        int t;
        do {
            t = stk.top();
            stk.pop();
            instk[t] = false;
            id[t] = scc_cnt;
            com[scc_cnt].push_back(t);
        } while (t != u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x, x) add(i, x);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    
    for (int i = 1; i <= n; i++) {
        for (int j = h[i]; j != -1; j = ne[j]) {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a != b) ind[b]++, outd[a]++;
        }
    }
    int sum = 0, start = 0, end = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!ind[i]) start++;
        if (!outd[i]) end++;
    }
    cout << start << endl << (scc_cnt == 1 ? 0 : max(start, end)) << endl;
    
    return 0;
}
