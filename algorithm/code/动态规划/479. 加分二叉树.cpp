#include<bits/stdc++.h>

using namespace std;
const int N = 35;
int f[N][N], n, a[N], root[N][N];

void dfs(int ll, int rr) {
    if (ll > rr) return;
    cout << root[ll][rr] << ' ';
    dfs(ll, root[ll][rr] - 1);
    dfs(root[ll][rr] + 1, rr);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    for (int len = 1; len <= n; len++) {
        for (int ll = 1; ll + len - 1 <= n; ll++) {
            int rr = ll + len - 1;
            for (int k = ll; k <= rr; k++) {
                int left = k == ll ? 1 : f[ll][k - 1];
                int right = k == rr ? 1 : f[k + 1][rr];
                int score = ll == rr ? a[k] : left * right + a[k];
                if (f[ll][rr] < score) {
                    f[ll][rr] = score;
                    root[ll][rr] = k;
                }
                
            }
        }
    }
    
    cout << f[1][n] << endl;
    dfs(1, n);
    return 0;
}
