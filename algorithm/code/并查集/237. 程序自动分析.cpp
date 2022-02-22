// 只判断条件对错，与顺序无关，先把相等的条件合并，再判断不相等的条件
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<vector>

using namespace std;
const int N = 2000010;
int p[N], n, cnt;
struct node {
    int a, b, c;
}str[N];

int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> alls;
        unordered_map<int, int> ma;
        for (int i = 1; i <= n; i++) {
            cin >> str[i].a >> str[i].b >> str[i].c;
            alls.push_back(str[i].a), alls.push_back(str[i].b);
        }
        sort(alls.begin(), alls.end());
        alls.erase(unique(alls.begin(), alls.end()), alls.end());
        cnt = 0;
        for (auto i : alls) ma[i] = ++cnt;
        
        for (int i = 1; i <= cnt; i++) p[i] = i;
        for (int i = 1; i <= n; i++) {
            if (str[i].c) {
                int x = find(ma[str[i].a]), y = find(ma[str[i].b]);
                if (x != y) p[x] = y;
            }
        }
        
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (!str[i].c) {
                int x = find(ma[str[i].a]), y = find(ma[str[i].b]);
                if (x == y) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}
