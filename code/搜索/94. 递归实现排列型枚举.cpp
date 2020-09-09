#include<bits/stdc++.h>

using namespace std;
const int N = 10;
int st[N], res[N], n;

void dfs(int cnt) {
    if (cnt >= n) {
        for (int i = 0; i < n; i++) cout << res[i] << ' ';
        cout << endl;
        return;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            st[i] = true;
            res[cnt] = i;
            dfs(cnt + 1);
            st[i] = false;
        }
    }
}

int main() {
    cin >> n;
    
    dfs(0);
    
    return 0;
}
