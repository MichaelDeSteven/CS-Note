#include<bits/stdc++.h>

using namespace std;
const int N = 10;
int st[N], n, res;

int get(int ll, int rr) {
    int cnt = 0;
    for (int i = ll; i <= rr; i++) cnt = cnt * 10 + st[i];
    return cnt;
}

int main() {
    cin >> n;
    for (int i = 1; i <= 9; i++) st[i] = i;
    do {
        for (int i = 1; i <= 6; i++) {
            int a = get(1, i);
            for (int j = i + 1; j < 9; j++) {
                int b = get(i + 1, j), c = get(j + 1, 9);
                if (b % c == 0 && a + b / c == n) res++;
            }
        }
    } while (next_permutation(st + 1, st + 10));
    cout << res << endl;
    return 0;
}

