#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int f[N], t, m, v, w;

int main() {
    cin >> t >> m;
    for (int i = 1; i <= m; i++) {
        cin >> v >> w;
        for (int j = t; j >= v; j--) f[j] = max(f[j], f[j - v] + w);
    }
    cout << f[t] << endl;
    
    return 0;
}
