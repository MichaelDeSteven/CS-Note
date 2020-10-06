#include<bits/stdc++.h>

using namespace std;
int a, b, x, y;

int exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return b;
    }
    int x1 = x, y1 = y;
    int d = exgcd(b, a % b, x1, y1);
    x = y1, y = x1 - a / b * y1;
    return d;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        exgcd(a, b, x, y);
        
        cout << x << ' ' << y << endl;
    }
    return 0;
}
