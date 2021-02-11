#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 100010;
int p[N], n, m;

int find(int x) {
    if (x == p[x]) return x;
    return p[x] = find(p[x]);
}

void Union(int a, int b) {
    int p1 = find(a), p2 = find(b);
    p[p1] = p[p2];
}


int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) p[i] = i;
    string op;
    int x, y;
    while (m--) {
        cin >> op >> x >> y;
        if (op == "M") Union(x, y);
        else if (op == "Q") {
            int p1 = find(x), p2 = find(y);
            if (p1 == p2) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
    
    return 0;
}
