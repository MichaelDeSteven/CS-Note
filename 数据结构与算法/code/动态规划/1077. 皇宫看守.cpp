#include<bits/stdc++.h>

using namespace std;
const int N = 1510, M = 2*N;
int e[M], ne[M], h[M], inx;
int w[N], n, f[N][3], st[N], root;
/*
    f[i][0/1/2]表示以结点i为根节点，0结点i的被父结点看到，1结点i的被直接子结点看到，2结点i被安置
    f[i][0] = min{f[son][1], f[son][2]}
    f[i][1] = 至少有一个子结点被安置，其它子结点状态转移为min{f[son][1], f[son][2]}
    f[i][2] = min{f[son][0], f[son][1], f[son][2]} + w[i]
*/
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    int minv = 0x3f3f3f3f;
    f[u][2] = w[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        f[u][0] += min(f[j][1], f[j][2]);
        f[u][2] += min(f[j][0], min(f[j][1], f[j][2]));
        f[u][1] += min(f[j][2], f[j][1]);
        minv = min(minv, -min(f[j][2], f[j][1]) + f[j][2]);
    }
    f[u][1] += minv;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> c >> b;
        w[a] = c;
        for (int j = 1; j <= b; j++) {
            cin >> c;
            st[c] = 1;
            add(a, c), add(c, a);
        }
    }
    for (int i = 1; i <= n; i++)
        if (!st[i]) root = i;

    dfs(root, -1);
    
    cout << min(f[root][1], f[root][2]) << endl;
    return 0;
}
