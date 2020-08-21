#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100010;

int h = -1, inx, e[N], ne[N];

int main() {
    int m;
    cin >> m;
    while (m--) {
        string str;
        int a, b;
        cin >> str;
        if (str == "H") {
            cin >> a;
            e[inx] = a, ne[inx] = h, h = inx++;
        } else if (str == "I") {
            cin >> a >> b;
            e[inx] = b, ne[inx] = ne[a - 1], ne[a - 1] = inx++;
        } else if (str == "D") {
            cin >> a;
            if (a == 0) {
                h = ne[h];
            } else {
                ne[a - 1] = ne[ne[a - 1]];
            }
        }
    }
    for (int i = h; i != -1; i = ne[i]) cout << e[i] << ' ';
    cout << endl;    
    return 0;
}
