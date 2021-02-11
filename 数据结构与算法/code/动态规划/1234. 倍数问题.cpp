#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[2][N][4], n, m, v;
vector<int> vec[N], a;
// 前i个数字选择j个数，总和为k的倍数的所有方案中的最大和
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        vec[x % m].push_back(x);
    }
    
    for (int i = 0; i < m; i++) {
        sort(vec[i].begin(), vec[i].end());
        for (int j = vec[i].size() - 1, cnt = 0; cnt < 3 && j >= 0; j--, cnt++)
            a.push_back(vec[i][j]);
    }
    n = a.size();
    for (int i = 1; i <= n; i++) {
        v = a[i - 1];
        for (int j = 0; j < m; j++) {
            for (int k = 1; k <= 3 && k <= i; k++) {
                int x = ((j - v) % m + m) % m;
                f[i & 1][j][k] = f[(i - 1) & 1][j][k];
                if ((f[(i - 1) & 1][x][k - 1] + v) % m == j) 
                    f[i & 1][j][k] = max(f[i & 1][j][k], f[(i - 1) & 1][x][k - 1] + v);
            }
        }
    }
    
    cout << f[n & 1][0][3] << endl;
    return 0;
}
