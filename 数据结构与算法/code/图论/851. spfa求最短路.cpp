#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1e6;
#define INF 0x3f3f3f3f
int e[N], ne[N], w[N], h[N], inx;
int n, m, st[N], dist[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void spfa() {
    memset(dist, 0x3f, sizeof dist);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    st[1] = true;
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
    if (dist[n] > INF / 2) cout << "impossible" << endl;
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
    spfa();
    
    return 0;
}
