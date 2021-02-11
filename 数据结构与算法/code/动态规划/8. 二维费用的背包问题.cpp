#include<bits/stdc++.h>

using namespace std;
int f[110][110], N, V, M, v, m, w;

int main() {
    cin >> N >> V >> M;
    for (int i = 1; i <= N; i++) {
        cin >> v >> m >> w;
        for (int j = V; j >= v; j--)
            for (int k = M; k >= m; k--)
                f[j][k] = max(f[j][k], f[j - v][k - m] + w);
    }
    
    cout << f[V][M] << endl;
    return 0;
}
