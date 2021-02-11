#include<bits/stdc++.h>

using namespace std;
int n, x;

void div(int x) {
    for (int i = 2; i <= x / i; i++) {
        if (x % i == 0) {
            int t = 0;
            while (x % i == 0) {
                t++;
                x /= i;
            }
            cout << i << ' ' << t << endl;
        }
    }
    if (x > 1) cout << x << ' ' << 1 << endl;
    cout << endl;
}

int main() {
    cin >> n;
    while (n--) {
        cin >> x;
        div(x);
    }
    return 0;
}
