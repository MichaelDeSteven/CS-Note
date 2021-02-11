#include<bits/stdc++.h>

using namespace std;
const int N = 3010;
int e[N], ne[N], h[N], inx;
int n, f[N][2], root;
/* 
f[i][0/1] 以结点i为根节点的子树中，0表示选择了结点i、1表示没有选择结点i的所有方案最小选择数
*/
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;    
}

void dfs(int u, int fa) {
    f[u][1] = 1;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        f[u][0] += f[j][1];
        f[u][1] += min(f[j][1], f[j][0]);
    }
}
int main() {
    while (scanf("%d", &n) != EOF) {
        memset(h, -1, sizeof h);
        memset(f, 0, sizeof f);
        inx = 0;
        for (int i = 1; i <= n; i++) {
            int a, b, c;
            scanf("%d:(%d)", &a, &b);
            if (i == 1) root = a;
            for (int i = 1; i <= b; i++) {
                cin >> c;
                add(a, c), add(c, a);
            }
        }
        dfs(root, -1);
        cout << min(f[root][0], f[root][1]) << endl;
    }
    
    return 0;
}
