#include<bits/stdc++.h>

using namespace std;
const int N = 10010, M = 2e6 + 10;
int e[M], ne[M], h[M], inx;
int w[N], n, indeg[N], outdeg[N], f[N];

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;
}

void topsort() {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) {
            f[i] = w[i];
            q.push(i);
        }
    }
    
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            
            for (int j = h[t]; j != -1; j = ne[j]) {
                int k = e[j];
                f[k] = max(f[k], f[t] + w[k]);
                indeg[k]--;
                if (indeg[k] == 0) q.push(k);
            }
        }
    }
    
    int res = 0;
    for (int i = 1; i <= n; i++)
        if (!outdeg[i]) 
            res = max(res, f[i]);
        
    cout << res << endl;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        scanf("%d %d", &a, &b);
        w[a] = b;
        while (scanf("%d", &c)) {
            if (!c) break;
            add(c, a);
            indeg[a]++, outdeg[c]++;
        }
    }
    
    topsort();
    
    return 0;
}
