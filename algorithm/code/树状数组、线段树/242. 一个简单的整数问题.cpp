#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef long long LL;
int n, m, tr[N];

int lowbit(int x) {
    return x & -x;
}

LL query(int x) {
    LL res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
    return res;
}

void add(int x, int y) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += y;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        add(i, x), add(i + 1, -x);
    }
    
    while (m--) {
        string op;
        cin >> op;
        if (op == "Q") {
            int x;
            cin >> x;
            cout << query(x) << endl;
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            add(x, z), add(y + 1, -z);
        }
    }
    
    return 0;
}
