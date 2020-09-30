#include<bits/stdc++.h>

using namespace std;
const int N = 100010;
int n, m, tr[N];

int lowbit(int x) {
    return x & -x;
}

int query(int x) {
    int sum = 0;
    for (int i = x; i > 0; i -= lowbit(i)) sum += tr[i];
    return sum;
}

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += y;
}
    
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        add(i, x);
    }
    
    while (m--) {
        int k, a, b;
        cin >> k >> a >> b;
        if (!k) cout << query(b) - query(a - 1) << endl;
        else add(a, b);
    }
    
    return 0;
}
