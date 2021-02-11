#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
int n;

int get_euler(int n) {
    int res = n;
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res = (LL)res * (i - 1) / i;
        }
    }
    if (n > 1) res = (LL)res * (n - 1) / n;
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        cout << get_euler(n) << endl;
    }
    return 0;
}
