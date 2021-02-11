#include<bits/stdc++.h>

using namespace std;
const int N = 110, M = 25;
int n, m, k;
int ma[1 << M];
vector<int> col[N];

int lowbit(int x) {
    return x & -x;
}
// 估计当前状态最少需要选几包
int f(int stat) {
    int cnt = 0;
    for (int i = (1 << m) - 1 - stat; i; i -= lowbit(i)) {
        int j = ma[lowbit(i)];
        cnt++;
        for (auto t : col[j]) {
            i = i & (~t);
        }
    }
    return cnt;
}

bool dfs(int stat, int dep) {
    if (!dep) return stat == (1 << m) - 1;
    if (f(stat) > dep) return false;
    
    int c = -1;
    for (int i = (1 << m) - 1 - stat; i; i -= lowbit(i)) {
        int j = ma[lowbit(i)];
        if (c == -1 || (col[c].size() > col[j].size())) c = j;
    }

    for (auto r : col[c]) {
        if (dfs(stat | r, dep - 1)) return true;
    }
    return false;
}


int main() {
    cin >> n >> m >> k;
    for (int i = 0; i < 20; i++) ma[1 << i] = i;
    for (int i = 0; i < n; i++) {
        int stat = 0;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            stat |= 1 << (x - 1);
        }
        for (int j = 0; j < m; j++) {
            if (stat >> j & 1) col[j].push_back(stat);
        }
    }
    
    int dep = 0;
    while (dep <= m && !dfs(0, dep)) dep++;
    
    if (dep > m) dep = -1;
    
    cout << dep << endl;
    
    return 0;
}
