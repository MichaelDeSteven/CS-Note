class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        // 将循环数组变成两段
        for (int i = 0; i < n; i++) nums.push_back(nums[i]);

        vector<int> res;
        stack<int> stk;
        for (int i = 2 * n - 1; i >= 0; i--) {
            while (!stk.empty() && nums[i] >= nums[stk.top()]) stk.pop();
            // 循环数组只需处理原来一段即可
            if (i < n) {
                if (stk.empty()) res.push_back(-1);
                else res.push_back(nums[stk.top()]);
            }
            stk.push(i);
        }
        // 由于是逆序查找，需要reverse
        reverse(res.begin(), res.end());
        return res;
    }
};
