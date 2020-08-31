#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 210;
struct edg{
    int a, b, c;
    bool operator < (const edg& t) const {
        return c < t.c;
    }
}edg[N];
int n, m, tot, p[N];

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}
int kruskal() {
    for (int i = 1; i <= n; i++) p[i] = i;        
    sort(edg + 1, edg + 1 + m);
    int cnt = 0, res = 0;
    for (int i = 1; i <= m; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        cnt++, res += c, p[x] = y;
        if (cnt == m - 1) return res;
    }
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edg[i].a >> edg[i].b >> edg[i].c;
        tot += edg[i].c;
    }
    
    cout << tot - kruskal() << endl;
    return 0;
}
