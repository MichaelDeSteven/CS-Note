#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N = 50010, M = 1e6;
typedef pair<int, int> PII;
int d[7][7], n, m, dist[N], st[N], list[7];
int e[M], ne[M], w[M], h[M], inx;

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++; 
}

void dijkstra(int S, int E) {
    memset(dist, 0x3f, sizeof dist);
    memset(st, 0, sizeof st);
    dist[list[S]] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, list[S]});

    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        int ver = t.second, distant = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distant + w[i]) {
                dist[j] = distant + w[i];
                q.push({dist[j], j});
            }
        }
    }
    d[S][E] = d[E][S] = dist[list[E]];
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    list[1] = 1;
    for (int i = 2; i <= 6; i++) cin >> list[i];
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z), add(y, x, z);
    }
    
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= i; j++)
            if (i != j) dijkstra(i, j);
    
    int res = 0x3f3f3f3f;
    int tmp[7] = {0, 1, 2, 3, 4, 5, 6};
    do {
        int ans = 0;
        for (int i = 2; i < 7; i++) ans += d[tmp[i - 1]][tmp[i]];
        res = min(res, ans);
    } while (next_permutation(tmp + 2, tmp + 7));
    
    cout << res << endl;
    return 0;
}
