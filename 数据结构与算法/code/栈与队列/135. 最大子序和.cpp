#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<limits.h>          // 引入INT_MIN
using namespace std;

const int N = 300010;
int n, m, a[N], s[N];
int tt = -1, hh, q[N];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    
    int res = INT_MIN;
    // 一开始的前缀和为s[0] = 0
    q[++tt] = 0;
    // s[i] - s[j], 枚举i，找到最小的s[j], 且j - i + 1 <= m
    for (int i = 1; i <= n; i++) {
        // 在区间长度不超过m
        while (tt >= hh && i - q[hh] > m) hh++;
        while (tt >= hh && s[i] <= s[q[tt]]) tt--;
        res = max(res, s[i] - s[q[hh]]);
        q[++tt] = i;
    }
    
    cout << res << endl;
    return 0;
}
