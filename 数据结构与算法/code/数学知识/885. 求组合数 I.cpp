#include<bits/stdc++.h>

using namespace std;
const int N = 2010, MOD = 1e9 + 7;
int C[N][N], a, b;

int main() {
    C[0][0] = 1;
    for (int i = 1; i < N; i++)
        for (int j = 0; j <= i; j++)
            if (!j) C[i][j] = 1;
            else C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
            
    
    int t;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        cout << C[a][b] << endl;
    }
    
    
    return 0;
}
