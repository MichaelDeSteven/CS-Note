class Trie {
public:
    Trie* son[26];
    int cnt;
    Trie() {
        memset(son, NULL, sizeof son);
        cnt = 0;
    }
    void insert(string str) {
        Trie* p = this;
        for (auto i : str) {
            int u = i - 'a';
            if (!p->son[u]) p->son[u] = new Trie();
            p = p->son[u];
        }
        p->cnt++;
    }
    string query(string str) {
        Trie* p = this;
        string res = "";
        for (auto i : str) {
            int u = i - 'a';
            if (!p->son[u] || p->cnt) break;
            res += (char)('a' + u);
            p = p->son[u];
        }
        if (p->cnt) return res;
        else return str;
    }
};
class Solution {
public:
    string replaceWords(vector<string>& dict, string sent) {
        Trie* root = new Trie();
        for (auto i : dict) root->insert(i);
        string res = "";
        for (int i = 0; i < sent.size(); i++) {
            int j = i;
            while (j < sent.size() && sent[j] != ' ') j++;
            string word = sent.substr(i, j - i);
            res += root->query(word);
            i = j;
            if (i < sent.size()) res += " ";
        }
        return res;
    }
};
