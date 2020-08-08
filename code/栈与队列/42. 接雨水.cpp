// 解法1：计算每一列最长的水柱长度（找到左右两边的最大值） 暴力方式
class Solution {
public:
    int trap(vector<int>& h) {
        int res = 0;
        for (int i = 0; i < h.size(); i++) {
            int lh = 0;
            for (int j = i; j >= 0; j--) {
                lh = max(h[j], lh);
            }
            int rh = 0;
            for (int j = i; j < h.size(); j++) {
                rh = max(h[j], rh);
            }
            res += min(rh, lh) - h[i];
        }
        return res;
    }
};

// 解法2：用动态规划的思想，预处理每一列的左右最大值
class Solution {
public:
    int trap(vector<int>& h) {
        vector<int> ll(h.size()), rr(h.size());
        for (int i = 0; i < h.size(); i++) {
            // max(i - 1, 0)防止越界
            ll[i] = max(ll[max(i - 1, 0)], h[i]);
        }
        int len = h.size();
        for (int i = len - 1; i >= 0; i--) {
            // min(i + 1, len - 1)防止越界
            rr[i] = max(h[i], rr[min(i + 1, len - 1)]);
        }
        int res = 0;
        for (int i = 0; i < h.size(); i++) {
            res += min(ll[i], rr[i]) - h[i];
        }
        return res;
    }
};

// 解法3：单调栈
class Solution {
public:
    int trap(vector<int>& h) {
        stack<int> stk;
        int res = 0;
        for (int i = 0; i < h.size(); i++) {
            while (!stk.empty() && h[i] > h[stk.top()]) {
                int val = h[stk.top()];
                stk.pop();
                if (stk.empty()) break;
                int len = i - stk.top() - 1;
                int hh = min(h[stk.top()], h[i]) - val;
                res += len * hh;
            }
            stk.push(i);
        }
        return res;
    }
};
