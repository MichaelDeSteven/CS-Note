#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 500010;
struct node {
    int l, r;
    LL d;
} seg[4*N];

LL w[N], tr[N];
int n, m;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, LL y) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += y;
}

LL sum(int x) {
    LL res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void pushup(int u) {
    seg[u].d = gcd(seg[u << 1].d, seg[u << 1 | 1].d);
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {ll, ll, w[ll] - w[ll - 1]};
        return;
    }
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u].l = ll, seg[u].r = rr;
    pushup(u);
}

LL query(int u, int ll, int rr) {
    if (ll > rr) return 0;
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u].d;
    int mid = seg[u].l + seg[u].r >> 1;
    LL v = 0;
    if (ll <= mid) v = gcd(query(u << 1, ll, rr), v);
    if (rr >= mid + 1) v = gcd(query(u << 1 | 1, ll, rr), v);
    return v;
}

void modify(int u, int inx, LL v) {
    if (seg[u].l == seg[u].r) {
        seg[u].d += v;
        return;
    }
    int mid = seg[u].l + seg[u].r >> 1;
    if (inx <= mid) modify(u << 1, inx, v);
    else modify(u << 1 | 1, inx, v);
    pushup(u);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &w[i]);
    for (int i = 1; i <= n; i++) add(i, w[i] - w[i - 1]);
    build(1, 1, n + 1);
    char op[2];
    while (m--) {
        scanf("%s", op);
        if (*op == 'C') {
            int a, b;
            LL c;
            scanf("%d %d %lld", &a, &b, &c);
            add(a, c), add(b + 1, -c);
            modify(1, a, c), modify(1, b + 1, -c);
        } else {
            int a, b;
            scanf("%d %d", &a, &b);
            LL r1 = sum(a), r2 = query(1, a + 1, b);
            printf("%lld\n", abs(gcd(r1, r2)));
        }
    }
    return 0;
}
