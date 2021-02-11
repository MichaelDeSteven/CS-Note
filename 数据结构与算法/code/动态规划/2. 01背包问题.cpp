#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N][N], n, m, v, w;

int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        cin >> v >> w;
        for (int j = 1; j <= m; j++) {
            f[i][j] = f[i - 1][j];
            if (j >= v) f[i][j] = max(f[i][j], f[i - 1][j - v] + w);
        }
    }
    
    cout << f[n][m] << endl;
    return 0;
}


// 空间优化版
#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N], n, m, v, w;

int main() {
    cin >> n >> m;
    
    for (int i = 1; i <= n; i++) {
        cin >> v >> w;
        for (int j = m; j >= v; j--) {
            f[j] = max(f[j], f[j - v] + w);
        }
    }
    
    cout << f[m] << endl;
    return 0;
}
