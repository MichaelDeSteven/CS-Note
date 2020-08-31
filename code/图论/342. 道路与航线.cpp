#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>


using namespace std;
typedef pair<int, int> PII;
#define INF 0x3f3f3f3f
const int N = 25010, M = 50000 * 4;
int e[M], ne[M], w[M], h[M], inx;
int n, r, p, s, st[N], dist[N], bcnt;
vector<int> block[N];
queue<int> q;
int indeg[N], id[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int cnt) {
    id[u] = cnt;
    block[cnt].push_back(u);
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (!id[j]) dfs(j, cnt);
    }
}

void dijkstra(int bid) {
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    for (auto i : block[bid]) heap.push({dist[i], i});
    
    while (!heap.empty()) {
        auto t = heap.top();
        heap.pop();
        
        int ver = t.second, distant = t.first;
        
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distant + w[i]) {
                dist[j] = distant + w[i];
                if (id[j] == id[ver]) heap.push({dist[j], j});
            }
            if (id[j] != id[ver] && --indeg[id[j]] == 0) q.push(id[j]);
        }
    }
}

void topsort() {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    for (int i = 1; i <= bcnt; i++) if (!indeg[i]) q.push(i);

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        dijkstra(t);
    }
}


int main() {
    cin >> n >> r >> p >> s;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= r; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    for (int i = 1; i <= n; i++) if (!id[i]) dfs(i, ++bcnt);
    
    for (int i = 1; i <= p; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        indeg[id[b]]++;
    }
    
    topsort();
    for (int i = 1; i <= n; i++) {
        if (dist[i] > INF / 2) cout << "NO PATH" << endl;
        else cout << dist[i] << endl;
    }
    return 0;
}
