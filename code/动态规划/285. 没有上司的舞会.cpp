#include<bits/stdc++.h>

using namespace std;
const int N = 6010*2;
int e[N], ne[N], h[N], inx;
int f[N][2], n, a[N], w[N], res = -0x3f3f3f3f;
/*
    f[i][0]表示以i为根节点，不邀请i去的最大值
    f[i][1]表示以i为根节点，邀请i去的最大值
*/
void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void dfs(int u, int fa) {
    f[u][1] = w[u];
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j == fa) continue;
        dfs(j, u);
        f[u][0] += max(f[j][0], f[j][1]);
        f[u][1] += f[j][0];
    }
    res = max(res, max(f[u][1], f[u][0]));
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> w[i];
    
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    dfs(1, -1);
    
    cout << res << endl;
    
    return 0;
}
