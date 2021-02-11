class Solution {
public:
    vector<int> asteroidCollision(vector<int>& ast) {
        vector<int> vec;
        for (auto i : ast) {
            // 方向为负才有可能发生碰撞
            if (i < 0) {
                bool coll = false;
                // 栈顶元素为空一定发生碰撞
                while (!vec.empty() && vec.back() > 0) {
                    // 当栈顶元素大于等于当前石头质量绝对值，该石头一定爆炸
                    if (vec.back() >= abs(i)) {
                        coll = true;
                        // 都爆炸
                        if (vec.back() == abs(i)) vec.pop_back(); 
                        break;
                    }
                    vec.pop_back();
                }
                if (coll) continue;
                vec.push_back(i);
            } else vec.push_back(i);
        }
        return vec;
    }
};
