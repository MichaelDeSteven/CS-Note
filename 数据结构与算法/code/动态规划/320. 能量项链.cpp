#include<bits/stdc++.h>

using namespace std;
const int N = 210;

int f[N][N], w[N], n, res;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        w[i + n] = w[i];
    }
    
    for (int len = 2; len <= n; len++) {
        for (int ll = 1; ll + len - 1 < 2*n; ll++) {
            int rr = ll + len - 1;
            for (int k = ll; k < rr; k++) {
                f[ll][rr] = max(f[ll][rr], f[ll][k] + f[k + 1][rr] + w[ll] * w[k + 1] * w[rr + 1]);
                res = max(f[ll][rr], res);
            }
        }
    }
    
    cout << res << endl;
    return 0;
}
