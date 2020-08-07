class Solution {
public:
    int res = 0;

    void cal(vector<int>& f, vector<int>& bound) {
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < f.size(); i++) {
            while (stk.top() != -1 && f[i] <= f[stk.top()]) stk.pop();
            bound[i] = stk.top();
            stk.push(i);
        }
    }

    void solve(vector<int>& ll, vector<int>& rr, vector<int>& f) {
        cal(f, ll);
        reverse(f.begin(), f.end());
        cal(f, rr);
        reverse(f.begin(), f.end());
        reverse(rr.begin(), rr.end());

        for (int i = 0; i < f.size(); i++) {
            // 计算区间长度不包括左右两边因此是右指针-左指针 - 1，且左指针最小是-1全体都要+1
            int len = (f.size() - rr[i]) - (ll[i] - 1) - 1;
            res = max(res, f[i] * len);
        }
    }
    int maximalRectangle(vector<vector<char>>& mat) {
        int n = mat.size();
        // 恶心的特判
        if (!n) return 0;
        int m = mat[0].size();
        vector<int> ll(m), rr(m), f(m, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == '0') f[j] = 0;
                else f[j]++;
            }
            solve(ll, rr, f);
        }
        
        return res;
    }
};
