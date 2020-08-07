class MinStack {
public:
    /** initialize your data structure here. */
    // s1为普通栈，s2为单调栈
    stack<int> s1, s2;
    // 维护插入元素
    vector<int> vec;
    MinStack() {
        
    }
    
    void push(int x) {
        vec.push_back(x);
        s1.push(vec.size() - 1);
        if (s2.empty() || x < vec[s2.top()]) s2.push(vec.size() - 1);
        
    }
    
    void pop() {
        if (s2.top() == s1.top()) s2.pop();
        s1.pop();
    }
    
    int top() {
        return vec[s1.top()];
    }
    
    int getMin() {
        return vec[s2.top()];
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */
