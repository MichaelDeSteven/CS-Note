#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 1e5 + 10;

int h[N], hp[N], ph[N], sz, n;

void heap_swap(int a, int b) {
    
    swap(ph[hp[a]], ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}
void down(int u) {
    int t = u;
    if (2 * u <= sz && h[2 * u] < h[t]) t = 2 * u;
    if (2 * u + 1 <= sz && h[2 * u + 1] < h[t]) t = 2 * u + 1;
    if (t != u) {
        heap_swap(t, u);
        down(t);
    }
}

void up(int u) {
    while (u >> 1 && h[u] < h[u >> 1]) {
        heap_swap(u, u >> 1);
        u >>= 1;
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        string op;
        cin >> op;
        if (op == "I") {
            int x; 
            cin >> x;
            h[++sz] = x, ph[++n] = sz, hp[sz] = n;
            up(sz);
        } else if (op == "PM") {
            cout << h[1] << endl;
        } else if (op == "DM") {
            heap_swap(1, sz), sz--;
            down(1);
        } else if (op == "D") {
            int k;
            cin >> k;
            k = ph[k];
            heap_swap(k, sz), sz--;
            down(k), up(k);
        } else if (op == "C") {
            int k, x;
            cin >> k >> x;
            k = ph[k];
            h[k] = x;
            down(k), up(k);
        }
    }
    
    return 0;
}
