#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N][N], n, m, v, w, s;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v >> w >> s;
        for (int j = 0; j <= m; j++)
            for (int k = 0; k <= s; k++)
                if (j >= k*v) f[i][j] = max(f[i][j], f[i - 1][j - k*v] + k*w);
    }
    cout << f[n][m] << endl;
    
    return 0;
}

\\ 空间优化同01背包
#include<bits/stdc++.h>

using namespace std;
const int N = 110;
int f[N], n, m, v, w, s;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> v >> w >> s;
        for (int j = m; j >= 0; j--)
            for (int k = 0; k <= s; k++)
                if (j >= k*v) f[j] = max(f[j], f[j - k*v] + k*w);
    }
    cout << f[m] << endl;
    
    return 0;
}
