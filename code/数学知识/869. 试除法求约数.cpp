#include<bits/stdc++.h>

using namespace std;
int n;

vector<int> get_div(int n) {
    vector<int> res;
    for (int i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            res.push_back(i);
            if (i != n / i) res.push_back(n / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> res = get_div(n);
        for (auto t : res) cout << t << ' ';
        cout << endl;
    }
    
    return 0;
}
