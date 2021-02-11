#include<bits/stdc++.h>

using namespace std;
const int N = 13;
int d[N];
int f(int x) {
    if (x <= 1) return x;
    return 2*f(x - 1) + 1;
}

int main() {
    memset(d, 0x3f, sizeof d);
    d[0] = 0;
    for (int i = 1; i <= 12; i++) {
        for (int j = 0; j <= i; j++) {
            d[i] = min(d[i], 2*d[j] + f(i - j));
        }
        cout << d[i] << endl;
    }
    
    return 0;
}
