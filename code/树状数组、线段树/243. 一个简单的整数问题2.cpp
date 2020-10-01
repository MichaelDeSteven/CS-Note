#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef long long LL;
LL n, m, tr1[N], tr2[N], a[N];

int lowbit(int x) {
    return x & -x;
}

LL query(LL x) {
    LL res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
        res += (x + 1) * tr1[i];
        res -= tr2[i];
    }
    return res;
}

void add(LL x, LL y) {
    for (int i = x; i <= n; i += lowbit(i)) {
        tr1[i] += y;
        tr2[i] += x*y;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        add(i, a[i] - a[i - 1]);
    }
    
    while (m--) {
        string op;
        cin >> op;
        if (op == "Q") {
            int x, y;
            cin >> x >> y;
            cout << query(y) - query(x - 1) << endl;
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            add(x, z), add(y + 1, -z);
        }
    }
    
    return 0;
}
