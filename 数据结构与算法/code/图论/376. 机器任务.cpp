#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const int N = 110;
int g[N][N], n, m, k;
int match[N], st[N];

bool find(int u) {
    for (int i = 1; i < m; i++) {
        if (st[i] || !g[u][i]) continue;
        st[i] = true;
        if (!match[i] || find(match[i])) {
            match[i] = u;
            return true;
        }
    }
    return false;
}
int main() {
    while (cin >> n, n) {
        cin >> m >> k;
        memset(g, 0, sizeof g);
        memset(match, 0, sizeof match);
        for (int i = 1; i <= k; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            if (!b || !c) continue;
            g[b][c] = 1;
        }

        int res = 0;
        for (int i = 1; i < n; i++) {
            memset(st, 0, sizeof st);
            if (find(i)) res++;
        }
        cout << res << endl;
    }
}
