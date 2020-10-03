#include<bits/stdc++.h>

using namespace std;
const int N = 32010;
int tr[N], cnt[N], n;

int lowbit(int x) {
    return x & -x;    
}

int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

void add(int x, int y) {
    for (int i = x; i < N; i += lowbit(i)) tr[i] += y;    
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        x++;
        cnt[query(x)]++;
        add(x, 1);
    }
    for (int i = 0; i < n; i++) cout << cnt[i] << endl;
    
    return 0;
}
