#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 110;
int idg[N], res[N], st[N], g[N][N], n, m;


bool topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) if (!idg[i]) q.push(i);
    int cnt = 0;
    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        st[t] = true;
        res[++cnt] = t;
        for (int i = 1; i <= n; i++) {
            if (g[t][i] && --idg[i] == 0) q.push(i);
        }
    }
    return cnt == n;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int son;
        while (cin >> son, son) {
            g[i][son] = 1, idg[son]++;
        }
    }
    
    topsort();
    for (int i = 1; i <= n; i++) cout << res[i] << ' ';
    
    return 0;
}
