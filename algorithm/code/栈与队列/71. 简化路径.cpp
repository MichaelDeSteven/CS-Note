class Solution {
public:
    string simplifyPath(string path) {
        string res = "/";
        vector<string> stk;
        for (int i = 0; i < path.size(); i++) {
            int j = i;
            // 找斜杠
            while (j < path.size() && path[j] == '/') j++;
            i = j;
            // 找文件名
            while (j < path.size() && path[j] != '/') j++;
            string str = path.substr(i, j - i);
            i = j - 1;
            // ..即为栈顶的文件名
            if (str == ".." && stk.size()) stk.pop_back();
            else if (str != "." && str != ".." && str.size()) stk.push_back(str);
        }

        for (int i = 0; i < stk.size(); i++) {
            res = res + stk[i];
            if (i != stk.size() - 1) res += "/";
        }
        return res;
    }
};
