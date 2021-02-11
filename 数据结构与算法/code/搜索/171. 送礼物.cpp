#include<bits/stdc++.h>

using namespace std;
const int N = 47;
typedef long long LL;
LL s[1 << (N / 2)];
int n, w, a[N], cnt;
LL res;

void dfs1(int u, LL weight) {
    if (u > n / 2) {
        s[++cnt] = weight;
        return;
    }
    
    dfs1(u + 1, weight);
    if (weight + a[u] <= w) dfs1(u + 1, weight + a[u]);
}

void dfs2(int u, LL weight) {
    if (u > n) {
        int ll = 1, rr = cnt;
        while (ll < rr) {
            int mid = ll + rr + 1 >> 1;
            if (s[mid] <= w - weight) ll = mid;
            else rr = mid - 1;
        }
        res = max(res, s[ll] + weight);
        return;
    }
    
    dfs2(u + 1, weight);
    if (weight + a[u] <= w) dfs2(u + 1, weight + a[u]);
}

int main() {
    cin >> w >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    reverse(a + 1, a + 1 + n);
    dfs1(1, 0);
    sort(s + 1, s + cnt + 1);
    cnt = unique(s + 1, s + cnt + 1) - (s + 1);

    dfs2(n / 2 + 1, 0);
    
    cout << res << endl;
    return 0;
}
