#include<bits/stdc++.h>

using namespace std;

const int N = 100010;
int a[N], n;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    
    int d = a[2] - a[1];
    for (int i = 2; i <= n; i++) d = gcd(a[i] - a[i - 1], d);
    
    if (!d) cout << n << endl;
    else cout << (a[n] - a[1]) / d + 1 << endl;
    
    return 0;
}
