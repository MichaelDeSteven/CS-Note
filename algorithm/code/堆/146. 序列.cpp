#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;
const int N = 1010;
typedef pair<int, int> PII;
int a[N], b[N], c[N], n, m;

void merge() {
    priority_queue<PII, vector<PII>, greater<PII>> q;
    for (int i = 1; i <= n; i++) q.push({a[1] + b[i], 1});
    for (int i = 1; i <= n; i++) {
        auto t = q.top();
        q.pop();
        c[i] = t.first, q.push({a[t.second + 1] + t.first - a[t.second], t.second + 1});
    }
    memcpy(a, c, sizeof c);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> m >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        sort(a + 1, a + 1 + n);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j <= n; j++) cin >> b[j];
            merge();
        }
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << endl;
    }
    
    return 0;
}
