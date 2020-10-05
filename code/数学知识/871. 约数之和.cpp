#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int MOD = 1e9 + 7;
int n;
unordered_map<int, int> ma;
void get(int n) {
    for (int i = 2; i <= n / i; i++) {
        if (n % i == 0) {
            int t = 0;
            while (n % i == 0) {
                t++;
                n /= i;
            }
            ma[i] += t;
        }
    }
    if (n > 1) ma[n]++;
}

LL get_pow(int a, int b) {
    LL res = 1;
    for (int i = 1; i <= b; i++) {
        LL t = i, base = a, c = 1;
        while (t) {
            if (t & 1) c = (c * base) % MOD;
            base = (base * base) % MOD;
            t >>= 1;
        }
        res = (res + c) % MOD;
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        get(n);
    }
    LL res = 1;
    for (auto i : ma) res = (res * get_pow(i.first, i.second)) % MOD;
    
    cout << res << endl;
    return 0;
}
