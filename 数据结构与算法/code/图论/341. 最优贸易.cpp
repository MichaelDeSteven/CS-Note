#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N = 100010, M = 2e6 + 10;
int e[M], ne[M], h[M], rh[M], inx;
int n, m, val[N];
int dmin[N], dmax[N], st[N];

void add(int *h, int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}
void spfa() {
    memset(st, 0, sizeof st);
    memset(dmin, 0x3f, sizeof dmin);
    dmin[1] = val[1];
    
    queue<int> q;
    q.push(1);
    st[1] = true;
    
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        
        for (int i = h[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dmin[j] > min(dmin[t], val[j])) {
                dmin[j] = min(dmin[t], val[j]);
                if (!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
}

void spfa1() {
    memset(st, 0, sizeof st);
    memset(dmax, -0x3f, sizeof dmax);
    dmax[n] = val[n];
    
    queue<int> q;
    q.push(n);
    st[n] = true;
    
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = false;
        
        for (int i = rh[t]; i != -1; i = ne[i]) {
            int j = e[i];
            if (dmax[j] < max(dmax[t], val[j])) {
                dmax[j] = max(dmax[t], val[j]);
                if (!st[j]) {
                    st[j] = true;
                    q.push(j);
                }
            }
        }
    }
}
int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    memset(rh, -1, sizeof rh);
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        add(h, a, b), add(rh, b, a);
        if (c == 2) add(h, b, a), add(rh, a, b);
    }
    spfa();
    spfa1();
    int res = -0x3f3f3f3f;
    for (int i = 1; i <= n; i++) res = max(res, dmax[i] - dmin[i]);
    cout << res << endl;
    return 0;
}
