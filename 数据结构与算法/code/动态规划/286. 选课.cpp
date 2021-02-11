#include<bits/stdc++.h>

using namespace std;
const int N = 310, M = 2*N;
int e[M], ne[M], h[M], inx;
int w[N], f[N][N], n, m;
/*
    f[i][j]表示以i为根节点，选j门课获得的最多的学分
    每个子结点选择多少门课看作每组选哪个物品，子结点及其子树看成组，则为分组背包问题
*/
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (fa == j) continue;
        dfs(j, u);
        for (int k = m - 1; k >= 1; k--)
            for (int v = 1; v <= k; v++)
                f[u][k] = max(f[u][k], f[u][k - v] + f[j][v]);
    }
    
    for (int j = m; j; j--) f[u][j] = f[u][j - 1] + w[u];
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        w[i] = b;
        add(i, a), add(a, i);
    }
    m++;
    dfs(0, -1);
    
    cout << f[0][m] << endl;
    
    return 0;
}
