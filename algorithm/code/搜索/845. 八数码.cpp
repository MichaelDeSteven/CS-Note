#include<bits/stdc++.h>

using namespace std;

const int N = 10;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
char g[N][N];
int res, flag;
unordered_set<string> se;

string toStr(char tmp[][N]) {
    string res = "";
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            res += g[i][j];
        }
    }

        
    return res;
}

int toArr(string tmp) {
    int res = 0;
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++) {
            g[i][j] = tmp[(i - 1)*3 + j - 1];
            if (g[i][j] == 'x') res = (i - 1)*3 + j - 1;
        }
    return res;
}

void bfs() {
    queue<string> q;
    string str = toStr(g);
    q.push(str);
    se.insert(str);

    while (!q.empty()) {
        int sz = q.size();
        
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            if (t == "12345678x") {
                flag = true;
                return;
            }
            int pos = toArr(t);
            int u = pos / 3 + 1, v = (pos % 3) + 1;
            for (int j = 0; j < 4; j++) {
                int x = dx[j] + u, y = dy[j] + v;
                if (x <= 0 || y <= 0 || x > 3 || y > 3) continue;
                swap(g[u][v], g[x][y]);
                string str = toStr(g);
                swap(g[u][v], g[x][y]);
                if (se.count(str)) continue;
                se.insert(str);
                q.push(str);
            }
        }
        
        res++;
    }
}

int main() {
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++) cin >> g[i][j];
        
    bfs();
        
    if (!flag) res = -1;
    cout << res << endl;
    
    return 0;
}
