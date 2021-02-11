#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
struct node {
    int w, l, r;
} seg[4*N];
int n, m, w[N];

void pushup(int u) {
    seg[u].w = max(seg[u << 1].w, seg[u << 1 | 1].w);    
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {w[ll], ll, ll};
        return;
    }
    
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u].l = ll, seg[u].r = rr;
    pushup(u);
}

int query(int u, int ll, int rr) {
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u].w;
    int mid = seg[u].l + seg[u].r >> 1, maxv = 0;
    if (ll <= mid) maxv = max(maxv, query(u << 1, ll, rr));
    if (rr >= mid + 1) maxv = max(maxv, query(u << 1 | 1, ll, rr));
    return maxv;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
    build(1, 1, n);

    while (m--) {
        int ll, rr;
        scanf("%d %d", &ll, &rr);
        printf("%d\n", query(1, ll, rr));
    }
    
    return 0;
}
