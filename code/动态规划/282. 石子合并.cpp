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


// 记忆化搜索版本
#include<bits/stdc++.h>


using namespace std;
const int N = 310;
int f[N][N], n, s[N];

int dfs(int ll, int rr) {
    if (f[ll][rr] != -1) return f[ll][rr];
    if (ll == rr) return f[ll][rr] = 0;
    
    int res = 0x3f3f3f;
    for (int k = ll; k < rr; k++) {
        res = min(res, dfs(ll, k) + dfs(k + 1, rr) + s[rr] - s[ll - 1]);
    }
    return f[ll][rr] = res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    
    memset(f, -1, sizeof f);
    
    cout << dfs(1, n) << endl;
    return 0;
}
