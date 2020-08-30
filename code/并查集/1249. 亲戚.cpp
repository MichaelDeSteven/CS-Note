#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 20010;
int n, m, q, p[N];

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}

int main() {
    for (int i = 1; i < N; i++) p[i] = i;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        int a = find(x), b = find(y);
        if (a != b) p[a] = b;
    }
    cin >> q;
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        int a = find(x), b = find(y);
        if (a != b) printf("No\n");
        else printf("Yes\n");
    }
    return 0;
}
