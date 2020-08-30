class Trie {
public:
    /** Initialize your data structure here. */
    Trie* son[26];
    int cnt;
    Trie() {
        memset(son, NULL, sizeof son);
        cnt = 0;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* p = this;
        for (auto i : word) {
            int u = i - 'a';
            if (!p->son[u]) p->son[u] = new Trie();
            p = p->son[u];
        }
        p->cnt++;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* p = this;
        for (auto i : word) {
            int u = i - 'a';
            if (!p->son[u]) return false;
            p = p->son[u];
        }
        return p->cnt;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* p = this;
        for (auto i : prefix) {
            int u = i - 'a';
            if (!p->son[u]) return false;
            p = p->son[u];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
