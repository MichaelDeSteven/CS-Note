/*
给定N种硬币，其中第 i 种硬币的面值为Ai,共有Ci个。
从中选出若干个硬币，把面值相加，若结果为S，则称“面值S能被拼成”。
求1~M之间能被拼成的面值有多少个?

本题仅关注“可行性”(面值能否拼成)而不是“最优性”,这是一个特殊之处。
仔细分析动态规划的过程，我们可以发现，若前i种硬币能够拼成面值j。只有两类可能情况：

1、 前i-1种硬币就能拼成面值j,即在第i阶段开始，变量F[j] 已经成为true.
2、 使用了第i种硬币，即在第i阶段的递推中，发现F[j-a[i]] 为true 从而F[j] 变为true  

于是我们考虑一种贪心策略：设used[j] 表示f[j] 阶段i时为 true 至少需要用多少枚第i种硬币 
并且尽量选择第一类情况，也就是说，在F[j-a[i]] 为true 时
如果F[j] 已经为true 则不执行DP转移，并令used[j]=0,否则才执行
F[j]=F[j] or F[j-a[i]] 的转移，并令used[j]=used[j-a[i]]+1. 


*/

#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int f[N], used[N], n, m, v[N], s[N];

int main() {
    while (cin >> n >> m, n && m) {
        for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
        for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= m; j++) used[j] = 0;
            for (int j = v[i]; j <= m; j++)
                if (!f[j] && f[j - v[i]] && used[j - v[i]] < s[i])
                    f[j] = 1, used[j] = used[j - v[i]] + 1;
        }
        int res = 0;
        for (int i = 1; i <= m; i++)
            if (f[i]) res++;
            
        cout << res << endl;
    }
    
    return 0;
} 
