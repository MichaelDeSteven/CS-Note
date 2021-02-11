#include<bits/stdc++.h>

using namespace std;
const int N = 110;
string str1, str2;
int cnt1, cnt2;
int main() {
    cin >> str1 >> str2;
    string s1 = str1, s2 = str2;
    for (int i = 1; i < s1.size(); i++) {
        if (s1[i] == s2[i]) continue;
        if (s1[i] == '*') s1[i] = 'o';
        else s1[i] = '*';
        if (i + 1 < s1.size()) {
            if (s1[i + 1] == '*') s1[i + 1] = 'o';
            else s1[i + 1] = '*';            
        }
        cnt1++;
    }
    if (s1 != s2) cnt1 = N;
    s1 = str1, s2 = str2;
    for (int i = s1.size() - 1; i >= 0; i--) {
        if (s1[i] == s2[i]) continue;
        if (s1[i] == '*') s1[i] = 'o';
        else s1[i] = '*';
        if (i) {
            if (s1[i - 1] == '*') s1[i - 1] = 'o';
            else s1[i - 1] = '*';            
        }
        cnt2++;
    }
    if (s1 != s2) cnt2 = N;
    cout << min(cnt1, cnt2) << endl;
    return 0;
}
