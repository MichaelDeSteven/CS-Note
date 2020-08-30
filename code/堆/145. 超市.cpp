#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int, int> PII;
#define INF 0x3f3f3f3f
int n;
int main() {
    while (scanf("%d", &n) != EOF) {
        vector<PII> vec;
        priority_queue<PII, vector<PII>, greater<PII>> q;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            vec.push_back({y, x});
        }
        sort(vec.begin(), vec.end());
        for (auto t : vec) {
            q.push({t.second, t.first});
            if (t.first < q.size()) q.pop();
        }
        int res = 0;
        while (!q.empty()) {
            auto t = q.top();
            q.pop();
            res += t.first;
        }
        cout << res << endl;
    }
    
    return 0;
}

// 堆顶维护每天要买的商品，按过期从小到大排序，再按利润从小到大
// 将当前商品加入堆，若该过期时间大于或等于集合大小说明集合所有元素均能卖完
// 出堆的一定都是要过期且价值低的物品
