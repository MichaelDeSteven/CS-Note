#include<bits/stdc++.h>

using namespace std;

const int N = 10;
typedef pair<string, char> PSC;
char op[3] = {'A', 'B', 'C'};
unordered_map<string, int> ma;
unordered_map<string, PSC> pre;
int res = 1;
char g[N][N], tmp[N][N], path[N];
string str;

string toStr() {
    string str = "";
    for (int j = 1; j <= 4; j++) str += tmp[1][j];
    for (int j = 4; j >= 1; j--) str += tmp[2][j];
    return str;
}

string mov1(string str){
    return str.substr(7, 1) + str.substr(6, 1) + str.substr(5, 1) + str.substr(4, 1)
    + str.substr(3, 1) + str.substr(2, 1) + str.substr(1, 1) + str.substr(0, 1);
}
string mov2(string str){
    return str.substr(3, 1) + str.substr(0, 3) + str.substr(5, 1) + str.substr(6, 1)
    + str.substr(7, 1) + str.substr(4, 1);
}
string mov3(string str){
    return str.substr(0, 1) + str.substr(6, 1) + str.substr(1, 1) + str.substr(3, 1)
     + str.substr(4, 1) + str.substr(2, 1) + str.substr(5, 1) + str.substr(7, 1);
}

void bfs() {
    queue<string> q;
    q.push("12345678");
    ma["12345678"] = 0;
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 1; i <= sz; i++) {
            auto t = q.front();
            q.pop();
            if (t == str) return;
            
            string s[3] = { mov1(t), mov2(t), mov3(t) };
            for (int i = 0; i < 3; i++) {
                if (!ma.count(s[i])) {
                    pre[s[i]] = {t, op[i]};
                    ma[s[i]] = res;
                    q.push(s[i]);
                }
            }
        }
        res++;
    }
}

int main() {
    for (int i = 1; i <= 8; i++) {
        char c;
        cin >> c;
        str += c;
    }

    bfs();
    
    cout << ma[str] << endl;
    string path = "";
    while (str != "12345678") {
        path = pre[str].second + path;
        str = pre[str].first;
    }
    if (path != "") cout << path << endl;
    return 0;
}


