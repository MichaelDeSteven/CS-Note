#include<bits/stdc++.h>

using namespace std;
const int N = 9, M = 1 << N;

int ma[M], ones[M];
int col[N], row[N], cel[N / 3][N / 3];
string str;

int lowbit(int x) {
    return x & -x;
}

int get(int x, int y) {
    return row[x] & col[y] & cel[x / 3][y / 3];    
}

void init() {
    for (int i = 0; i < N; i++) row[i] = col[i] = (1 << N) - 1;
    
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cel[i][j] = (1 << N) - 1;
}

void draw(int x, int y, int t, bool is_set) {
    if (is_set) str[x * N + y] = t + '1';
    else str[x * N + y] = '.';
    
    int v = 1 << t;
    if (!is_set) v = -v;
    
    row[x] -= v, col[y] -= v, cel[x / 3][y / 3] -= v;
}

bool dfs(int cnt) {
    if (!cnt) return true;
    
    int minv = 10, x, y;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (str[i * N + j] == '.') {
                int stat = get(i, j);
                if (ones[stat] < minv) {
                    minv = ones[stat];
                    x = i, y = j;
                }
            }
    int stat = get(x, y);
    
    for (int i = stat; i; i -= lowbit(i)) {
        int t = ma[lowbit(i)];
        draw(x, y, t, true);
        if (dfs(cnt - 1)) return true;
        draw(x, y, t, false);
    }
    return false;
}
int main() {
    for (int i = 0; i < N; i++) ma[1 << i] = i;
    for (int i = 0; i < 1 << N; i++)
        for (int j = 0; j < N; j++) ones[i] += i >> j & 1;
        
    while (cin >> str, str != "end") {
        init();
        
        int cnt = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (str[i * N + j] != '.') draw(i, j, str[i * N + j] - '1', true);
                else cnt++;
                
        dfs(cnt);
        
        cout << str << endl;
    }
    
    return 0;
}
