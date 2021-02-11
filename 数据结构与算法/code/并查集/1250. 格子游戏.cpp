#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>

using namespace std;
const int N = 210 * 210;
int p[N], n, m;

// 二维坐标转一维
int get(int x, int y) {
    return x * n + y;
}

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i < N; i++) p[i] = i;
    
    for (int i = 1; i <= m; i++) {
        int a, b, x, y;
        string dir;
        cin >> a >> b >> dir;
        x = get(a, b);
        if (dir == "D") y = get(a + 1, b);
        else y = get(a, b + 1);
        x = find(x), y = find(y);
        if (x == y) {
            cout << i << endl;
            return 0;
        }
        else p[x] = y;
    }
    cout << "draw" << endl;
    return 0;
}
