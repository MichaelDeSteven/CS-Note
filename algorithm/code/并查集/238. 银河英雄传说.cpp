#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 30010;
int p[N], dist[N], n, sz[N];           // dist[i]表示结点i到根节点的距离, sz[i]表示i所在集合战舰数量

int find(int x) {
    if (p[x] == x) return p[x];
    int t = find(p[x]);
    dist[x] += dist[p[x]];
    return p[x] = t;
}
int main() {
    cin >> n;
    for (int i = 1; i < N; i++) p[i] = i, sz[i] = 1;
    for (int i = 1; i <= n; i++) {
        string op;
        int a, b;
        cin >> op >> a >> b;
        int x = find(a), y = find(b);
        if (op == "M") {
            if (x != y) {
                p[x] = y;
                dist[x] += sz[y];
                sz[y] += sz[x];
            }
        } else if (op == "C") {
            if (x != y) cout << "-1" << endl;
            else {
                if (a == b) cout << 0 << endl;
                else cout << abs(dist[b] - dist[a]) - 1 << endl;
            }
        }
    }
    return 0;
}
