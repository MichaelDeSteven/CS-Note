#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 100010;
int p[N], n, m, sz[N];

int find(int x) {
    if (x == p[x]) return x;
    return p[x] = find(p[x]);
}

void Union(int a, int b) {
    int p1 = find(a), p2 = find(b);
    sz[p2] = sz[p1] + sz[p2];
    p[p1] = p[p2];
}


int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;
    string op;
    int x, y;
    while (m--) {
        cin >> op >> x >> y;
        if (op == "C") {
            int a, b;
            cin >> a >> b;
            Union(a, b);
        } else if (op == "Q1") {
            cin >> a >> b;
            if (find(a) == find(b)) cout << "Yes" << endl;
            else cout << "No" << endl;
        } else if (op == "Q2") {
            int a;
            cin >> a;
            cout << sz[a] << endl;
        }
    }


    return 0;
}
