#include<bits/stdc++.h>

using namespace std;
const int N = 16;
int st[N], n;

void dfs(int u, int cnt) {
    if (u > n) {
        for (int i = 0; i < cnt; i++) cout << st[i] << ' ';
        cout << endl;
        return;
    }
    
    dfs(u + 1, cnt);
    st[cnt] = u;
    dfs(u + 1, cnt + 1);
}

int main() {
    cin >> n;
    dfs(1, 0);
    return 0;
}
