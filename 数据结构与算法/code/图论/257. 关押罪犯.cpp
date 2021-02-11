#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 20010, M = 200010;
int e[M], ne[M], w[M], h[M], inx;
int n, m, color[N], st[N];

void add(int a, int b, int c) {
    w[inx] = c, e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}
// 求最大值最小问题
// 只用大于x的边权来判断是否为二分图
// 成立则答案在左半区间
bool dfs(int u, int c, int x) {
    color[u] = c;
    st[u] = true;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (w[i] <= x) continue;
        if (color[j] == -1) {
            if (!dfs(j, !c, x)) return false;
        } else if (color[j] == c) return false;
    }
    return true;
}
bool check(int x) {
    memset(st, 0, sizeof st);
    memset(color, -1, sizeof color);
    for (int i = 1; i <= n; i++)
        if (!st[i]) {
            if (!dfs(i, 0, x)) return false;
        }
    return true;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    
    int ll = 0, rr = 1000000000;
    while (ll < rr) {
        int mid = ll + rr >> 1;
        if (check(mid)) rr = mid;
        else ll = mid + 1;
    }
    
    cout << ll << endl;
    return 0;
}
