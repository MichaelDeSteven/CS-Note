#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 310, M = 8010;
int p[N], n, m, maxv;
struct edg {
    int a, b, c;
    bool operator < (const edg& t) const {
        return c < t.c;
    }
}edg[M];

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

void kruskal() {
    for (int i = 1; i <= n; i++) p[i] = i;
    sort(edg + 1, edg + 1 + m);
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        cnt++, maxv = max(maxv, c), p[x] = y;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> edg[i].a >> edg[i].b >> edg[i].c;
    kruskal();
    cout << n - 1 << ' ' << maxv << endl;
    
    return 0;
}
