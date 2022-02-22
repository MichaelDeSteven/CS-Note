#include<bits/stdc++.h>

using namespace std;

const int N = 110;
int a[N], n;

bool dfs(int cnt, int max_dep) {
    if (cnt > max_dep) return false;
    if (a[cnt] == n) return true;
    
    bool st[N];
    memset(st, 0, sizeof st);
    
    for (int i = cnt; i >= 1; i--)
        for (int j = i; j >= 1; j--) {
            int cur = a[i] + a[j];
            if (cur <= a[cnt] || cur > n || st[cur]) continue;
            st[cur] = true;
            a[cnt + 1] = cur;
            if (dfs(cnt + 1, max_dep)) return true;
        }
    return false;
}

int main() {
    a[1] = 1;
    while (cin >> n, n) {
        int dep = 1;
        while (!dfs(1, dep)) dep++;
        
        for (int i = 1; i <= dep; i++) cout << a[i] << ' ';
        cout << endl;
    }
    
    return 0;
}
