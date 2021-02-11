#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
const int N = 510;
int n, k, x[N], y[N], p[N];
double d[N];
struct edg {
    int a, b;
    double c;
    bool operator < (const edg& t) const {
        return c < t.c;
    }
}edg[N*N];

double get(int i, int j) {
    return sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]));
}

int find(int x) {
    if (x == p[x]) return p[x];
    return p[x] = find(p[x]);
}

double kruskal() {
    double res = 0;
    sort(edg + 1, edg + 1 + n*n);
    for(int i = 1; i <= n; i++) p[i] = i;
    int cnt = 0;
    
    for (int i = 1; i <= n*n; i++) {
        int a = edg[i].a, b = edg[i].b;
        double c = edg[i].c;
        int x = find(a), y = find(b);
        if (x == y) continue;

        p[x] = y, d[++cnt] = c;        
    }
    return d[max(n - k, 0)];
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int cnt = (i - 1)*n + j;
            edg[cnt].a = i, edg[cnt].b = j, edg[cnt].c = get(i, j);
        }
    printf("%.2lf\n", kruskal());
    return 0;
}
