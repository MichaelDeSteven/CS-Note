#include<bits/stdc++.h>

using namespace std;
const int N = 25;
string dict[N][N];
int cnt[N], n, res;

void dfs(string str, int last) {
    int l = str.size();
    res = max(res, l);
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 2 || dict[last][i] == "") continue;
        cnt[i]++;
        dfs(str + dict[last][i], i);
        cnt[i]--;
    }
}

int main() {
    string list[N];
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> list[i];
    for (int i = 1; i <= n; i++) {
        int l1 = list[i].size();
        for (int j = 1; j <= n; j++) {
            int l2 = list[j].size();
            for (int len = 1; len < l1; len++) {
                string sub1 = list[i].substr(l1 - len, len);
                string sub2 = list[j].substr(0, len);
                if (sub1 == sub2) {
                    dict[i][j] = list[j].substr(len, l2 - len);
                    break;
                }
            }
        }
    }
    char c;
    cin >> c;
    for (int i = 1; i <= n; i++)
        if (list[i][0] == c) {
            cnt[i]++;
            dfs(list[i], i);
            cnt[i]--;
        }
    
    cout << res << endl;
    return 0;
}
