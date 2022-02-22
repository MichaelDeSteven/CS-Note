#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
struct node {
    int l, r, add, mul;
    LL sum;
} seg[4*N];
int n, m, p, w[N];

void pu(int u) {
    seg[u].sum = (seg[u << 1].sum + seg[u << 1 | 1].sum) % p;    
}

void cal(node& t, LL mul, LL add) {
    t.add = (t.add * mul + add) % p;
    t.mul = (t.mul * mul) % p;
    t.sum = ((t.sum * mul) % p + ((LL)(t.r - t.l + 1) * add) % p) % p;
}

void pd(int u) {
    auto &root = seg[u], &left = seg[u << 1], &right = seg[u << 1 | 1];
    cal(left, root.mul, root.add);
    cal(right, root.mul, root.add);
    root.add = 0, root.mul = 1;
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {ll, ll, 0, 1, w[ll]};
        return;
    }    
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u] = {ll, rr, 0, 1, 0};
    pu(u);
}

void modify(int u, int ll, int rr, LL mul, LL add) {
    if (seg[u].l >= ll && seg[u].r <= rr) {
        cal(seg[u], mul, add);
        return;
    }
    pd(u);
    int mid = seg[u].l + seg[u].r >> 1;
    if (ll <= mid) modify(u << 1, ll, rr, mul, add);
    if (rr >= mid + 1) modify(u << 1 | 1, ll, rr, mul, add);
    pu(u);
}

LL query(int u, int ll, int rr) {
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u].sum % p;
    pd(u);
    int mid = seg[u].l + seg[u].r >> 1;
    LL sum = 0;
    if (ll <= mid) sum = query(u << 1, ll, rr);
    if (rr >= mid + 1) sum = (sum + query(u << 1 | 1, ll, rr)) % p;
    return sum;
}

int main() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> w[i];
    cin >> m;
    build(1, 1, n);
    while (m--) {
        int a, t, g, c;
        cin >> a >> t >> g;
        if (a == 3) cout << query(1, t, g) << endl;
        else {
            cin >> c;
            if (a == 1) modify(1, t, g, c, 0);
            else modify(1, t, g, 1, c);
        }
    }
    return 0;
}
