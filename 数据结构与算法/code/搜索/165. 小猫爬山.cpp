#include<bits/stdc++.h>

using namespace std;
const int N = 20;

int a[N], gr[N], n, w, res = N;

void dfs(int cnt, int cur) {
    // 最优性剪枝
    if (cnt >= res) return; 
    if (cur >= n) {
        res = min(res, cnt);
        return;
    }
    // 开新的一组
    gr[cnt + 1] = a[cur];
    dfs(cnt + 1, cur + 1);
    
    // 选一组
    for (int i = 1; i <= cnt; i++) {
        // 可行性剪枝
        if (gr[i] + a[cur] <= w) {
            gr[i] += a[cur];
            dfs(cnt, cur + 1);
            gr[i] -= a[cur];
        }
    }
}

int main() {
    cin >> n >> w;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    // 优先搜索分枝少的结点
    reverse(a, a + n);
    
    dfs(0, 0);
    
    cout << res << endl;
    return 0;
}
