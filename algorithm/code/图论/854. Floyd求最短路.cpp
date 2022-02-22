#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>

using namespace std;
const int N = 210;
#define INF 0x3f3f3f3f
int g[N][N], n, m, k;

void floyd() {
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}
int main() {
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i != j) g[i][j] = INF;
            
            
    while(m--){
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = min(g[a][b], c);
    }
    floyd();
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        if (g[x][y] > 0x3f3f3f3f / 2) cout << "impossible" << endl;
        else cout << g[x][y] << endl;
    }
    
    return 0;
}
