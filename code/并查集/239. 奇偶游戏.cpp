// s[r] - s[l - 1] = 偶, s[r]、s[l - 1]奇偶性相同
// s[r] - s[l - 1] = 奇, s[r]、s[l - 1]奇偶性不同
// s[i]表示前缀[0, i]的奇偶性，可证明上述充要条件
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<unordered_map>
#include<vector>

using namespace std;
const int N = 20010;
int p[N], n, m, cnt, dist[N];       // dist[i]表示与根节点的奇偶关系，0为奇偶相同，1奇偶不同
vector<int> alls;
unordered_map<int, int> ma;
struct node {
    int a, b; 
    string c;
} str[N];

int find(int x) {
    if (p[x] == x) return p[x];
    int t = find(p[x]);
    dist[x] += dist[p[x]];
    return p[x] = t;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> str[i].a >> str[i].b >> str[i].c;
        alls.push_back(str[i].a), alls.push_back(str[i].b);
    }
    
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());
    
    for (auto i : alls) ma[i] = ++cnt;
    for (int i = 0; i <= cnt; i++) p[i] = i;
    
    for (int i = 1; i <= m; i++) {
        int a = ma[str[i].a] - 1, b = ma[str[i].b];
        int x = find(a), y = find(b);
        if (x == y) {
            int z = ((dist[a] - dist[b]) % 2 + 2) % 2;
            if ((!z && str[i].c == "odd") || (z && str[i].c == "even")) {
                cout << i - 1 << endl;
                return 0;
            }
        } else {
            p[x] = y;
            if (str[i].c == "even") dist[x] = dist[b] - dist[a];
            else dist[x] = dist[b] - dist[a] + 1;
        }
    }
    cout << m << endl;
    return 0;
}
