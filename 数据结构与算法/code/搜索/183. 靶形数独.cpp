#include<bits/stdc++.h>

using namespace std;
const int N = 9, M = 1 << N;

int ma[M], ones[M];
int col[N], row[N], cel[N / 3][N / 3];
char str[N * N];
int dict[N][N] = {
    {6, 6, 6, 6,  6, 6, 6, 6, 6},
    {6, 7, 7, 7,  7, 7, 7, 7, 6},
    {6, 7, 8, 8,  8, 8, 8, 7, 6},
    {6, 7, 8, 9,  9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9,  9, 9, 8, 7, 6},
    {6, 7, 8, 8,  8, 8, 8, 7, 6},
    {6, 7, 7, 7,  7, 7, 7, 7, 6},
    {6, 6, 6, 6,  6, 6, 6, 6, 6},
};
int res, flag;

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

void dfs(int cnt, int score) {
    if (!cnt) {
        flag = true;
        res = max(res, score);
        return;
    }
    
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
        dfs(cnt - 1, score + (t + 1) * dict[x][y]);
        draw(x, y, t, false);
    }
}
int main() {
    for (int i = 0; i < N; i++) ma[1 << i] = i;
    for (int i = 0; i < 1 << N; i++)
        for (int j = 0; j < N; j++) ones[i] += i >> j & 1;
    init();
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c;
            cin >> c;
            if (c == '0') str[i * N + j] = '.';
            else str[i * N + j] = c;
        }
    }
        
    int cnt = 0, res1 = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (str[i * N + j] != '.') {
                res1 += (str[i*N + j] - '0') * dict[i][j];
                draw(i, j, str[i * N + j] - '1', true);
            }
            else cnt++;
            
    dfs(cnt, res1);
    if (!flag) res = -1;
    cout << res << endl;
    return 0;
}
