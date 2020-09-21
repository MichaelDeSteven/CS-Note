#include<bits/stdc++.h>

using namespace std;
const int N = 1010;
int h[N], f[N], n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    
    int res = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = h[i];
        for (int j = 1; j < i; j++)
            if (h[i] > h[j]) f[i] = max(f[i], h[i] + f[j]);
        res = max(res, f[i]);
    }
    
    cout << res << endl;
    
    return 0;
}
