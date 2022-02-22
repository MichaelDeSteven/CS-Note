#include<bits/stdc++.h>

using namespace std;
const int N = 100010;
typedef long long LL;
unordered_map<int, int> ma;
int a[N], n, tr[N], cnt;
vector<int> alls;

int lowbit(int x) {
    return x & -x;
}

int query(int x) {
    LL res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
    return res;
}

void add(int x, int y) {
    for (int i = x; i <= cnt; i += lowbit(i)) tr[i] += y;
}

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        alls.push_back(a[i]);
    }
    sort(alls.begin(), alls.end());
    alls.erase(unique(alls.begin(), alls.end()), alls.end());

    for (auto t : alls) ma[t] = ++cnt; 
    
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        res += query(cnt) - query(ma[a[i]]);
        add(ma[a[i]], 1);
    }
    
    cout << res << endl;
    
    return 0;
}
