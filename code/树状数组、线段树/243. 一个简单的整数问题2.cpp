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


// 线段树懒标记
#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
struct node {
    int l, r, add;
    LL w;
} seg[4*N];
int w[N], n, m;

void pushup(int u) {
    seg[u].w = seg[u << 1].w + seg[u << 1 | 1].w;    
}

void pushdown(int u) {
    auto& root = seg[u], &left = seg[u << 1], &right = seg[u << 1 | 1];
    if (root.add) {
        left.add += root.add, left.w += (LL)(left.r - left.l + 1) * root.add;
        right.add += root.add, right.w += (LL)(right.r - right.l + 1) * root.add;
        root.add = 0;
    }
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {ll, ll, 0, w[ll]};
        return;
    }
    
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u] = {ll, rr, 0, 0};
    pushup(u);
}

void modify(int u, int ll, int rr, int v) {
    if (seg[u].l >= ll && seg[u].r <= rr) {
        seg[u].w += (LL)(seg[u].r - seg[u].l + 1) * v;
        seg[u].add += v;
        return;
    }
    pushdown(u);
    int mid = seg[u].l + seg[u].r >> 1;
    if (ll <= mid) modify(u << 1, ll, rr, v);
    if (rr >= mid + 1) modify(u << 1 | 1, ll, rr, v);
    pushup(u);
}

LL query(int u, int ll, int rr) {
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u].w;
    pushdown(u);
    int mid = seg[u].l + seg[u].r >> 1;
    LL res = 0;
    if (ll <= mid) res += query(u << 1, ll, rr);
    if (rr >= mid + 1) res += query(u << 1 | 1, ll, rr);
    return res;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    build(1, 1, n);
    while (m--) {
        string op;
        int a, b, c;
        cin >> op >> a >> b;
        if (op == "Q") cout << query(1, a, b) << endl;
        else {
            cin >> c;
            modify(1, a, b, c);
        }
    }
    
    return 0;
}
