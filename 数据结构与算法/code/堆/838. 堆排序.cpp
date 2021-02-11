#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;

const int N = 1e5 + 10;
int h[N], n, m, sz;
void down(int u) {
    int t = u;
    if (u * 2 <= sz && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= sz && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (t != u) {
        swap(h[t], h[u]);
        down(t);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[++sz];
    }
    
    for (int i = n / 2; i; i--) down(i);
    
    for (int i = 1; i <= m; i++) {
        cout << h[1] << ' ';
        h[1] = h[sz--];
        down(1);
    }
    
    return 0;
}
