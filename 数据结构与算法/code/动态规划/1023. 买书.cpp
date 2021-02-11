#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N], v[4] = {10, 20, 50, 100}, n;
// f[i][j]表示前i本书选择若干本，花费不超过j的方案数
int main() {
    cin >> n;
    f[0] = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j <= n; j++)
            if (j >= v[i]) f[j] += f[j - v[i]];
            
    cout << f[n] << endl;
    return 0;
}
