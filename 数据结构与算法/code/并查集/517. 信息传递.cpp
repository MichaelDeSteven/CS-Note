// 带权并查集写法
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 200010;

int p[N], n, d[N], res = 0x3f3f3f3f;

int find(int x) {
    if (p[x] == x) return p[x];
    int t = find(p[x]);
    d[x] += d[p[x]];
    return p[x] = t;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) p[i] = i;
    
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        int x = find(i), y = find(t);
        // 存在环则更新
        if (x == y) {
            res = min(res, d[i] + d[t] + 1);
        }
        else {
            p[x] = y;
            d[i] = d[t] + 1;
        }
    }
    
    cout << res << endl;
    return 0;
}

// 不采用路径压缩
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 200010;

int p[N], n, cnt, res = 0x3f3f3f3f;

int find(int x) {
    cnt++;
    if (p[x] == x) return p[x];
    return find(p[x]);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) p[i] = i;
    
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        cnt = 0;
        int x = find(t);
        if (x == i) {
            res = min(res, cnt);
        } else {
            p[i] = t;
        }
    }
    
    cout << res << endl;
    return 0;
}
