#include<bits/stdc++.h>
/*
      0     1
      2     3
4  5  6  7  8  9  10
      11    12
13 14 15 16 17 18 19
      20    21
      22    23
*/

using namespace std;
const int N = 30;
int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};
int a[N], cnt[4];
int opposite[8] = {5, 4, 7, 6, 1, 0, 3, 2};
int path[100];

int f() {
    memset(cnt, 0, sizeof cnt);
    for (int i = 6; i <= 8; i++) cnt[a[i]]++;
    for (int i = 15; i <= 17; i++) cnt[a[i]]++;
    cnt[a[11]]++, cnt[a[12]]++;
    int maxv = 0;
    for (int i = 0; i < 4; i++) maxv = max(maxv, cnt[i]);
    return 8 - maxv;
}

void operation(int inx) {
    int t = a[op[inx][0]];
    for (int i = 1; i <= 6; i++) a[op[inx][i - 1]] = a[op[inx][i]];
    a[op[inx][6]] = t;
}

bool dfs(int cnt, int max_dep, int last) {
    if (f() + cnt > max_dep) return false;
    
    if (!f()) return true;
    
    for (int i = 0; i < 8; i++) {
        if (opposite[i] == last) continue;
        operation(i);
        path[cnt] = 'A' + i;
        if (dfs(cnt + 1, max_dep, i)) return true;
        operation(opposite[i]);
    }    
    
    return false;
}

int main() {
    while (cin >> a[0], a[0]) {
        for (int i = 1; i < 24; i++) cin >> a[i];
        
        int dep = 0;
        while (!dfs(0, dep, 10)) dep++;
        if (!dep) cout << "No moves needed" << endl;
        else {
            for (int i = 0; i < dep; i++) cout << (char)path[i];
            puts("");
        }
        cout << a[6] << endl;

    }
}
