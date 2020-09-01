#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 6010;
struct node {
    int a, b, c;
    bool operator < (const node& t) const {
        return c < t.c;
    }
}edg[N];
int n, p[N], sz[N];

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}
int kruskal() {
    int res = 0;
    for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    sort(edg + 1, edg + n);
    for (int i = 1; i < n; i++) {
        int a = edg[i].a, b = edg[i].b, c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;
        res += (sz[x] * sz[y] - 1) * (c + 1);
        sz[y] += sz[x], p[x] = y;
    }
    return res;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i < n; i++) cin >> edg[i].a >> edg[i].b >> edg[i].c;
        cout << kruskal() << endl;
    }
    
    return 0;
}
