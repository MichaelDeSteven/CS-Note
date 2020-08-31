#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 2010, M = 1e4 + 10;
int p[N], n, m, cnn, res;
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
    sort(edg + 1, edg + 1 + cnn);
    for (int i = 1; i <= cnn; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        res += c, p[x] = y;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            int x = find(a), y = find(b);
            p[x] = y, res += c;
            continue;
        }
        cin >> edg[++cnn].a >> edg[cnn].b >> edg[cnn].c;
    }
    kruskal();
    cout << res << endl;
    
    return 0;
}
