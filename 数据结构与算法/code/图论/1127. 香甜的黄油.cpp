#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>

using namespace std;
const int N = 810, M = 5000;
#define INF 0x3f3f3f3f
int dist[N], st[N], n, m, k, cnt[N];
int e[M], ne[M], h[M], w[M], inx;

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}
int spfa(int s) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    st[s] = true;
    
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > dist[t] + w[i]) {
                dist[j] = dist[t] + w[i];
                
                if (!st[j]) {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    
    int res = 0;
    for (int i = 1; i <= k; i++) {
        if (dist[cnt[i]] == INF) return INF;
        res += dist[cnt[i]];
    }
    return res;
}
int main() {
    cin >> k >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        cnt[i] = x;
    }
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    int res = INF;
    for (int i = 1; i <= n; i++) res = min(res, spfa(i));
    
    cout << res << endl;
    return 0;
}
