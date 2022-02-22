#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 100010;
typedef long long LL;
int h[N], n, ll[N], rr[N];

void cal(int bound[N]) {
    int stk[N], hh;
    // 初始化
    stk[hh] = 0;
    for (int i = 1; i <= n; i++) {
        while (hh && h[i] <= h[stk[hh]]) hh--;
        bound[i] = stk[hh];
        stk[++hh] = i;
    }
}

int main() {
    // 逗号表达式，输入同时，判断n是否为0，为0则结束
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> h[i];
        // cal函数用来计算每个矩形左边第一个比它小的矩形位置
        cal(ll);
        // 反转数组h，计算矩形右边第一个比它小的矩形位置则变成了左边第一个比它小的矩形
        reverse(h + 1, h + 1 + n);
        cal(rr);
        // 还原回来，方便计算原来位置的矩形
        reverse(h + 1, h + 1 + n);
        // rr[i]计算的是反转后的矩形的位置，所以要反转一下
        reverse(rr + 1, rr + 1 + n);
        LL res = 0;
        for (int i = 1; i <= n; i++) {
            LL len = (n - rr[i]) - ll[i];
            res = max(res, len * h[i]);
        }
        cout << res << endl;
    }
}
