#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1e6;
int e[N], ne[N], h[N], inx;
int idg[N], res[N], st[N], n, m;

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

bool topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) if (!idg[i]) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = true;
        res[++cnt] = t;
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (--idg[j] == 0) q.push(j);
        }
    }
    return cnt == n;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b);
        idg[b]++;
    }
    
    if (!topsort()) cout << "-1" << endl;
    else {
        for (int i = 1; i <= n; i++) cout << res[i] << ' ';
    }
    
    return 0;
}
