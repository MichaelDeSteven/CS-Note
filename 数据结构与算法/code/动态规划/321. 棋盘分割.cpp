#include<bits/stdc++.h>

using namespace std;
const int N = 15;
int n;
double s[N][N], f[N][N][N][N][N];
double avg;

double get(int x1, int y1, int x2, int y2) {
    double res = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
    res -= avg;
    return res * res / n;
}

double dfs(int cnt, int x1, int y1, int x2, int y2) {
    double &res = f[cnt][x1][y1][x2][y2];
    if (res >= 0) return res;
    if (cnt == 1) return res = get(x1, y1, x2, y2);
    
    res = 1e9;
    
    // 竖着割
    for (int i = x1; i < x2; i++) {
        res = min(res, get(x1, y1, i, y2) + dfs(cnt - 1, i + 1, y1, x2, y2));
        res = min(res, get(i + 1, y1, x2, y2) + dfs(cnt - 1, x1, y1, i, y2));
    }
    
    // 横着割
    for (int i = y1; i < y2; i++) {
        res = min(res, get(x1, y1, x2, i) + dfs(cnt - 1, x1, i + 1, x2, y2));
        res = min(res, get(x1, i + 1, x2, y2) + dfs(cnt - 1, x1, y1, x2, i));
    }

    return res;
}

int main() {
    cin >> n;
  for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++) {
            cin >> s[i][j];
            s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        }
    memset(f, -1, sizeof f);
    avg = s[8][8] / n;
    printf("%.3lf\n", sqrt(dfs(n, 1, 1, 8, 8)));
    return 0;
}
