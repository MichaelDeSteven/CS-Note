#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;

const int N = 500010;
int a[N], s[N], q[N], hh, tt = -1;
int n, m;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    
    int res = 0;
    q[++tt] = 0;
    for (int i = 1;i <= n; i++) {
        while (tt >= hh && i - m > q[hh]) ++hh;
        while (tt >= hh && s[i] <= s[q[tt]]) --tt;
        res = max(res, s[i] - s[q[hh]]);
        q[++tt] = i;
    }
    
    cout << res << endl;
    return 0;
}
