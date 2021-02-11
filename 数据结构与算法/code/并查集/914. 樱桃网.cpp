#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1e5 + 10;
int p[N], n, m;

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}
int main() {
    int t;
    cin >> t;
    for (int j = 1; j <= t; j++) {
        cin >> n >> m;
        int res = 0;
        for (int i = 1; i <= n; i++) p[i] = i;
        for (int i = 1; i <= m; i++) {
            int x, y;
            cin >> x >> y;
            int a = find(x), b = find(y);
            if (a != b) {
                res++;
                p[a] = b;
            }
        }
        printf("Case #%d: %d\n", j, res + (n - res - 1) * 2);
    }
    return 0;
}
