#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 31;
LL f[N][N][N][N][N], n;
int row[N];

int main() {
    while (cin >> n, n) {
        memset(f, 0, sizeof f);
        memset(row, 0, sizeof row);
        
        for (int i = 0; i < n; i++) cin >> row[i];
        
        f[0][0][0][0][0] = 1;
        for (int a = 0; a <= row[0]; a++) {
            for (int b = 0; b <= min(row[1], a); b++) {
                for (int c = 0; c <= min(row[2], b); c++) {
                    for (int d = 0; d <= min(row[3], c); d++) {
                        for (int e = 0; e <= min(row[4], d); e++) {
                            if (a > 0 && a - 1 >= b) f[a][b][c][d][e] += f[a - 1][b][c][d][e];
                            if (b > 0 && b - 1 >= c) f[a][b][c][d][e] += f[a][b - 1][c][d][e];
                            if (c > 0 && c - 1 >= d) f[a][b][c][d][e] += f[a][b][c - 1][d][e];
                            if (d > 0 && d - 1 >= e) f[a][b][c][d][e] += f[a][b][c][d - 1][e];
                            if (e > 0) f[a][b][c][d][e] += f[a][b][c][d][e - 1];
                        }
                    }
                }
            }
        }
        
        cout << f[row[0]][row[1]][row[2]][row[3]][row[4]] << endl;
    }
    return 0;
}
