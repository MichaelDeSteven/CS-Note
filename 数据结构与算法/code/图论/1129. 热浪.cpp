#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 6210;
int e[N], ne[N], h[N], w[N], inx;
int t, c, S, E, dist[N], st[N];
typedef pair<int, int> PII;
void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, S});
    
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
    cout << dist[E] << endl;
}
int main() {
    cin >> t >> c >> S >> E;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= c; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add(x, y, z), add(y, x, z);
    }
    dijkstra();
    return 0;
}
