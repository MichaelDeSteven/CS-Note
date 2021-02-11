## 剑指Offer总结

### 数组中重复的元素

描述：在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

```cpp
输入：
[2, 3, 1, 0, 2, 5, 3]
输出：2 或 3 
```

**解题思路**

对于这种元素在[0, n-1]范围的数组，可以将值为i的元素调整到第i个位置上

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            while (i != nums[i]) {
                if (nums[nums[i]] == nums[i]) return nums[i];
                swap(nums[i], nums[nums[i]]);
            }
        }
        return -1;
    }
};
```

[数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof) 



### 二维数组中的查找

描述：在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

```cpp
[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target = 5，返回 true。

给定 target = 20，返回 false。
```

**解题思路**

* 分治：每个点的左上方向都小于等于该点，右下都大于等于该点

时间复杂度：$O(nlogn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    bool dfs(vector<vector<int>>& matrix, int r1, int c1, int r2, int c2, int target) {
        if (r1 > r2 || c1 > c2) return false;
        int midr = r1 + r2 >> 1, midc = c1 + c2 >> 1;
        if (matrix[midr][midc] == target) return true;
        else if (matrix[midr][midc] > target) {
            return dfs(matrix, r1, c1, r2, midc - 1, target) ||
            dfs(matrix, r1, c1, midr - 1, c2, target);
        } else {
            return dfs(matrix, midr + 1, c1, r2, c2, target) ||
            dfs(matrix, r1, midc + 1, r2, c2, target);
        }
    }
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;
        int n = matrix.size(), m = matrix[0].size();
        return dfs(matrix, 0, 0, n - 1, m - 1, target);
    }
};
```



* 线性查找：从右上角开始，若比该点小，则往左边移动一格，比该点大，则往下边移动一格

时间复杂度：*O(n + m)*

空间复杂度：*O(1)*

```cpp
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;
        int n = matrix.size(), m = matrix[0].size();
        int r = 0, c = m - 1;
        while (c >= 0 && r < n) {
            if (target == matrix[r][c]) return true;
            else if (target > matrix[r][c]) r++;
            else c--; 
        }
        return false;
    }
};
```

[二维数组中的查找](https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof) 



### 替换空格

描述：请实现一个函数，把字符串 `s` 中的每个空格替换成"%20"。

```cpp
输入：s = "We are happy."
输出："We%20are%20happy."
```

**解题思路**

简单地模拟一下就好了

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    string replaceSpace(string s) {
        string res = "";
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == ' ') res += "%20";
            else res += s[i];
        }
        return res;
    }
};
```

[替换空格](https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof)



### 从尾到头打印链表

描述：输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

**解题思路**

递归遍历链表

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> res;
    void traverse(ListNode* head) {
        if (!head) return;
        traverse(head->next);
        res.push_back(head->val);
    }
    vector<int> reversePrint(ListNode* head) {
        traverse(head);
        return res;
    }
};
```



[从尾到头打印链表](https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof)



### 重建二叉树

描述：输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

```
前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

    3
   / \
  9  20
    /  \
   15   7
```

**解题思路**

以前序遍历的当前值来确定根节点，对中序遍历的数组进行分治

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    unordered_map<int, int> ma;
    TreeNode* merge(vector<int>& pre, vector<int>& ino, int pl, int pr, int il, int ir) {
        if (pl > pr || il > ir) return NULL;
        TreeNode* root = new TreeNode(pre[pl]);
        int inx = ma[pre[pl]], sz = inx - il;
        root->left = merge(pre, ino, pl + 1, pl + sz, il, inx - 1);
        root->right = merge(pre, ino, pl + sz + 1, pr, inx + 1, ir);
        return root;
    }
    TreeNode* buildTree(vector<int>& pre, vector<int>& ino) {
        for (int i = 0; i < ino.size(); i++) {
            ma[ino[i]] = i;
        }
        return merge(pre, ino, 0, pre.size() - 1, 0, ino.size() - 1);
    }
};
```



[重建二叉树](https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof)





### 用两个栈实现队列

描述：用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )

```cpp
示例 1：

输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]
示例 2：

输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]
```



**解题思路**

* appendTail：直接加入优先栈
* deleteHead：将优先栈的值弹出到另一个栈，然后删除栈顶元素，再把值再弹出到优先栈

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class CQueue {
public:
    int priorStk[10010], stk[10010];
    int sz;
    CQueue() {
        sz = 0;
    }
    
    void appendTail(int value) {
        priorStk[++sz] = value;
    }
    
    int deleteHead() {
        if (!sz) return -1;
        int t = 0;
        while (sz) {
            stk[++t] = priorStk[sz--];
        }
        int res = stk[t--];
        while (t) {
            priorStk[++sz] = stk[t--];
        }
        return res;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
```



[用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof)



### 斐波那契数列&青蛙跳台阶问题

描述：写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

**解题思路**

动态规划

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    int fib(int n) {
        int f[110];
        f[0] = 0, f[1] = 1;
        for (int i = 2; i <= n; i++) f[i] = (f[i - 1] + f[i - 2]) % 1000000007;
        return f[n];
    }
};
```



[斐波那契数列](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof)

[青蛙跳台阶问题](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof) 



### 旋转数组的最小数字

描述：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

```cp
示例 1：

输入：[3,4,5,1,2]
输出：1
示例 2：

输入：[2,2,2,0,1]
输出：0
```

**解题思路**

二分

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int ll = 0, rr = numbers.size() - 1;
        while (ll < rr) {
            int mid = ll + rr >> 1;
            if (numbers[mid] == numbers[rr]) rr--;
            else if (numbers[mid] > numbers[rr]) ll = mid + 1;
            else rr = mid;
        }
        return numbers[ll];
    }
};
```



[旋转数组的最小数字](https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof)

[拓展](https://blog.csdn.net/Trista__/article/details/112692089)

### 矩阵中的路径

**解题思路**

深搜+回溯

时间复杂度：$O(nm)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int st[210][210];
    int n, m;
    bool dfs(vector<vector<char>>& board, int u, int v, int inx, string word) {
        if (inx == word.size()) return true;
        for (int i = 0; i < 4; i++) {
            int x = u + dx[i], y = v + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= m || word[inx] != board[x][y] || st[x][y]) continue;
            st[x][y] = true;
            if (dfs(board, x, y, inx + 1, word)) return true;
            st[x][y] = false;
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        memset(st, 0, sizeof st);
        n  = board.size(), m = board[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0]) {
                    st[i][j] = true;
                    if (dfs(board, i, j, 1, word)) return true;
                    st[i][j] = false;
                }
            }
        }
        return false;
    }
};
```



[矩阵中的路径](https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof) 



### 机器人的运动范围



**解题思路**

深搜

时间复杂度：$O(nm)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int f[110][110] = {0}, vis[110][110] = {0}, cnt, N, M;
    int get(int x) {
        int res = 0; 
        while (x) {
            res += x % 10;
            x /= 10;
        }
        return res;
    }
    void dfs(int u, int v) {
        if (u < 0 || v < 0 || u >= M || v >= N || vis[u][v] || !f[u][v]) return;
        cnt++;
        vis[u][v] = 1;
        dfs(u + 1, v);
        dfs(u - 1, v);
        dfs(u, v + 1);
        dfs(u, v - 1); 
    }
    int movingCount(int m, int n, int k) {
        N = n, M = m;
        cnt = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int t = 0;
                t = get(i) + get(j);
                if (t <= k) f[i][j] = 1; 
            }
        }
        dfs(0, 0);
        return cnt;
    }
};
```

[机器人的运动范围](https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof) 





### 剪绳子&剪绳子 II

描述：给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

**解题思路**

* 动态规划

时间复杂度：$O(n^3)$

空间复杂度：$O(n^2)$

```cpp
// f[i][j]表示长度为i的绳子分成j段得到的最大乘积
// 初始化，j=1最大乘积为本身，其它乘积为1
// 由题意得到j < i
class Solution {
public:
    int cuttingRope(int n) {
        vector<vector<int>> f(100, vector<int>(100, 1));
        for (int i = 1; i <= n; i++) f[i][1] = i;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                for (int k = 1; k < i; k++) {
                    f[i][j] = max(f[i][j], f[i - k][j - 1] * k);
                }
            }
        }
        int res = 0;
        for (int i = 2; i <= n; i++) {
            res = max(res, f[n][i]);
        }
        return res;
    }
};
```

* 贪心

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int cuttingRope(int n) {
        if (n < 4) return n - 1;
        if (n == 4) return n;
        long long res = 1;
        while (n > 4) {
            res = (res * 3) % 1000000007;
            n -= 3;
        }
        return (res * n) % 1000000007;
    }
};
```



[剪绳子](https://leetcode-cn.com/problems/jian-sheng-zi-lcof)

[剪绳子 II](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof) 





### 二进制中1的个数

**解题思路**

* 逐位判断

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n) {
            if (n & 1) res++;
            n >>= 1;
        }
        return res;
    }
};
```

[二进制中1的个数](https://leetcode-cn.com/problems/er-jin-zhi-zhong-1de-ge-shu-lcof)



### 数值的整数次方

**解题思路**

* 快速幂：先将指数项化为正数，再用快速幂模板计算出结果

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        long long exp = abs(n);
        if (n < 0) x = 1 / x;
        double base = x, res = 1;
        while (exp) {
            if (exp & 1) res = res * base;
            base = base * base;
            exp >>= 1;
        }
        return res;
    }
};
```



[数值的整数次方](https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof)



### 打印从1到最大的n位数

描述：输入数字 `n`，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

**解题思路**

简单模拟

时间复杂度：$O(10^n)$

空间复杂度：$O(10^n)$

```cpp
class Solution {
public:
    vector<int> printNumbers(int n) {
        int dict[110];
        dict[1] = 10;
        for (int i = 2; i < 10; i++) dict[i] = dict[i - 1] * 10;
        vector<int> res;
        for (int i = 1; i < dict[n]; i++) {
            res.push_back(i);
        } 
        return res;
    }
};
```



[打印从1到最大的n位数](https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof) 



### 删除链表的节点

描述：给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

返回删除后的链表的头节点。

```cpp
示例 1:

输入: head = [4,5,1,9], val = 5
输出: [4,1,9]
解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
示例 2:

输入: head = [4,5,1,9], val = 1
输出: [4,5,9]
解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.
```

**解题思路**

头结点法：给链表增加一个头结点，判断当前结点的下一结点是否为目标结点，是则直接删除

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* h = new ListNode(-1), *t = h;
        h->next = head;
        while (t && t->next) {
            if (t->next->val == val) {
                t->next = t->next->next;
                break;
            }
            t = t->next;
        }
        return h->next;
    }
};
```



[删除链表的节点](https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof)





### 正则表达式匹配

描述：请实现一个函数用来匹配包含'. '和'\*'的正则表达式。模式中的字符'.'表示任意一个字符，而'\*'表示它前面的字符可以出现任意次（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac\*a"匹配，但与"aa.a"和"ab\*a"均不匹配。

```cpp
示例 1:

输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:

输入:
s = "aa"
p = "a*"
输出: true
解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:

输入:
s = "ab"
p = ".*"
输出: true
解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
示例 4:

输入:
s = "aab"
p = "c*a*b"
输出: true
解释: 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
示例 5:

输入:
s = "mississippi"
p = "mis*is*p*."
输出: false

输入:
s = "aaa"
p = ".*"
输出: true
s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母以及字符 . 和 *，无连续的 '*'
```



**解题思路**

* 动态规划：设$f[i + 1][j + 1]$表示$s[0...i]$与$p[0...j]$是否匹配
* 初始化，考虑字符串为空的情况，$f[0][0] = 1$表示空字符串，$ f[0][j] = f[0][j - 2]$ && $p[j - 2]$ 等于字符\*
* 当$s[i - 1] == p[j - 1]$或者$p[j]$为字符. ，$f[i][j] = f[i - 1][j - 1]$
* $p[j - 1]$为字符\*与$p[j - 2]$进行匹配
  * 匹配0次，$f[i][j] = f[i][j - 2]$
  * 匹配1次，$f[i][j] = f[i][j - 1]$&&($ p[j - 2] = s[i - 1]$或者$p[j - 2]$等于字符.)
  * 匹配n次（$n>1$），$f[i][j] = f[i - 1][j] $&&($ p[j - 2] = s[i - 1]$或者$p[j - 2]$等于字符.)

时间复杂度：$O(nm)$

空间复杂度：$O(nm)$

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, false));
        f[0][0] = true;
        for (int i = 2; i <= m; i += 2) f[0][i] = f[0][i - 2] && p[i - 1] == '*';
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == '.' || (p[j - 1] == s[i - 1])) {
                    f[i][j] = f[i - 1][j - 1];
                } else if (j >= 2 && p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (p[j - 2] == s[i - 1] || p[j - 2] == '.') 
                        f[i][j] |= f[i][j - 1] || f[i - 1][j];
                }
            }
        }
        return f[n][m];
    }
};
```



[正则表达式匹配](https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof)





### 表示数值的字符串

[表示数值的字符串](https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof)





### 调整数组顺序使奇数位于偶数前面

描述：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

```cpp
输入：nums = [1,2,3,4]
输出：[1,3,2,4] 
注：[3,1,2,4] 也是正确的答案之一。
```



**解题思路**

* 双指针：首尾指针

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        vector<int> res(nums);
        int ll = 0, rr = nums.size() - 1;
        for (auto t : nums) {
            if (t & 1) res[ll++] = t;
            else res[rr--] = t;
        }
        return res;
    }
};
```



[调整数组顺序使奇数位于偶数前面](https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof)



### 链表中倒数第k个节点

描述：输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。

```cpp
给定一个链表: 1->2->3->4->5, 和 k = 2.

返回链表 4->5.
```

**解题思路**

* 双指针：快慢指针

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* f = head, *s = head;
        for (int i = 0; i < k; i++) s = s->next;
        while (s) {
            s = s->next;
            f = f->next;
        }
        return f;
    }
};
```



[链表中倒数第k个节点](https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof) 





### 反转链表

描述：定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

```cpp
输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL
```

**解题思路**

* 头结点法

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* hh = new ListNode(-1), *t = head;
        while (t) {
            ListNode* tmp = t;
            t = t->next;
            tmp->next = hh->next;
            hh->next = tmp;
        }
        return hh->next;
    }
};
```

* 迭代

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head, *pre = NULL, *tmp = head;
        while (cur) {
            tmp = tmp->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};
```



* 递归

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverse(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* newHead = reverse(head->next);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
    ListNode* reverseList(ListNode* head) {
        return reverse(head);
    }
};
```





[反转链表](https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof)





### 合并两个排序的链表

描述：输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

```cpp
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
```



**解题思路**

* 分治

时间复杂度：$O(N+M)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* res = new ListNode(-1);
        ListNode* p = l1, *q = l2, *hh = res;
        while (p && q) {
            if (p->val <= q->val) {
                res->next = p;
                p = p->next;
            } else {
                res->next = q;
                q = q->next;
            }
            res = res->next;
        }
        if (q) res->next = q;
        else res->next = p;
        return hh->next;
    }
};
```



[合并两个排序的链表](https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof) 





### 树的子结构

描述：输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

    例如:
    给定的树 A:
         3
        / \
       4   5
      / \
     1   2
    给定的树 B：
    
       4 
      /
     1
    返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

**解题思路**

* 递归+树的遍历

时间复杂度：$O(NM)$其中N为遍历A树花费的时间，M为遍历B树所花费的时间

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool dfs(TreeNode* A, TreeNode* B) {
        if (!A && B) return false;
        if (!A || !B) return true;
        return A->val == B->val && dfs(A->left, B->left) && dfs(A->right, B->right);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) return false;
        return (A->val == B->val && dfs(A, B)) || 
        isSubStructure(A->left, B) || isSubStructure(A->right, B);
    }
};
```



[树的子结构](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof) 





### 二叉树的镜像

描述：请完成一个函数，输入一个二叉树，该函数输出它的镜像。

例如输入：

```cpp
请完成一个函数，输入一个二叉树，该函数输出它的镜像。

例如输入：

     4
   /   \
  2     7
 / \   / \
1   3 6   9
镜像输出：

     4
   /   \
  7     2
 / \   / \
9   6 3   1
```



**解题思路**

* 递归定义镜像二叉树：每个节点都到了它的镜像处

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void dfs(TreeNode* root) {
        if (!root) return;
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        dfs(root->left);
        dfs(root->right);
    }
    TreeNode* mirrorTree(TreeNode* root) {
        dfs(root);
        return root;
    }
};
```



[二叉树的镜像](https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof) 





### 对称的二叉树

描述：请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。

```cpp
例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

    1

   / \
  2   2
 / \ / \
3  4 4  3
但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

    1

   / \
  2   2
   \   \
   3    3
```





**解题思路**

* 递归定义镜像二叉树：每个节点都到了它的镜像处

时间复杂度：$O(N)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool dfs(TreeNode* ll, TreeNode* rr) {
        if (!ll && !rr) return true;
        if (!ll || !rr) return false;
        return (ll->val == rr->val) && dfs(ll->left, rr->right) && dfs(ll->right, rr->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (!root) return true;
        return dfs(root->left, root->right);
    }
};
```

[对称的二叉树](https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof)





### 顺时针打印矩阵

描述：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

**解题思路**

* 模拟+边界判断

时间复杂度：$O(NM)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (!matrix.size() || !matrix[0].size()) return {};
        int n = matrix.size(), m = matrix[0].size();
        vector<int> res;
        int r = m - 1, d = n - 1, l = 0, u = 0; 
        // 右-下-左-上
        while (true) {
            for (int i = l; i <= r; i++) res.push_back(matrix[u][i]);
            if (++u > d) break;
            for (int i = u; i <= d; i++) res.push_back(matrix[i][r]);
            if (--r < l) break;
            for (int i = r; i >= l; i--) res.push_back(matrix[d][i]);
            if (--d < u) break;
            for (int i = d; i >= u; i--) res.push_back(matrix[i][l]);
            if (++l > r) break;
        }
        return res;
    }
};
```



[顺时针打印矩阵](https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof) 





### 包含min函数的栈

描述：定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

**解题思路**

* 栈的性质：设置一个存放最小值的栈，压入的值若大于最小值栈的栈顶的值则一定不是当前的最小值，所以不用压入，弹出时，若两个栈顶的值相同则说明是同一个压入的值两个栈都弹出

时间复杂度：$O(1)$

空间复杂度：$O(1)$

```cpp
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> minStk, stk;

    MinStack() {
    }
    
    void push(int x) {
        stk.push(x);
        if (minStk.empty() || minStk.top() >= x) minStk.push(x);
    }
    
    void pop() {
        if (minStk.top() == stk.top()) minStk.pop();
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int min() {
        return minStk.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->min();
 */
```



[包含min函数的栈](https://leetcode-cn.com/problems/bao-han-minhan-shu-de-zhan-lcof)







### 栈的压入、弹出序列

描述：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如，序列 {1,2,3,4,5} 是某栈的压栈序列，序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。



**解题思路**

* 模拟栈

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stk;
        int n = pushed.size();
        for (int i = 0, j = 0; i < n;) {
            while (i < n && (stk.empty() || stk.top() != popped[j])) stk.push(pushed[i++]);
            while (j < n && !stk.empty() && stk.top() == popped[j]) {
                stk.pop();
                j++;
            }
        }
        return stk.empty();
    }
};
```



[栈的压入、弹出序列](https://leetcode-cn.com/problems/zhan-de-ya-ru-dan-chu-xu-lie-lcof) 





### 从上到下打印二叉树&II&III

* BFS模板

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> res;
        queue<TreeNode*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto t = q.front();
                q.pop();
                res.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return res;
    }
};
```



```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> q;
        if (root) q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> tmp;
            for (int i = 0; i < sz; i++) {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(tmp);
        }
        return res;
    }
};
```



```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        queue<TreeNode*> q;
        int cnt = 0;
        if (root) q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> tmp;
            for (int i = 0; i < sz; i++) {
                auto t = q.front();
                q.pop();
                tmp.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            if (cnt & 1) reverse(tmp.begin(), tmp.end());
            res.push_back(tmp);
            ++cnt;
        }
        return res;
    }
};
```







[从上到下打印二叉树](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof)

[从上到下打印二叉树 II](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof) 

[从上到下打印二叉树 III](https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof) 





### 二叉搜索树的后序遍历序列

描述：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 `true`，否则返回 `false`。假设输入的数组的任意两个数字都互不相同。

```cpp
参考以下这颗二叉搜索树：

     5
    / \
   2   6
  / \
 1   3
示例 1：

输入: [1,6,3,2,5]
输出: false
示例 2：

输入: [1,3,2,6,5]
输出: true
```

**解题思路**

* 二叉搜索树的性质：根节点的左子树小于根节点的值，右子树大于根节点的值
* 二叉树后序遍历的性质：最后一个位置为根节点

```cpp
class Solution {
public:
    bool dfs(vector<int>& post, int ll, int rr) {
        if (ll >= rr) return true;
        int i = ll;
        while (i <= rr && post[i] < post[rr]) i++;
        int j = i;
        while (j <= rr && post[j] > post[rr]) j++;
        return j == rr && dfs(post, ll, i - 1) && dfs(post, i, j - 1);
    }
    bool verifyPostorder(vector<int>& post) {
        return dfs(post, 0, post.size() - 1);
    }
};
```



[二叉搜索树的后序遍历序列](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof)





### 复杂链表的复制

描述：请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

**解题思路**

* 哈希表映射

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random; 
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> ma;
        Node* h = head;
        while (h) {
            Node* t = new Node(h->val);
            ma[h] = t;
            h = h->next;
        }
        h = head;
        while (h) {
            ma[h]->next = ma[h->next];
            ma[h]->random = ma[h->random];
            h = h->next;
        }
        return ma[head];
    }
};
```

* 在原链表上插入新的结点，然后对新的结点赋值，最后分成两个链表

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random; 
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return NULL;
        Node* h = head;
        while (h) {
            Node* t = new Node(h->val);
            t->next = h->next;
            h->next = t;
            h = t->next;
        }
        h = head;
        while (h) {
            h->next->random = h->random ? h->random->next : NULL;
            h = h->next->next;
        }
        Node* h1 = head, *h2 = head->next;
        h = head->next;
        while (h2->next) {
            h1->next = h1->next->next;
            h2->next = h2->next->next;
            h1 = h1->next;
            h2 = h2->next;
        }
        // 还原原链表
        h1->next = NULL;
        return h;
    }
};
```



[复杂链表的复制](https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof) 



### 二叉搜索树与双向链表

描述：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。

**解题思路**

* 中序遍历

按中序遍历的顺序获得所有结点，然后进行双向链表的连接

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```java
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/
class Solution {
public:
    Node* hh, *cur;
    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        if (hh) {
            cur->right = root;
            root->left = cur;
            cur = cur->right;
        }
        else {
            hh = root;
            cur = hh;
        }
        inorder(root->right);
    }
    Node* treeToDoublyList(Node* root) {
        if (!root) return NULL;
        hh = NULL, cur = NULL;
        inorder(root);
        hh->left = cur;
        cur->right = hh;
        return hh;
    }
};
```



[二叉搜索树与双向链表](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof) 





### 序列化二叉树

描述：请实现两个函数，分别用来序列化和反序列化二叉树。

**解题思路**

* 先序遍历实现序列化

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    string path;
    void dfs_s(TreeNode* root) {
        if (!root) {
            path += "#,";
            return;
        }
        path += to_string(root->val) + ",";
        dfs_s(root->left);
        dfs_s(root->right);
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        dfs_s(root);
        return path;
    }

    TreeNode* dfs_d(string& data, int& u) {
        if (data[u] == '#') {
            u += 2;
            return NULL;
        }
        int t = u;
        while (u < data.size() && data[u] != ',') u++;
        TreeNode* root = new TreeNode(stoi(data.substr(t, u - t)));
        u++;
        root->left = dfs_d(data, u);
        root->right = dfs_d(data, u);
        return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int u = 0;
        return dfs_d(data, u);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
```



[序列化二叉树](https://leetcode-cn.com/problems/xu-lie-hua-er-cha-shu-lcof) 





### 字符串的排列

描述：输入一个字符串，打印出该字符串中字符的所有排列。

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

**解题思路**

* 全排列

时间复杂度：$O(n!)$

空间复杂度：$O(1)$

 ```cpp
class Solution {
public:
    vector<string> res;
    int permu[15], st[15];
    unordered_set<string> se;
    void dfs(string s, int cnt) {
        if (cnt >= s.size()) {
            string str = "";
            for (int i = 0; i < s.size(); i++) {
                str += s[permu[i]];
            }
            se.insert(str);
            return;
        }
        for (int i = 0; i < s.size(); i++) {
            if (!st[i]) {
                st[i] = true;
                permu[cnt] = i;
                dfs(s, cnt + 1);
                st[i] = false;
            }
        }
    }
    vector<string> permutation(string s) {
        memset(st, 0, sizeof st);
        dfs(s, 0);
        for (auto t : se) {
            res.push_back(t);
        }
        return res;
    }
};
 ```



[字符串的排列](https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof) 







### 数组中出现次数超过一半的数字

描述：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

**解题思路**

* 票数正负抵消

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = nums[0], cnt = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (res != nums[i]) {
                cnt--;
                if (!cnt) res = nums[i], cnt = 1;
            } else {
                cnt++;
            }
        }
        return res;
    }
};
```



[数组中出现次数超过一半的数字](https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof)



### 最小的k个数

描述：输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

 **解题思路**

* 分治+快排变形

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    vector<int> res;
    void quick_sort(vector<int>& arr, int ll, int rr, int k) {
        if (ll == rr && k) res.push_back(arr[ll]);  
        if (ll >= rr) return;
        int i = ll - 1, j = rr + 1, x = arr[i + j >> 1];
        do {
            do i++; while (arr[i] < x);
            do j--; while (arr[j] > x);
            if (i < j) swap(arr[i], arr[j]);
        } while (i < j);
        int left_size = j - ll + 1;
        if (left_size > k) {
            quick_sort(arr, ll, j, k);
        } else {
            for (int x = ll; x <= j; x++) res.push_back(arr[x]);
            quick_sort(arr, j + 1, rr, k - left_size);
        }
    }
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        quick_sort(arr, 0, arr.size() - 1, k);
        return res;
    }
};
```



[最小的k个数](https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof)





### 数据流中的中位数

描述：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

* void addNum(int num) - 从数据流中添加一个整数到数据结构中。
* double findMedian() - 返回目前所有元素的中位数。

```cpp
示例 1：

输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
示例 2：

输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]
```



 **解题思路**

* 双堆

时间复杂度：$O(logn)$

空间复杂度：$O(n)$

```cpp
class MedianFinder {
public:
    /** initialize your data structure here. */
    priority_queue<int, vector<int>> ll;
    priority_queue<int, vector<int>, greater<int>> rr;
    int cnt;
    MedianFinder() {
        cnt = 0;
    }
    
    void addNum(int num) {
        cnt++;
        if (ll.size() != rr.size()) {
            ll.push(num);
            rr.push(ll.top());
            ll.pop();
        } else {
            rr.push(num);
            ll.push(rr.top());
            rr.pop();
        }
    }
    
    double findMedian() {
        return cnt & 1 ? ll.top() : ((double)ll.top() + rr.top()) / 2;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
```



[数据流中的中位数](https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof) 





### 连续子数组的最大和

描述：输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。

要求时间复杂度为O(n)。

  **解题思路**

* 动态规划

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int res = -0x3f3f3f3f, maxv = 0;
        for (auto t : nums) {
            maxv += t;
            res = max(maxv, res);
            if (maxv < 0) maxv = 0;
        }
        return res;
    }
};
```

时间复杂度：$O(nlogn)$

空间复杂度：$O(1)$





[连续子数组的最大和](https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof)



### 1～n 整数中 1 出现的次数

描述：输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。

例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。

```cpp
示例 1：

输入：n = 12
输出：5
示例 2：

输入：n = 13
输出：6
```

  **解题思路**

* 找规律

根据当前位来判断1出现的个数

* cur = 0，由高位high决定，high*digit
* cur=1，由高位和低位决定，high*digit+low+1
* cur > 1，只由高位来决定，（high + 1）* digit

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int countDigitOne(int n) {
        long long digit = 1;
        int res = 0, high = n / 10, low = 0, cur = n % 10;
        while (cur || high) {
            if (cur == 0) res += digit * high;
            else if (cur == 1) res += digit * high + low + 1;
            else res += digit * (high + 1);
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return res;
    }
};
```





[1～n 整数中 1 出现的次数](https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof)





### 数字序列中某一位的数字

描述：数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数，求任意第n位对应的数字。

```
示例 1：

输入：n = 3
输出：3
示例 2：

输入：n = 11
输出：0
 
```



**解题思路**

* 找规律

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

![](https://pic.leetcode-cn.com/2cd7d8a6a881b697a43f153d6c10e0e991817d78f92b9201b6ab71e44cb619de-Picture1.png)

```cpp
class Solution {
public:
    int findNthDigit(int n) {
        long long digit = 1, start = 1, count = 9;
        while (n > count) {
            n -= count;
            digit++;
            start *= 10;
            count = 9 * digit * start;
        }
        long long num = start + (n - 1) / digit;
        return to_string(num)[(n - 1) % digit] - '0';
    }
};
```





[数字序列中某一位的数字](https://leetcode-cn.com/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof)







### 把数组排成最小的数

描述：输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

* 贪心+排序

时间复杂度：$O(nlogn)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    static bool cmp(string a, string b) {
        string s1 = a + b, s2 = b + a;
        return s1 < s2;
    }
    string minNumber(vector<int>& nums) {
        vector<string> vec;
        for (auto t : nums) vec.push_back(to_string(t));
        string res = "";
        sort(vec.begin(), vec.end(), cmp);
        for (auto t : vec) res += t;
        return res;
    }
};
```



[把数组排成最小的数](https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof)





### 把数字翻译成字符串

**解题思路**

* 动态规划

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    int translateNum(int num) {
        string str = to_string(num);
        int f[110] = {0}, n = str.size();
        f[0] = 1;
        for (int i = 1; i < n; i++) {
            f[i] = f[i - 1];
            int num = stoi(str.substr(i - 1, 2));
            if (num >= 10 && num <= 25) f[i] += f[max(i - 2, 0)];
        }
        return f[n - 1];
    }
};
```



* 深搜

时间复杂度：$O(2^n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int dfs(int num) {
        if (num < 10) return 1;
        int t = dfs(num / 10), u = num % 100;
        if (u >= 10 && u <= 25) t += dfs(num / 100);
        return t;
    }
    int translateNum(int num) {
        return dfs(num);
    }
};
```





[把数字翻译成字符串](https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof)







### 礼物的最大价值

**解题思路**

* 方格型动态规划

时间复杂度：$O(n^2)$

空间复杂度：$O(n^2)$

```cpp
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                f[i][j] = max(f[i - 1][j], f[i][j - 1]) + grid[i - 1][j - 1];
            }
        }
        return f[n][m];
    }
};
```



[礼物的最大价值](https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof)







### 最长不含重复字符的子字符串

**解题思路**

* 滑动窗口+双指针

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> ma;
        int i = -1, res = 0;
        for (int j = 0; j < s.size(); j++) {
            if (ma.count(s[j])) i = max(i, ma[s[j]]);
            res = max(res, j - i);
            ma[s[j]] = j;
        }
        return res;
    }
};
```





[最长不含重复字符的子字符串](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof)







### 丑数

**解题思路**

* 动态规划+三指针

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    int nthUglyNumber(int n) {
        int f[2000];
        f[1] = 1;
        int a = 1, b = 1, c = 1;
        for (int i = 2; i <= n; i++) {
            if (f[a] * 2 <= f[i - 1]) a++;
            if (f[b] * 3 <= f[i - 1]) b++;
            if (f[c] * 5 <= f[i - 1]) c++;
            f[i] = min(f[a] * 2, min(f[b] * 3, f[c] * 5));
        }
        return f[n];
    }
};
```



[丑数](https://leetcode-cn.com/problems/chou-shu-lcof) 









### 第一个只出现一次的字符

**解题思路**

* 哈希表维护字符出现个数

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> ma;
        for (auto i : s) ma[i] = 0;
        for (auto i : s) ma[i]++;
        for (auto i : s) {
            if (ma[i] == 1) return i;
        }
        return ' ';
    }
};
```



[第一个只出现一次的字符](https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof)







### 数组中的逆序对

**解题思路**

* 归并排序

时间复杂度：$O(nlogn)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    int tmp[50010];
    int merge(vector<int>& nums, int ll, int rr) {
        if (ll >= rr) return 0;
        int res = 0, mid = ll + rr >> 1;
        res = merge(nums, ll, mid) + merge(nums, mid + 1, rr);
        int t = 0, i = ll, j = mid + 1;
        while (i <= mid && j <= rr) {
            if (nums[i] > nums[j]) {
                res += mid - i + 1;
                tmp[t++] = nums[j++];
            } else {
                tmp[t++] = nums[i++];
            }
        }
        while (i <= mid) tmp[t++] = nums[i++];
        while (j <= rr) tmp[t++] = nums[j++];
        for (int k = 0, i = ll; k < t; k++, i++) nums[i] = tmp[k];
        return res;
    }
    int reversePairs(vector<int>& nums) {
        return merge(nums, 0, nums.size() - 1);
    }
};
```

**解题思路**

* 树状数组

时间复杂度：$O(nlogn)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    vector<int> all;
    unordered_map<int, int> ma;
    int cnt, tr[50010];

    int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int y) {
        for (int i = x; i < 50010; i += lowbit(i)) tr[i] += y;
    }

    int query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= lowbit(i)) res += tr[i];
        return res;
    }
    int reversePairs(vector<int>& nums) {
        cnt = 0;
        int res = 0;
        all = vector(nums);
        sort(all.begin(), all.end());
        all.erase(unique(all.begin(), all.end()), all.end());
        for (auto t : all) ma[t] = ++cnt;
        for (auto t : nums) {
            res += query(50000) - query(ma[t]);
            add(ma[t], 1);
        }
        return res;
    }
};
```



[数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof)



### 两个链表的第一个公共节点

**解题思路**

* 双指针

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return NULL;
        ListNode *t1 = headA, *t2 = headB;
        int time = 0;
        while (t1 != t2 && time <= 2) {
            if (t1->next) t1 = t1->next;
            else {
                t1 = headB;
                time++;
            }
            if (t2->next) t2 = t2->next;
            else {
                t2 = headA;
                time++;
            }
        }
        return time > 2 ? NULL : t1;
    }
};
```



[两个链表的第一个公共节点](https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof)





### 在排序数组中查找数字 I

**解题思路**

* 二分

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return 0;
        int ll = 0, rr = nums.size() - 1;
        while (ll < rr) {
            int mid = ll + rr >> 1;
            if (nums[mid] >= target) rr = mid;
            else ll = mid + 1;
        }
        if (nums[ll] != target) return 0;
        int lll = 0, rrr = nums.size() - 1;
        while (lll < rrr) {
            int mid = lll + rrr + 1 >> 1;
            if (nums[mid] <= target) lll = mid;
            else rrr = mid - 1;
        }
        return lll - ll + 1;
    }
};
```



[在排序数组中查找数字 I](https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof)



### 0～n-1中缺失的数字

**解题思路**

* 二分

时间复杂度：$O(logn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ll = 0, rr = nums.size() - 1;
        while (ll < rr) {
            int mid = ll + rr >> 1;
            if (nums[mid] != mid) rr = mid;
            else ll = mid + 1;
        }
        return nums[ll] == ll ? ll + 1 : ll;
    }
};
```



[0～n-1中缺失的数字](https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof)





### 二叉搜索树的第k大节点

**解题思路**

* 中序遍历

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> res;
    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->left);
        res.push_back(root->val);
        dfs(root->right);
    }
    int kthLargest(TreeNode* root, int k) {
        dfs(root);
        return res[res.size() - k];
    }
};
```



[二叉搜索树的第k大节点](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof)



### 二叉树的深度

**解题思路**

* 递归

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```



[二叉树的深度](https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof) 





### 平衡二叉树

**解题思路**

* 递归

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalance;
    int dfs(TreeNode* root) {
        if (!root) return 0;
        if (!root->left && !root->right) return 1;
        int leftH = dfs(root->left) + 1, rightH = dfs(root->right) + 1;
        if (abs(leftH - rightH) > 1) isBalance = false;
        return max(leftH, rightH);
    }

    bool isBalanced(TreeNode* root) {
        isBalance = true;
        dfs(root);
        return isBalance;
    }
};
```



[平衡二叉树](https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof)





### 数组中数字出现的次数

**解题思路**

* 位运算性质

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int tmp = 0, a = 0, b = 0;
        for (auto t : nums) tmp ^= t;
        int h = 1;
        while ((tmp & h) == 0) h <<= 1;
        for (auto t : nums) {
            if (h & t) a ^= t;
            else b ^= t;
        }
        return {a, b};
    }
};
```



[数组中数字出现的次数](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof)



### 数组中数字出现的次数 II

**解题思路**

* 位运算

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int cnt[110] = {0}, res = 0;
        for (auto t : nums) {
            for (int i = 31; i >= 0; i--) {
                cnt[i] += t & 1;
                t >>= 1;
            }
        }
        for (int i = 31; i >= 0; i--) {
            if (cnt[i] % 3) res += 1 << (31 - i); 
        }
        return res;
    }
};
```



[数组中数字出现的次数 II](https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof)







### 和为s的两个数字

**解题思路**

* 二分枚举

时间复杂度：$O(nlogn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    bool binSearch(vector<int>& nums, int target) {
        int ll = 0, rr = nums.size() - 1;
        while (ll <= rr) {
            int mid = ll + rr >> 1;
            if (nums[mid] == target) return true;
            else if (nums[mid] < target) ll = mid + 1;
            else rr = mid - 1;
        }
        return false;
    }
    vector<int> twoSum(vector<int>& nums, int target) {
        for (auto t : nums) {
            if (binSearch(nums, target - t)) return {t, target - t};
        }
        return {};
    }
};
```

* 碰撞指针

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int ll = 0, rr = nums.size() - 1;
        while (ll < rr) {
            if (nums[ll] + nums[rr] == target) return {nums[ll], nums[rr]};
            else if (nums[ll] + nums[rr] < target) ll++;
            else rr--; 
        }
        return {};
    }
};
```



[和为s的两个数字](https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof)





### 和为s的连续正数序列

**解题思路**

* 滑动窗口

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;
        int i = 1, j = 1, sum = 0;
        while (j < target) {
            if (sum < target) sum += j++;
            else if (sum > target) sum -= i++;
            else {
                vector<int> tmp;
                for (int u = i; u < j; u++) tmp.push_back(u);
                res.push_back(tmp);
                sum -= i++;
            }
        }
        return res;
    }
};
```



[和为s的连续正数序列](https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof)





### 翻转单词顺序

**解题思路**

* 双指针

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    string reverseWords(string s) {
        vector<string> vec;
        int i = 0;
        while (i < s.size() && s[i] == ' ') i++;
        int j = i;
        while (j < s.size()) {
            while (j < s.size() && s[j] != ' ') j++;
            vec.push_back(s.substr(i, j - i));
            while (j < s.size() && s[j] == ' ') j++;
            i = j;
        }
        reverse(vec.begin(), vec.end());
        string res = "";
        for (int i = 0; i < vec.size(); i++) {
            res += vec[i];
            if (i != vec.size() - 1) res += ' ';
        }
        return res;
    }
};
```



[翻转单词顺序](https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof)





### 左旋转字符串

**解题思路**

* 字符串模拟

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        return s.substr(n, s.size() - n) + s.substr(0, n);
    }
};
```

* 原地

```cpp
class Solution {
public:
    void reverse(string &s, int ll, int rr) {
        while (ll < rr) swap(s[ll++], s[rr--]);
    }
    string reverseLeftWords(string s, int n) {
        reverse(s, 0, n - 1);
        reverse(s, n, s.size() - 1);
        reverse(s, 0, s.size() - 1);
        return s;
    }
};
```





[左旋转字符串](https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof)



### 滑动窗口的最大值

**解题思路**

* 滑动窗口

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size(), hh = 0, tt = -1;
        vector<int> vec(n, 0), res;
        for (int i = 0; i < n; i++) {
            while (tt >= hh && i - vec[hh] >= k) hh++;
            while (tt >= hh && nums[vec[tt]] <= nums[i]) tt--;
            vec[++tt] = i;
            if (i >= k - 1) res.push_back(nums[vec[hh]]);
        }
        return res;
    }
};
```



[滑动窗口的最大值](https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof)



### 队列的最大值

**解题思路**

* 滑动窗口

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class MaxQueue {
public:
    queue<int> que;
    vector<int> window;
    int tt, hh;
    MaxQueue() {
        tt = -1, hh = 0;
        window.resize(10010);
    }
    
    int max_value() {
        if (tt < hh) return -1;
        return window[hh];
    }
    
    void push_back(int value) {
        que.push(value);
        while (tt >= hh && window[tt] < value) tt--;
        window[++tt] = value; 
    }
    
    int pop_front() {
        if (que.empty()) return -1;
        int value = que.front();
        que.pop();
        if (window[hh] == value) ++hh; 
        return value;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
```



[队列的最大值](https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof)





### n个骰子的点数

**解题思路**

* 动态规划

时间复杂度：$O(n^2)$

空间复杂度：$O(n^2)$

```cpp
class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<vector<int>> f(n + 1, vector<int>(6 * n + 1, 0));
        f[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= 6 * i; j++) {
                for (int k = 1; k <= 6 && k <= j; k++) {
                    f[i][j] += f[i - 1][j - k];
                }
            }
        }
        double sum = 0;
        vector<double> vec;
        for (int i = n; i <= 6 * n; i++) sum += f[n][i];
        for (int i = n; i <= 6 * n; i++) {
            vec.push_back(f[n][i] / sum);
        }
        return vec;
    }
};
```



[n个骰子的点数](https://leetcode-cn.com/problems/nge-tou-zi-de-dian-shu-lcof)





### 扑克牌中的顺子

* 排序

时间复杂度：$O(nlogn)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int joker = 0;
        for (int i = 0; i < 4; i++) {
            if (nums[i] && nums[i] == nums[i + 1]) {
                return false;
            }
        }
        for (auto t : nums) if (!t) joker++;
        return nums[4] - nums[joker] <= 4;
    }
};
```



[扑克牌中的顺子](https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof)





### 圆圈中最后剩下的数字

* 模拟链表

时间复杂度：$O(n^2)$

空间复杂度：$O(n)$

```cpp
class Solution {
    public int lastRemaining(int n, int m) {
        List<Integer> list = new ArrayList<>(n);
        for (int i = 0; i < n; i++) list.add(i);
        int inx = 0;
        while (list.size() > 1) {
            inx = (inx + m - 1) % list.size();
            list.remove(inx);
            n--;
        }
        return list.get(0);
    }
}
```

* 数学公式

时间复杂度：$O(n^2)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    int lastRemaining(int n, int m) {
        int inx = 0;
        for (int i = 2; i <= n; i++) {
            inx = (inx + m) % i;
        }
        return inx;
    }
};
```



[圆圈中最后剩下的数字](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof)







### 股票的最大利润

* 动态规划

时间复杂度：$O(n)$

空间复杂度：$O(1)$

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(!prices.size()) return 0;
        int res = 0, minv = prices[0];
        for(int i = 1; i < prices.size(); i++){
            minv = min(minv, prices[i]);
            res = max(res, prices[i] - minv);
        }
        return res;
    }
};
```



[股票的最大利润](https://leetcode-cn.com/problems/gu-piao-de-zui-da-li-run-lcof)





### 求1+2+…+n

* 递归

时间复杂度：$O(n)$

空间复杂度：$O(n)$

```cpp
class Solution {
public:
    int sumNums(int n) {
        n && (n += sumNums(n - 1));
        return n;
    }
};
```



[求1+2+…+n](https://leetcode-cn.com/problems/qiu-12n-lcof)





### 不用加减乘除做加法



[不用加减乘除做加法](https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof)





### 构建乘积数组



[构建乘积数组](https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof)





### 把字符串转换成整数



[把字符串转换成整数](https://leetcode-cn.com/problems/ba-zi-fu-chuan-zhuan-huan-cheng-zheng-shu-lcof)





### 二叉搜索树的最近公共祖先



[二叉搜索树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-zui-jin-gong-gong-zu-xian-lcof)







### 二叉树的最近公共祖先



[二叉树的最近公共祖先](https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof)

