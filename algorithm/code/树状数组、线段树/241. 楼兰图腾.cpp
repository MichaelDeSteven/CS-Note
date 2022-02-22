#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 200010;
int n, tr[N], a[N]; // 维护比当前数小的个数
LL res1 = 0, res2 = 0;
int lowbit(int x) {
    return x & -x;
}

void query(int x, int inx) {
    LL smin = 0;
    for (int i = x - 1; i; i -= lowbit(i)) smin += tr[i];
    LL smax = inx - 1 - smin;
    res1 += smin*(x - 1 - smin);
    res2 += smax*(n - x - smax);
}

void add(int x, int y) {
    for (int i = x; i < N; i += lowbit(i)) tr[i] += y;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(a[i], 1);
        query(a[i], i);
    }
    cout << res2 << ' ' << res1 << endl;
    return 0;
}
