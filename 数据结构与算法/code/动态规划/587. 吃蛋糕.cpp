#include<bits/stdc++.h>

using namespace std;

const int N = 10010;
int f[N], n;
// f[j]表示若干个物品恰好凑成体积为j
int main() {
    int t; 
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> n;
        memset(f, 0x3f, sizeof f);
        f[0] = 0;
        for (int i = 1; i <= sqrt(n); i++)
            for (int j = i*i; j <= n; j++)
                f[j] = min(f[j], f[j - i*i] + 1);
        printf("Case #%d: %d\n", i, f[n]);
    }
    
    return 0;
}
