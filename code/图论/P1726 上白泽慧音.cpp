#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
int e[N], ne[N], h[N], inx;
int dfn[N], low[N], cnt, scc_cnt;
stack<int> stk;
int instk[N];
vector<int> com[N];
int n, m;

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
        } else if (instk[j]) low[u] = min(low[u], dfn[j]);
    }
    
    if (dfn[u] == low[u]) {
        scc_cnt++;
        int y;
        do {
            y = stk.top();
            stk.pop();
            instk[y] = false;
            com[scc_cnt].push_back(y);
        } while (y != u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b);
        if (c == 2) add(b, a);
    }
    
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    
    int maxv = 0, inx = -1;
    for (int i = 1; i <= scc_cnt; i++) {
        int sz = com[i].size();
        maxv = max(maxv, sz);
        sort(com[i].begin(), com[i].end());
    }
    
    for (int i = 1; i <= scc_cnt; i++) {
        if (com[i].size() == maxv && (inx == -1 || com[i][0] < com[inx][0])) inx = i;
    }
    cout << maxv << endl;
    for (auto t : com[inx]) cout << t << ' '; 
    return 0;
}
