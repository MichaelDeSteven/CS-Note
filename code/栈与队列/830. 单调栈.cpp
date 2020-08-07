#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 100010;
int stk[N], a[N], hh, n;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for (int i = 1; i <= n; i++) {
        // 栈顶的值比当前值小，显然以后的值左边第一个最小的元素一定不会是栈顶元素
        while (hh && a[stk[hh]] >= a[i]) --hh;
        
        if (hh) cout << a[stk[hh]] << ' ';
        else cout << "-1" << ' ';
        
        stk[++hh] = i;
    }
    return 0;
}
