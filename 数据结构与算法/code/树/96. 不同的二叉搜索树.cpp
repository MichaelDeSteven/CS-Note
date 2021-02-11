// 动态规划
class Solution {
public:
    int numTrees(int n) {
        vector<int> f(n + 1, 0);
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                f[i] += f[j] * f[i - j - 1];
            }
        }
        return f[n];
    }
};

// 卡特兰数公式
class Solution {
public:
    int numTrees(int n) {
        long long C = 1;
        for (int i = 0; i < n; i++) {
            C = C * 2 * (2 * i + 1) / (i + 2);
        }
        return C;
    }
};
