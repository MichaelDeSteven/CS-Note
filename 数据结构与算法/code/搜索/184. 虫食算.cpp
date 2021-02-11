#include<bits/stdc++.h>

using namespace std;

const int N = 30;
int st[N], res[N], q[N], n;
char str[4][N];

bool check() {
    for (int i = n - 1, t = 0; i >= 0; i--) {
        int a = res[str[0][i] - 'A'], b = res[str[1][i] - 'A'], c = res[str[2][i] - 'A'];
        if (a != -1 && b != -1 && c != -1) {
            if (t == -1) {
                int ans1 = (a + b) % n, ans2 = (a + b + 1) % n;
                if (ans1 != c && ans2 != c) return false;
                if (!i && a + b >= n) return false;
            } else {
                if ((a + b + t) % n != c) return false;
                if (!i && (a + b + t) >= n) return false;
                t = (a + b + t) / n;
            }
        } else t = -1;
    }
    return true;
}

bool dfs(int cnt) {
    if (cnt >= n) return true;

    for (int i = 0; i < n; i++) {
        if (!st[i]) {
            st[i] = true;
            res[q[cnt]] = i;
            if (check() && dfs(cnt + 1)) return true;
            res[q[cnt]] = -1;
            st[i] = false;
        }
    }
    return false;
}


int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> str[i];
    
    for (int i = n - 1, k = 0; i >= 0; i--)
        for (int j = 0; j < 3; j++)
            if (!st[str[j][i] - 'A']) {
                int a = str[j][i] - 'A';
                q[k++] = a;
                st[a] = true;
            }
    memset(res, -1, sizeof res);
    memset(st, 0, sizeof st);
    
    
    dfs(0);
    
    for (int i = 0; i < n; i++) {
        cout << res[i];
        if (i != n - 1) cout << ' ';
    }
    return 0;
}
