#include<bits/stdc++.h>

using namespace std;
const int N = 21;

int c[N], up[N], down[N], n;
string res[N];

void dfs(int cnt) {
    if (cnt > n) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) cout << res[i][j];
            cout << endl;
        }
        cout << endl;
        return;
    }    
    
    for (int i = 1; i <= n; i++) {
        if (!c[i] && !up[cnt + i] && !down[cnt - i + n]) {
            c[i] = up[cnt + i] = down[cnt - i + n] = 1;
            res[cnt][i] = 'Q';
            dfs(cnt + 1);
            res[cnt][i] = '.';
            c[i] = up[cnt + i] = down[cnt - i + n] = 0;
        }
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < N; i++) res[i] = string(N, '.');
    dfs(1);
    return 0;
}
