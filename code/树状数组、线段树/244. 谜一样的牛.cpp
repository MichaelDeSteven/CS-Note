#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int tr[N], n, a[N], b[N];

int lowbit(int x) {
    return x & -x;    
}

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += y;
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    cin >> n;
    for (int i = 2; i <= n; i++) cin >> a[i];
    
    for (int i = 1; i <= n; i++) add(i, 1);
    
    for (int i = n; i >= 1; i--) {
        int ll = 1, rr = n;
        while (ll < rr) {
            int mid = ll + rr >> 1;
            if (query(mid) >= a[i] + 1) rr = mid;
            else ll = mid + 1;
        }
        b[i] = ll;
        add(ll, -1);
    }
    
    for (int i = 1; i <= n; i++) cout << b[i] << endl;
    
    return 0;
}
