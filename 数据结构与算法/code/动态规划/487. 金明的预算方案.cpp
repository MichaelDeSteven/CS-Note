#include<bits/stdc++.h>

using namespace std;
const int N = 65, M = 200010;
vector<int> list[N], fa;
unordered_map<int, int> ma;
int n, m, v[N][N], w[N][N], s[N], cnt;
int f[M];
int main() {
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (!c) v[++cnt][1] = a, w[cnt][1] = a*b, s[cnt] = 1, ma[i] = cnt;
        else {
            c = ma[c];
            if (s[c] == 1) {
                v[c][2] = v[c][1] + a, w[c][2] = w[c][1] + a*b, s[c]++;
            } else if (s[c] ==  2) {
                v[c][3] = v[c][2] + a, w[c][3] = w[c][2] + a*b, s[c]++;
                v[c][4] = v[c][1] + a, w[c][4] = w[c][1] + a*b, s[c]++;
            }
        }
    }

    for (int i = 1; i <= cnt; i++)
        for (int j = m; j >= 0; j--)
            for (int k = 1; k <= s[i]; k++)
                if (j >= v[i][k]) f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
    
    cout << f[m] << endl;
    return 0;
}
