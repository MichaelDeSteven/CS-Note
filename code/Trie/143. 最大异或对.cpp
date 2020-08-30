#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>

using namespace std;
const int N = 100010;

int son[2][N * 32], inx, a[N];
void insert(int x) {
    int p = 0;
    for (int i = 30; i >= 0; i--) {
        int u = (x >> i) & 1;
        if (!son[u][p]) son[u][p] = ++inx;
        p = son[u][p];
    }
}

int query(int x) {
    int p = 0, res = 0;
    for (int i = 30; i >= 0; i--) {
        int u = (x >> i) & 1;
        if (son[u^1][p]) {
            p = son[u^1][p], res += 1 << i;
        }
        else {
            p = son[u][p];
        }
    }
    return res;
}
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        insert(a[i]);
    }
    
    int maxv = 0;
    for (int i = 1; i <= n; i++) {
        maxv = max(maxv, query(a[i]));
    }
    cout << maxv << endl;
    return 0;
}
