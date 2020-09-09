// 递归版
#include<bits/stdc++.h>

using namespace std;
const int N = 26;
int st[N], n, m;

void dfs(int cnt, int cur) {
    if (cnt >= m) {
        for (int i = 0; i < cnt; i++) cout << st[i] << ' ';
        cout << endl;
        return;
    }
    
    for (int i = cur; i <= n; i++) {
        st[cnt] = i;
        dfs(cnt + 1, i + 1);
    }
}
int main() {
    cin >> n >> m;
    dfs(0, 1);
    
    return 0;
}
