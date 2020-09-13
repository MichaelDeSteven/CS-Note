#include<bits/stdc++.h>

using namespace std;
const int N = 70;
int a[N], st[N], n, res, s;

bool dfs(int gn, int last, int cnt) {
    if (!gn) return true;
    if (cnt == res) return dfs(gn - 1, 1, 0);
    
    for (int i = last; i <= n; i++) {
        if (st[i]) continue;
        if (cnt + a[i] > res) continue;
        st[i] = true;
        if (dfs(gn, i + 1, cnt + a[i])) return true;
        st[i] = false;
        // 第一根木棍放在木板第一个位置或者最后一个位置不合法时，则以后的方案都会失败
        if(cnt == 0 || a[i] + cnt == res) break;
        int j = i;
        while(j <= n && a[j] == a[i]) j++;
        i = j - 1;
    }
    return false;
}
int main() {
    while (cin >> n, n) {
        s = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            s += a[i];
        }
        sort(a + 1, a + 1 + n);
        reverse(a + 1, a + 1 + n);
        
        for (int i = a[1]; i <= s; i++) {
            if (s % i) continue;
            res = i;
            int gn = s / i;
            memset(st, 0, sizeof st);
            if (dfs(gn, 1, 0)) break;
        }
        
        cout << res << endl;        
    }
    return 0;
}
