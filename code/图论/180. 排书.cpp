#include<bits/stdc++.h>

using namespace std;
const int N = 16;
int a[N], n;
int st[6][N];

int f() {
    int tot = 0;
    for (int i = 2; i <= n; i++)
        if (a[i] != a[i - 1] + 1) tot++;
    return (tot + 2) / 3;
}

bool dfs(int cnt, int max_dep) {
    if (cnt > max_dep) return false;
    if (f() + cnt > max_dep) return false;
    if (!f()) return true;
    
    for (int len = 1; len <= n; len++) {
        for (int ll = 1; ll + len - 1 <= n; ll++) {
            int rr = ll + len - 1;
            for (int k = rr + 1; k <= n; k++) {
                memcpy(st[cnt], a, sizeof a);
                int i = ll, j = rr + 1;
                for (; j <= k; i++, j++) a[i] = st[cnt][j];
                for (j = ll; j <= rr; j++, i++) a[i] = st[cnt][j];
                if (dfs(cnt + 1, max_dep)) return true;
                memcpy(a, st[cnt], sizeof a);
            }
        }
    }
    return false;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        
        int dep = 0;
        while (dep < 5 && !dfs(1, dep + 1)) dep++;
        
        if (dep >= 5) cout << "5 or more" << endl;
        else cout << dep << endl;
    }
    return 0;
}
