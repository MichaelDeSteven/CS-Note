#include<bits/stdc++.h>

using namespace std;
const int N = 5010;
int t[2*N], a[N], f[N], n;

int main() {
    cin >> n;
    memset(t, -1, sizeof t);
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        t[a] = b;
    }
    for (int i = 1, cnt = 1; cnt <= n; i++) {
        if (t[i] != -1) a[cnt++] = t[i];
    } 
    
    int res = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++)
            if (a[j] < a[i]) f[i] = max(f[i], f[j] + 1);
        res = max(f[i], res);
    }
    
    cout << res << endl;
    
    return 0;
}
