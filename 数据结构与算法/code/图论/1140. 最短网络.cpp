#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 110;
int g[N][N], dist[N], st[N], n;

int prim() {
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j])) t = j;
        st[t] = true;
        res += dist[t];
        
        for (int j = 1; j <= n; j++)
            if (dist[j] > g[t][j]) dist[j] = g[t][j];
    }
    
    return res;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> g[i][j];
        
    cout << prim() << endl;
    return 0;
}
