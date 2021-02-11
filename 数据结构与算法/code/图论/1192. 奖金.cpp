#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1e6;
typedef long long LL;
int e[N], ne[N], h[N], inx;
int idg[N], res[N], st[N], n, m;

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

bool topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) if (!idg[i]) q.push(i);
    int cnt = 0, c = 100;
    while (!q.empty()) {
        int sz = q.size();
        for (int k = 1; k <= sz; k++) {
            auto t = q.front();
            q.pop();
            st[t] = true;
            res[++cnt] = c;
            for (int i = h[t]; i != -1; i = ne[i]) {
                int j = e[i];
                if (--idg[j] == 0) q.push(j);
            }
        }
        c++;
    }
    return cnt == n;
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        add(b, a);
        idg[a]++;
    }
    
    if (!topsort()) cout << "Poor Xed" << endl;
    else {
        LL sum = 0;
        for (int i = 1; i <= n; i++) sum += res[i];
        cout << sum << endl;
    }
    
    return 0;
}
