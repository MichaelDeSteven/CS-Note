#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 20010, M = 100010;
struct node{
    int a, b, c;
    bool operator < (const node& t) const {
        if (c != t.c) return c > t.c;
        if (a != t.a) return a < t.a;
        return b < t.b;
    }
}rel[M];

int n, m, p[N], dist[N];

int find(int x) {
    if (x == p[x]) return p[x];
    int t = find(p[x]);
    dist[x] += dist[p[x]];
    return p[x] = t;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;
    for (int i = 1; i <= m; i++) cin >> rel[i].a >> rel[i].b >> rel[i].c;
    
    sort(rel + 1, rel + 1 + m);
    
    for (int i = 1; i <= m; i++) {
        int a = rel[i].a, b = rel[i].b;
        int x = find(a), y = find(b);
        if (x != y) {
            p[x] = y;
            dist[x] = dist[b] - dist[a] + 1;
        } else {
            if ((dist[a] - dist[b]) % 2 == 0) {
                cout << rel[i].c << endl;
                return 0;
            }
        }
    }
    cout << "0" << endl;
    return 0;
}
