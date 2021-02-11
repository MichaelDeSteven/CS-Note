#include<bits/stdc++.h>

using namespace std;
const int N = 20;
double x[N], y[N];
int n, m, path[N][N], f[1 << N];

int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(path, 0, sizeof path);
        memset(f, 0x3f, sizeof f);
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
        
        
        for (int i = 0; i < n; i++) {
            path[i][i] = 1 << i;
            for (int j = 0; j < n; j++) {
                double x1 = x[i], x2 = x[j], y1 = y[i], y2 = y[j];
                if (fabs(x1 - x2) < 1e-8) continue;
                double ta = (y1 / x1 - y2 / x2) / (x1 - x2);
                double tb = y1 / x1 - ta * x1;
                if (ta >= 0) continue;
                int stat = 0;
                for (int k = 0; k < n; k++) {
                    double t = ta * x[k] * x[k] + tb * x[k];
                    if (fabs(y[k] - t) < 1e-8) stat += 1 << k;
                }
                path[i][j] = stat;
            }
        }
            
        f[0] = 0;
        
        for (int i = 0; i < (1 << n); i++) {
            int x = 0;
            for (int j = 0; j < n; j++) {
                if ((i >> j & 1) == 0) {
                    x = j;
                    break;
                }
            }
            
            for (int j = 0; j < n; j++) {
                f[i | path[x][j]] = min(f[i] + 1, f[i | path[x][j]]);
            }
        }
        
        cout << f[(1 << n) - 1] << endl;
    }
    
    return 0;
}
