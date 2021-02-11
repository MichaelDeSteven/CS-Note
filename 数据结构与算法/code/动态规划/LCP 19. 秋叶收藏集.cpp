class Solution {
public:
    int minimumOperations(string ll) {
        int n = ll.size();
        int f[n][3];
        f[0][0] = (ll[0] == 'y');
        for (int i = 1; i < n; i++) {
            f[i][0] = f[i - 1][0] + (ll[i] == 'y');
            f[i][1] = f[i - 1][0] + (ll[i] == 'r');
            if (i > 1) {
                f[i][1] = min(f[i][1], f[i - 1][1] + (ll[i] == 'r'));
                f[i][2] = f[i - 1][1] + (ll[i] == 'y');
            }
            if (i > 2) {
                f[i][2] = min(f[i][2], f[i - 1][2] + (ll[i] == 'y'));
            }
        }
        return f[n - 1][2];
    }
};
