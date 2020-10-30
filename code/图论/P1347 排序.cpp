#include<bits/stdc++.h>

using namespace std;
const int N = 30, M = 1e4;
int n, m, indeg[N], deg[N], st[N], num;
char res[N];
int e[M], ne[M], h[M], inx;

void add(int a, int b) {
    e[inx] = b, ne[inx] = h[a], h[a] = inx++;    
}

int topsort(int num) {
    queue<int> q;
    for (int i = 0; i < 26; i++) {
        deg[i] = indeg[i];
        if (st[i] && !deg[i]) q.push(i);
    }
    
    bool flag = q.size() == 1;
    int cnt = 0;
    while (!q.empty()) {
        int sz = q.size();
        if (sz != 1) flag = false;
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            res[cnt++] = (char)('A' + t);
            for (int j = h[t]; j != -1; j = ne[j]) {
                int k = e[j];
                if (--deg[k] == 0) q.push(k);
            }
        }
    }
    if (cnt < num) return -1;
    if (cnt == n && flag) return 999;
    return cnt;
}

int main() {
    memset(h, -1, sizeof h);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        string str;
        cin >> str;
        int a = str[0] - 'A', b = str[2] - 'A';
        add(a, b);
        indeg[b]++;
        if (!st[a]) st[a]++, num++;
        if (!st[b]) st[b]++, num++;
        int t = topsort(num);
        if (t == -1) {
            printf("Inconsistency found after %d relations.\n", i);
            return 0;
        } else if (t == 999) {
            printf("Sorted sequence determined after %d relations: ", i);
            for (int i = 0; i < n; i++) cout << res[i];
            cout << ".";
            return 0;
        }
    }
    cout << "Sorted sequence cannot be determined." << endl;
    return 0;
}
