#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N =  1e6;
int st[N], n, m;
int e[N], ne[N], h[N], inx;

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}
bool dfs(int color, int u) {
    st[u] = color;
    for (int i = h[u]; i != -1; i = ne[i]) {
        int j = e[i];
        if (st[j] == -1) {
            if (!dfs(!color, j)) return false;
        }
        else if (st[j] == color) return false;
    }
    return true;
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(st, -1, sizeof st);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(a, b), add(b, a);
    }
    
    for (int i = 1; i <= n; i++)
        if (st[i] == -1) {
            if (!dfs(1, i)) {
                cout << "No" << endl;
                return 0;
            }
        }
    
    cout << "Yes" << endl;
    return 0;
}
