#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 1e6 + 10;
int st[N], primes[N], phi[N], cnt, n;

void get_primes(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; primes[j] * i <= n; j++) {
            st[i * primes[j]] = true;
            phi[i * primes[j]] = phi[i] * (primes[j] - 1); 
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
        }
    }
}

int main() {
    cin >> n;
    get_primes(n);
    LL res = 0;
    for (int i = 1; i <= n; i++) res += phi[i];
    
    cout << res << endl;
    
    return 0;
}
