class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        vector<int> res;
        stack<int> stk;
        for (int i = T.size() - 1; i >= 0; i--) {
            while (!stk.empty() && T[i] >= T[stk.top()]) stk.pop();
            if (stk.empty()) res.push_back(0);
            else res.push_back(stk.top() - i);
            stk.push(i);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
