#include<bits/stdc++.h>

using namespace std;
const int N = 500010;
struct node {
    int w, l, r, lmax, rmax, sum;
} seg[4*N];
int n, m, w[N];

void pushup(int u) {
    seg[u].lmax = max(seg[u << 1].sum + seg[u << 1 | 1].lmax, seg[u << 1].lmax);
    seg[u].rmax = max(seg[u << 1 | 1].sum + seg[u << 1].rmax, seg[u << 1 | 1].rmax);
    seg[u].w = max(seg[u << 1].w, max(seg[u << 1 | 1].w, seg[u << 1].rmax + seg[u << 1 | 1].lmax));
    seg[u].sum = seg[u << 1].sum + seg[u << 1 | 1].sum;
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {w[ll], ll, ll, w[ll], w[ll], w[ll]};
        return;
    }
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u].l = ll, seg[u].r = rr;
    pushup(u);
}

node query(int u, int ll, int rr) {
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u];
    int mid = seg[u].l + seg[u].r >> 1;
    if (rr <= mid) return query(u << 1, ll, rr);
    else if (ll >= mid + 1) return query(u << 1 | 1, ll, rr);
    else {
        node res;
        auto l = query(u << 1, ll, rr), r = query(u << 1 | 1, ll, rr);
        res.sum = l.sum + r.sum, res.l = ll, res.r = rr;
        res.lmax = max(l.sum + r.lmax, l.lmax);
        res.rmax = max(r.sum + l.rmax, r.rmax);
        res.w = max(l.w, max(r.w, l.rmax + r.lmax));
        return res;
    }
}

void modify(int u, int inx, int v) {
    if (seg[u].l == seg[u].r) {
        seg[u].sum = seg[u].lmax = seg[u].rmax = seg[u].w = v;
        return;
    }
    int mid = seg[u].l + seg[u].r >> 1;
    if (inx <= mid) modify(u << 1, inx, v);
    else modify(u << 1 | 1, inx, v);
    pushup(u);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    build(1, 1, n);
    
    while (m--) {
        int k, x, y;
        cin >> k >> x >> y;
        if (k == 1) {
            if (x > y) swap(x, y);
            cout << query(1, x, y).w << endl;
        } else modify(1, x, y);
    }
    
    return 0;
}
