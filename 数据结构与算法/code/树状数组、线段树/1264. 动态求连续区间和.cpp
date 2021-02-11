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

// 线段树写法
#include<bits/stdc++.h>

using namespace std;

const int N = 100010;
struct node {
    int w, l, r;
}seg[4*N];
int n, m, w[N];

void pushup(int u) {
    seg[u].w = seg[u << 1].w + seg[u << 1 | 1].w;
}

void build(int u, int ll, int rr) {
    if (ll == rr) {
        seg[u] = {w[ll], ll, rr};
        return;
    }
    int mid = ll + rr >> 1;
    build(u << 1, ll, mid), build(u << 1 | 1, mid + 1, rr);
    seg[u].l = ll, seg[u].r = rr;
    pushup(u);
}

int query(int u, int ll, int rr) {
    if (seg[u].l >= ll && seg[u].r <= rr) return seg[u].w;
    int mid = seg[u].l + seg[u].r >> 1;
    int sum = 0;
    if (ll <= mid) sum += query(u << 1, ll, rr);
    if (rr >= mid + 1) sum += query(u << 1 | 1, ll, rr);
    return sum;
}

void modify(int u, int inx, int v) {
    if (seg[u].l == seg[u].r) {
        seg[u].w += v;
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
        int k, a, b;
        cin >> k >> a >> b;
        if (!k) cout << query(1, a, b) << endl;
        else modify(1, a, b);
    }
    return 0;
}
