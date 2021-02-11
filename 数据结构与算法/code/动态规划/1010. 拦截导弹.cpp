#include<bits/stdc++.h>

using namespace std;
const int N = 1010, M = 30010;
int f[N], h[N], g[N], n;

int main() {
    int x;
    while (scanf("%d", &x) != EOF) h[++n] = x;
    reverse(h + 1, h + 1 + n);
    int res1 = 0, res2 = 0;
    // 求最长不下降子序列
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (h[j] <= h[i]) f[i] = max(f[i], f[j] + 1);
        res1 = max(f[i], res1);
    }
    // 求最长下降子序列
    for (int i = 1; i <= n; i++) {
        g[i] = 1;
        for (int j = 1; j < i; j++)
            if (h[j] > h[i]) g[i] = max(g[i], g[j] + 1);
        res2 = max(g[i], res2);
    }
        
    cout << res1 << endl << res2 << endl;
    return 0;
}
