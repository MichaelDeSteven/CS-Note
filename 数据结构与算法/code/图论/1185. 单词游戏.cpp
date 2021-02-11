#include<bits/stdc++.h>

using namespace std;
const int N = 30;
int outd[N], ind[N], p[N], st[N], n;

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        memset(outd, 0, sizeof outd);
        memset(ind, 0, sizeof ind);
        memset(st, 0, sizeof st);
        int merge = 0, cnt = 0;
        for (int i = 0; i < N; i++) p[i] = i;
        
        for (int i = 1; i <= n; i++) {
            string str;
            cin >> str;
            int hh = str[0] - 'a', tt = str[str.size() - 1] - 'a';
            outd[hh]++, ind[tt]++;
            int x = find(hh), y = find(tt);
            if (!st[hh]) st[hh] = true, cnt++;
            if (!st[tt]) st[tt] = true, cnt++;
            if (x != y) {
                merge++;
                p[x] = y;
            }
        }
        int one, two, dif = 0;
        for (int i = 0; i < N; i++) {
            if (ind[i] == outd[i]) continue;
            dif++;
            if (dif > 2) break;
            if (dif == 1) one = i;
            else two = i;
        }
        int a = ind[one] - outd[one], b = ind[two] - outd[two];

        if (merge == cnt - 1 && (!dif || (dif == 2 && abs(a) == 1 && a + b == 0))) {
            cout << "Ordering is possible." << endl;
        } else {
            cout << "The door cannot be opened." << endl;            
        }
    }
    
    return 0;
}
