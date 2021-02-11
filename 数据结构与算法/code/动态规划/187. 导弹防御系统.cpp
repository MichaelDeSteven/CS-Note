#include<bits/stdc++.h>

using namespace std;
const int N = 66;
int h[N], n;
int up[N], down[N];

bool dfs(int su, int sd, int u, int max_dep) {
    if (su + sd > max_dep) return false;
    if (u >= n) return true;
    bool flag = false;
    for (int i = 1; i <= su; i++)
        if (up[i] < h[u]) {
            flag = true;
            int t = up[i];
            up[i] = h[u];
            if (dfs(su, sd, u + 1, max_dep)) return true;
            up[i] = t;
            break;
        }
    if (!flag) {
        up[su + 1] = h[u];
        if (dfs(su + 1, sd, u + 1, max_dep)) return true;
    }
    flag = false;
    for (int i = 1; i <= sd; i++)
        if (down[i] > h[u]) {
            flag = true;
            int t = down[i];
            down[i] = h[u];
            if (dfs(su, sd, u + 1, max_dep)) return true;
            down[i] = t;
            break;
        }
    if (!flag) {
        down[sd + 1] = h[u];
        if (dfs(su, sd + 1, u + 1, max_dep)) return true;
    }
    return false;
}

int main() {
    
    while (cin >> n, n) {
        for (int i = 0; i < n; i++) cin >> h[i];
        
        int dep = 0;
        while (!dfs(0, 0, 0, dep)) dep++;
        
        cout << dep << endl;
    }
    
    return 0;
}
