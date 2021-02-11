#include<bits/stdc++.h>

using namespace std;
const int N = 5010;
int a, b;
int st[N], primes[N], cnt, sum[N];

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) primes[cnt++] = i;
        for (int j = 0; primes[j] <= n / i; j++) {
            st[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

int get(int n, int p) {
    int res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}

vector<int> mul(vector<int>& a, int b) {
    for (int i = 0; i < a.size(); i++) a[i] *= b;
    
    int t = 0;
    for (int i = 0; i < a.size(); i++) {
        t = t + a[i];
        a[i] = t % 10;
        t /= 10;
    }
    
    while (t) {
        a.push_back(t % 10);
        t /= 10;
    }
    return a;
}

int main() {
    cin >> a >> b;
    
    get_primes(a);
    
    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        sum[i] = get(a, p) - get(b, p) - get(a - b, p);
    }
    vector<int> res;
    res.push_back(1);
    
    for (int i = 0; i < cnt; i++)
        for (int j = 1; j <= sum[i]; j++)
            res = mul(res, primes[i]);
    
    for (int i = res.size() - 1; i >= 0; i--) cout << res[i];
    
    
    return 0;
}
