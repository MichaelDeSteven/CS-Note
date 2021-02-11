#include<bits/stdc++.h>

using namespace std;
const int N = 30, M = 1010;
int n, cnt, cnn;
int p[M], st[M], vis[M];
int ind[M], outd[M];
string str[M], res[M];
int ptr[N];
int find(int x) {
    if (p[x] == x) return p[x];
    return p[x] = find(p[x]);
}

void dfs(int u) {
    for (int i = 0; i < n; i++) {
        if (!vis[i] && str[i][0] - 'a' == u) {
            vis[i] = true;
            dfs(str[i][str[i].size() - 1] - 'a');
            res[++cnn] = str[i];
        }
    }
}

int main() {
    cin >> n;
    int merge = 0;
    for (int i = 0; i < N; i++) p[i] = i;
    for (int i = 0; i < n; i++) cin >> str[i];
    sort(str, str + n);
    for (int i = 0; i < n; i++) {
        int hh = str[i][0] - 'a', tt = str[i][str[i].size() - 1] - 'a';
        ind[tt]++, outd[hh]++;
        if (!st[hh]) st[hh]++, cnt++;
        if (!st[tt]) st[tt]++, cnt++;
        int x = find(hh), y = find(tt);
        if (x != y) {
            merge++;
            p[x] = y;
        }
    }
    
    int one, two, dif = 0;
    for (int i = 0; i < N; i++) {
        if (ind[i] == outd[i]) continue;
        dif++;
        if (dif > 3) break;
        if (dif == 1) one = i;
        else two = i;
    }
    
    int a = ind[one] - outd[one], b = ind[two] - outd[two];
    
    if (merge == cnt - 1 && (!dif || (dif == 2 && (a + b == 0 && abs(a) == 1)))) {
        int u;
        if (!dif) {
            for (int i = 0; i < N; i++)
                if (st[i]) {
                    u = i;
                    break;
                }
        } else u = one;
        dfs(u);
        string ss = "";
        for (int i = cnn; i; i--) {
            ss += res[i];
            if (i != 1) ss += ".";
        }
        cout << ss << endl;
    } else {
        cout << "***" << endl;
    }
    return 0;
}
