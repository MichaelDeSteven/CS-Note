#include<bits/stdc++.h>

using namespace std;
const int N = 1e6;
int tr[N], n, k;

int lowbit(int x) {
    return x & -x;
}

void add(int x, int y) {
    for (int i = x; i < N; i += lowbit(i)) tr[i] += y;
}

int query(int x) {
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
    return res;
}

int main() {
    cin >> n >> k;
    while (k--) {
        string op;
        cin >> op;
        if (op == "A") {
            int x;
            cin >> x;
            cout << query(x) << endl;
        } else {
            int x, y;
            cin >> x >> y;
            if (op == "B") add(x, y);
            else add(x, -y);
        }
    }
    
    return 0;
}
