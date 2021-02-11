#include<bits/stdc++.h>

using namespace std;
const int N = 6e4 + 10;
int f[N], n, a[7], used[N];

int main() {
    while (cin >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6]) {
        int sum = 0;
        for (int i = 1; i <= 6; i++) sum += a[i]*i;
        if (!sum) break;
        if (sum % 2) {
            cout << "Can't" << endl;
            continue;
        }
        memset(f, 0, sizeof f);
        f[0] = 1;
        for (int i = 1; i <= 6; i++) {
            for (int i = 0; i <= sum / 2; i++) used[i] = 0;
            for (int k = i; k <= sum / 2; k++)
                if (!f[k] && f[k - i] && used[k - i] < a[i])
                    f[k] = 1, used[k] = used[k - i] + 1;
        }
        if (!f[sum / 2]) cout << "Can't" << endl;
        else cout << "Can" << endl;
    }
}
