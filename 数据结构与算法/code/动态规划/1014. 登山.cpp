#include<bits/stdc++.h>

using namespace std;
const int N = 2010;
int f1[N], f2[N], up[N], down[N], n;
/*
    题意是所有点的前面的最长上升子序列+后面的最长下降子序列中的最大值
*/
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> up[i];
        down[n - i + 1] = up[i];
    }
    
    int res = 0;
    for (int i = 1; i <= n; i++) {
        f1[i] = 1;
        for (int j = 1; j < i; j++)
            if (up[j] < up[i]) f1[i] = max(f1[i], f1[j] + 1);
    }
    for (int i = 1; i <= n; i++) {
        f2[i] = 1;
        for (int j = 1; j < i; j++)
            if (down[j] < down[i]) f2[i] = max(f2[i], f2[j] + 1);
    }
    for (int i = 1; i <= n; i++)
        res = max(res, f1[i] + f2[n - i + 1] - 1);
        
    cout << res << endl;
    return 0;
}
