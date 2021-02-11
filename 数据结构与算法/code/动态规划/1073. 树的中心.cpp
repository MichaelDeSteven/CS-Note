/*
 f[i][0/1/2]表示以结点i为根节点，通过0/1/2方式中能走到的最远距离
 0表示结点i向子结点出发能走到的最远距离
 1表示结点i向父结点出发能走到的最远距离
 2表示结点i向子结点出发能走到的第二远的距离
 f[i][0] = max{f[son][0] + Wson}
 f[i][2] = 2max{f[son][0] + Wson}
 若父结点fa到子结点的f[fa][0] = fa到i的距离+f[i][0]，不满足f[i][1]最远距离的定义，此时选择f[fa][2]
 f[i][1] = {f[fa][1], f[fa][2] + Wfa}
 若满足f[fa][0] != fa到i的距离+f[i][0]
 f[i][1] = {f[fa][1], f[fa][0] + Wfa}
*/
#include<bits/stdc++.h>

using namespace std;
const int N = 10010, M = 2*N;
int e[M], ne[M], w[M], h[M], inx;
int n, f[N][3];

void add(int a, int b, int c) {
    e[inx] = b, w[inx] = c, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    int d1 = 0, d2 = 0;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        int d = f[j][0] + w[i];
        if (d > d1) d2 = d1, d1 = d;
        else if (d > d2) d2 = d;
    }
    f[u][0] = d1, f[u][2] = d2;
}

void dfs_up(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        if (f[u][0] == w[i] + f[j][0]) f[j][1] = max(f[u][1], f[u][2]) + w[i];
        else f[j][1] = max(f[u][1], f[u][0]) + w[i];
        dfs_up(j, u);
    }
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c), add(b, a, c);
    }
    
    dfs(1, -1);
    dfs_up(1, -1);
    
    int res = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) res = min(res, max(f[i][0], f[i][1]));
    
    cout << res << endl;
    
    return 0;
}
