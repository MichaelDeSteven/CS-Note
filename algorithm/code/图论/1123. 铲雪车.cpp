#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int N = 10;
int sx, sy;

int main() {
    double res = 0;
    int a, b, c, d;
    cin >> sx >> sy;
    while (scanf("%d %d %d %d", &a, &b, &c, &d) != EOF) {
        res += sqrt((LL)(a - c) * (a - c) + (LL)(b - d) * (b - d)) * 2;
    }
    
    res /= 20000;

    int hour = (int)res, mins = (res - hour) * 60 + 0.5;
    printf("%d:%02d", hour, mins);
    
    return 0;
}
