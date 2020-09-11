#include<bits/stdc++.h>

using namespace std;
const int N = 15;
vector<vector<int>> vec;
int a[N], n, res = N;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
void dfs(int cnt) {
    int sz = vec.size();
    if (sz > res) return;
    if (cnt >= n) {
        res = min(res, sz);
        return;
    }
    
    // 分在新的一组
    vec.push_back({a[cnt]});
    dfs(cnt + 1);
    vec.pop_back();
    for (int i = 0; i < vec.size(); i++) {
        bool flag = true;
        for (auto j : vec[i]) {
            if (gcd(j, a[cnt]) != 1) {
                flag = false;
                break;
            }
        }
        // 与该组均互质则加入该组
        if (flag) {
            vec[i].push_back(a[cnt]);
            dfs(cnt + 1);
            vec[i].pop_back();
        }
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    
    dfs(0);
    
    cout << res << endl;
    return 0;
}
