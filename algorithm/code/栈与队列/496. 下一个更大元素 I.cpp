class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        // 存放nums1元素在num2的下一个比它大的数
        unordered_map<int, int> ma;
        stack<int> stk;
        // 逆序实现了单调栈查找右边最近的最大/最小的数
        for (int i = nums2.size() - 1; i >= 0; i--) {
            while (!stk.empty() && nums2[i] >= nums2[stk.top()]) stk.pop();
            if (stk.empty()) ma[nums2[i]] = -1;
            else ma[nums2[i]] = nums2[stk.top()];

            stk.push(i);
        }

        vector<int> res;
        for (auto i : nums1) res.push_back(ma[i]);
        return res;
    }
};
