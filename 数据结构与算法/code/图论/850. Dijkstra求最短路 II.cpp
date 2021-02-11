#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1e6;
typedef pair<int, int> PII;
#define INF 0x3f3f3f3f
int e[N], ne[N], w[N], h[N], inx;
int n, m, st[N], dist[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    dist[1] = 0;
    q.push({0, 1});

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
    if (dist[n] == INF) cout << "-1" << endl;
    else cout << dist[n] << endl;
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add(x, y, z);
    }
    dijkstra();
    
    return 0;
}
