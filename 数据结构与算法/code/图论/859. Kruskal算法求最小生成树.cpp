#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10, M = 1e6;

struct edg {
    int a, b, c;
    bool operator < (const edg& t) const {
        return c < t.c;
    }
}edg[M];

int n, m, p[N];

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}
void Kruskal() {
    int res = 0, cnt = 0;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        p[x] = y, res += c, cnt++;
        if (cnt >= n - 1) break;
    }
    if (cnt < n - 1) cout << "impossible" << endl;
    else cout << res << endl;
}
int main() {
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        cin >> edg[i].a >> edg[i].b >> edg[i].c;
    }
    sort(edg + 1, edg + 1 + m);
    
    Kruskal();
    
    return 0;
}
