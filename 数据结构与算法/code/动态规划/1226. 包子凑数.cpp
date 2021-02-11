#include<bits/stdc++.h>

using namespace std;
const int N = 100010;

int f[N], n, v;

int main() {
    cin >> n;
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> v;
        for (int j = v; j < N; j++)
            f[j] |= f[j - v];
    }
    
    int res = 0;
    for (int i = 1; i < N; i++) if (!f[i]) res++;
    
    if (res > N / 2) cout << "INF" << endl;
    else cout << res << endl;
    return 0;
}
