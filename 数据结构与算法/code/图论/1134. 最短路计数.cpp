#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1e6, MOD = 100003;
typedef pair<int, int> PII;
int e[N], ne[N], h[N], inx;
int dist[N], st[N], n, m, cnt[N];
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++; 
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    cnt[1] = 1;
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, 1});
    
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        
        int ver = t.second, distant = t.first;
        if (st[ver]) continue;
        st[ver] = true;
        
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dist[j] > distant + 1) {
                dist[j] = distant + 1;
                cnt[j] = cnt[ver];
                q.push({dist[j], j});
            } else if (dist[j] == distant + 1) {
                cnt[j] = (cnt[j] + cnt[ver]) % MOD;
            }
        }
    }
}
int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dijkstra();
    
    for (int i = 1; i <= n; i++) cout << cnt[i] << endl;
    
    return 0;
}
