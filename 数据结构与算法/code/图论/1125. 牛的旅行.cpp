#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>

using namespace std;
const int N = 155;
#define INF 0x3f3f3f3f
double g[N][N], x[N], y[N], d[N];
int n;

double get(int a, int b) {
    double dx = x[a]  - x[b], dy = y[a] - y[b];
    return sqrt(dx * dx + dy * dy);
}

void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (g[i][j] < INF / 2) d[i] = max(d[i], g[i][j]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j) g[i][j] = INF;
            else g[i][j] = 0;
            
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < str.size(); j++) {
            int t = str[j] - '0';
            if (t) {
                g[i][j + 1] = g[j + 1][i] = get(i, j + 1);
            }
        }
    }
    floyd();
    double res1 = 0;
    for (int i = 1; i <= n; i++) res1 = max(res1, d[i]);
    double res2 = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (g[i][j] > INF / 2) {
                res2 = min(d[i] + d[j] + get(i, j), res2);
            }
        }
    }

    printf("%.6lf\n", max(res1, res2));
    return 0;
}
