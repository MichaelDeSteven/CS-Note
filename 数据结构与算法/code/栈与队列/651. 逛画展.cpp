// 用最少的钱看最多种类的画抽象出来就是求区间出现了1~M所有的数的最短区间
// 解法1：哈希表加双指针
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N = 1e6 + 10;
int n, m, a[N];
unordered_map<int, int> ma;    // 表示某个作家的画出现在该区间的次数
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    // 初始化
    for (int i = 1; i <= m; i++) ma[i] = 0;
    int cnt = 0, res = n, ll = 1, rr = n;
    for (int i = 1, j = 1; i <= n; ) {
        if (cnt < m) {
            if (!ma[a[i]]) cnt++;
            ma[a[i]]++;
            if (cnt < m) i++;
        }
        if (cnt == m) {
            if (res > i - j + 1) {
                ll = j, rr = i;
                res = i - j + 1;
            }
            ma[a[j]]--;
            if(!ma[a[j]]) cnt--, i++;
            j++;
        }
    }
    cout << ll << ' ' << rr << endl;
    return 0;
}


// 解法2 哈希+单调队列
// 单调队列维护画的种类，根据单调队列的性质，队头一定是老画，队头画的种类超过1则出队，备胎中一定有同一种类的新画，
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N = 1e6 + 10;
// st[i]为种类为i的画的数量，q为单调队列
int a[N], n, m, cnt, st[N], q[N], tt = -1, hh;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    int res = n, ll = 1, rr = n;
    for (int i = 1; i <= n; i++) {
        if (!st[a[i]]) cnt++;
        st[a[i]]++;
        // 保证同种老画的数量不超过1
        while (tt >= hh && st[a[q[hh]]] >= 2) st[a[q[hh]]]--, hh++;
        if (cnt == m && i - q[hh] + 1 < res) {
            res = i - q[hh] + 1;
            ll = q[hh], rr = i;
        }
        q[++tt] = i;
    }
    
    cout << ll << ' ' << rr << endl;
    return 0;
}
