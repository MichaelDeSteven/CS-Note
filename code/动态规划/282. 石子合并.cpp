#include<bits/stdc++.h>

using namespace std;
const int N = 310;
int s[N], f[N][N], n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    
    memset(f, 0x3f, sizeof f);
    
    for (int len = 1; len <= n; len++) {
        for (int ll = 1; ll + len - 1 <= n; ll++) {
            int rr = ll + len - 1;
            for (int k = ll; k <= rr; k++) {
                if (ll == rr) {
                    f[ll][rr] = 0;
                    break;
                }
                f[ll][rr] = min(f[ll][rr], f[ll][k] + f[k + 1][rr] + s[rr] - s[ll - 1]);
            }
        }
    }
    
    cout << f[1][n] << endl;
    
    return 0;
}
