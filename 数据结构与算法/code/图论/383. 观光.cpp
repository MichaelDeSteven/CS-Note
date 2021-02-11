#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1010, M = 10010;
typedef pair<int, int> PII;
int n, m, S, F;
int e[M], ne[M], h[M], w[M], inx;
int dist[N][2], cnt[N][2];   // 0 表示最短、1表示次短

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;    
}

void dijkstra() {
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> q;
    q.push({0, S});
    dist[S][0] = 0, cnt[S][0] = 1;
    while (!q.empty()) {
        auto t = q.top();
        q.pop();
        
        int ver = t.second, distant = t.first;
        int k = -1;
        if (distant == dist[ver][0]) k = 0;
        else if (distant == dist[ver][1]) k = 1;
        else continue;
        
        for (int i = h[ver]; i != -1; i = ne[i]) {
            int j = e[i], d = distant + w[i];
            if (dist[j][0] > d) {
                dist[j][1] = dist[j][0], cnt[j][1] = cnt[j][0];
                dist[j][0] = d, cnt[j][0] = cnt[ver][k];
                q.push({d, j});
            } else if (dist[j][0] == d) {
                cnt[j][0] += cnt[ver][k];
            } else {
                if (dist[j][1] > d) {
                    dist[j][1] = d, cnt[j][1] = cnt[ver][k];
                    q.push({d, j});
                } else if (dist[j][1] == d) {
                    cnt[j][1] += cnt[ver][k];
                }
            }
        }
    }
    if (dist[F][0] + 1 == dist[F][1]) cout << cnt[F][0] + cnt[F][1] << endl;
    else cout << cnt[F][0] << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        memset(h, -1, sizeof h);
        for (int i = 1; i <= m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            add(a, b, c);
        }
        cin >> S >> F;
        dijkstra();
    }
    
    return 0;
}
