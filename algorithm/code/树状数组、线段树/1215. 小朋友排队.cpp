#include<bits/stdc++.h>

using namespace std;
const int N = 1000010;
typedef long long LL;
int tr[N], h[N], n, sum[N];

int lowbit(int x) {
    return x & -x;    
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void add(int x, int y) {
    for (int i = x; i < N; i += lowbit(i)) tr[i] += y;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    
    for (int i = 1; i <= n; i++) {
        sum[i] += query(N - 1) - query(h[i]);
        add(h[i], 1);
    }
    
    memset(tr, 0, sizeof tr);
    
    for (int i = n; i >= 1; i--) {
        sum[i] += query(h[i] - 1);
        add(h[i], 1);
    }
    
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        res += (LL)(sum[i]) * (sum[i] + 1) / 2;
    }
    
    cout << res << endl;
    return 0;
}
