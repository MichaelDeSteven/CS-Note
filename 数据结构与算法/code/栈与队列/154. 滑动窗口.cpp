#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1e6 + 10;
int q[N], a[N], hh, tt = -1, k, n;

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    // 找滑动窗口最小值
    for (int i = 1; i <= n; i++) {
        // 不在窗口内的值出队
        while (tt >= hh && i - k >= q[hh]) hh++;
        // 队尾元素比当前值大则出队
        while (tt >= hh && a[i] <= a[q[tt]]) tt--;
        q[++tt] = i;
        if (i >= k) {
            cout << a[q[hh]] << ' ';
        }
    }
    cout << endl;
    tt = -1, hh = 0;
    // 找滑动窗口最大值
    for (int i = 1; i <= n; i++) {
        while (tt >= hh && i - k >= q[hh]) hh++;
        while(tt >= hh && a[i] >= a[q[tt]]) tt--;
        q[++tt] = i;
        if (i >= k) {
            cout << a[q[hh]] << ' ';
        }
    }
    return 0;
}
