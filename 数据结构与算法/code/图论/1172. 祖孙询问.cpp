#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 4e5, M = 2*N;
int e[M], ne[M], h[M], inx;
int n, m, root;
int fa[N][16], dep[N];

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void bfs() {
    queue<int> q;
    dep[root] = 1;
    q.push(root);
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (!dep[j]) {
                dep[j] = dep[t] + 1;
                q.push(j);
                fa[j][0] = t;
                for (int k = 1; k < 16; k++) {
                    fa[j][k] = fa[fa[j][k - 1]][k - 1];
                }
            }
        }
    }
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = 15; i >= 0; i--) {
        if (dep[fa[a][i]] >= dep[b]) {
            a = fa[a][i];
        }
    }
    if (a == b) return a;
    for (int i = 15; i >= 0; i--) {
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

int main() {
    cin >> n;
    memset(h, -1, sizeof h);

    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        if (b == -1) {
            root = a;
            continue;
        }
        add(a, b), add(b, a);
    }
    bfs();
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        
        int c = lca(a, b);
        if (c == a) cout << 1 << endl;
        else if (c == b) cout << 2 << endl;
        else cout << 0 << endl;
    }
    
    return 0;
}
