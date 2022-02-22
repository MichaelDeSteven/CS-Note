#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 1010;
int p[N*N], n, m, res;
int get(int x, int y) {
    return x*m + y;
}
int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

void kruskal() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int a = get(i - 1, j), b = get(i, j);
            if (a > n*m || b > n*m) continue;
            int x = find(a), y = find(b);
            if (x == y) continue;
            res += 1, p[x] = y;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int a = get(i - 1, j), b = get(i - 1, j + 1);
            if (a > n*m || b > n*m) continue;
            int x = find(a), y = find(b);
            if (x == y) continue;
            res += 2, p[x] = y;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n*m; i++) p[i] = i;
    int a, b, c, d;
    while (cin >> a >> b >> c >> d) {
        int x = find(get(a - 1, b)), y = find(get(c - 1, d));
        p[x] = y;
    }
    kruskal();
    cout << res << endl;
    
    return 0;
}
