#include<bits/stdc++.h>

using namespace std;
const int N = 110;
char str[N];
int res;

int dfs(int u, int cnt) {
    if (!str[u]) {
        return cnt;
    }
    int i = 0;
    if (str[u] == '(') return dfs(u + 1, cnt);
}

int main() {
    cin >> str;
    
    dfs(0, 0);
    
    cout << res << endl;
    return 0;
}
