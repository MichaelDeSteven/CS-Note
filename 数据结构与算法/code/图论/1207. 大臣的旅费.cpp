// 两遍dfs
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1e6;
typedef long long LL;
int e[N], ne[N], h[N], w[N], inx;
int n, d[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa, int val) {
    d[u] = val;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != fa) dfs(j, u, val + w[i]);
    }
}
int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    int u = 1;
    dfs(1, -1, 0);
    for (int i = 1; i <= n; i++)
        if (d[i] > d[u]) u = i;
    
    dfs(u, -1, 0);
    for (int i = 1; i <= n; i++)
        if (d[i] > d[u]) u = i;
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        LL start = 11, end = start + d[i] - 1;
        res = max(res, (start + end) * d[i] / 2);
    }
    cout << res << endl;
    return 0;
}

// 树形dp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1e6;
typedef long long LL;
int e[N], ne[N], h[N], w[N], inx;
int n, d[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

int dfs(int u, int fa) {
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != fa) {
            int dist = dfs(j, u) + w[i];
            if (dist > d1) d2 = d1, d1 = dist;
            else if (dist > d2) d2 = dist;
        }
    }
    d[u] = d1 + d2;
    return max(d1, d2);
}
int main() {
    cin >> n;
    memset(h, -1, sizeof h);
    for (int i = 1; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    dfs(1, -1);
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        LL start = 11, end = start + d[i] - 1;
        res = max(res, (start + end) * d[i] / 2);
    }
    cout << res << endl;
    return 0;
}
