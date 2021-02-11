#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 2010;
int n, m, idg[N], st[N], dist[N], res[N], cnt;
int e[N*N], ne[N*N], w[N*N], h[N*N], inx;

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

int topsort() {
    queue<int> q;
    for (int i = 1; i <= n + m; i++) if (!idg[i]) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        res[++cnt] = t;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--idg[j] == 0) q.push(j);
        }
    }
    return cnt == n + m;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int t;
        cin >> t;
        int start = n, end = 1;
        memset(st, 0, sizeof st);
        for (int j = 1; j <= t; j++) {
            int x;
            cin >> x;
            start = min(start, x);
            end = max(end, x);
            st[x] = true;
        }
        int ver = i + n;
        for (int j = start; j <= end; j++) {
            if (!st[j]) {
                add(j, ver, 0);
                idg[ver]++;
            } else {
                add(ver, j, 1);
                idg[j]++;
            }
        }
    }
    topsort();
    int ans = 0;
    for (int i = 1; i <= n; i++) dist[i] = 1;
    for (int i = 1; i <= n + m; i++) {
        for (int j = h[res[i]]; j != -1; j = ne[j]) {
            int t = e[j];
            dist[t] = max(dist[t], dist[res[i]] + w[j]); 
        }
    }
    
    for (int i = 1; i <= n; i++) ans = max(ans, dist[i]);
    cout << ans << endl;
    return 0;
}

// 邻接矩阵写法
#include<bits/stdc++.h>

using namespace std;
const int N = 1010, M = 1e6;
int g[N][N];
int st[N], is[N], indeg[N], n, m;

void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (!indeg[i]) q.push(i);
        
    int cnt = 0;
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            for (int j = 1; j <= n; j++) {
                if (g[t][j]) {
                    g[t][j] = 0;
                    if (--indeg[j] == 0) q.push(j);
                }
            }
        }
        cnt++;
    }
    cout << cnt << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int t, k;
        scanf("%d", &t);
        memset(is, 0, sizeof is);
        for (int j = 1; j <= t; j++) {
            scanf("%d", &k);
            st[j] = k, is[k] = true;
        }
        
        for (int j = st[1]; j <= st[t]; j++) {
            if (!is[j]) {
                for (int k = 1; k <= t; k++) {
                    if (!g[st[k]][j]) {
                        g[st[k]][j] = 1;
                        indeg[j]++;
                    }
                }
            }
        }
    }
    
    topsort();
    
    return 0;
    
}
