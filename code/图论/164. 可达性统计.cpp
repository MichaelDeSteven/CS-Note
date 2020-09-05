#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<bitset>

using namespace std;
const int N = 30010;
int e[N], ne[N], h[N], inx;
int idg[N], res[N], n, m, cnt;
bitset<N> se[N];
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

bool topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) if (!idg[i]) q.push(i);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
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
    topsort();
    for (int i = n; i; i--) {
        int t = res[i];
        se[t][t] = 1;
        for (int j = h[t]; j != -1; j = ne[j]) {
            int k = e[j];
            se[t] |= se[k];
        }
    }
    for (int i = 1; i <= n; i++) cout << se[i].count() << endl;
    return 0;
}
