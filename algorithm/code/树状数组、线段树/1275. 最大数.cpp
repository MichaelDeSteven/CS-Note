#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
struct node {
    int w, l, r;
}seg[4*N];
int m, p, last, n;

void pushup(int u) {
    seg[u].w = max(seg[u << 1].w, seg[u << 1 | 1].w);
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {0, ll, rr};
        return;
    }
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u].l = ll, seg[u].r = rr;
    pushup(u);
}

int query(int u, int ll, int rr) {
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u].w;
    int maxv = 0, mid = seg[u].l + seg[u].r >> 1;
    if (ll <= mid) maxv = query(u << 1, ll, rr);
    if (rr >= mid + 1) maxv = max(maxv, query(u << 1 | 1, ll, rr));
    return maxv;
}

void modify(int u, int inx, int v) {
    if (seg[u].l == seg[u].r) {
        seg[u].w = v;
        return;
    }
    
    int mid = seg[u].l + seg[u].r >> 1;
    if (inx <= mid) modify(u << 1, inx, v);
    else modify(u << 1 | 1, inx, v);
    pushup(u);
}

int main() {
    cin >> m >> p;
    build(1, 1, m);
    
    while (m--) {
        string op;
        int x;
        cin >> op >> x;
        if (op == "A") {
            ++n;
            modify(1, n, (x + last) % p);
        }
        else {
            last = query(1, n - x + 1, n);
            cout << last << endl; 
        }
    }
    return 0;
}
