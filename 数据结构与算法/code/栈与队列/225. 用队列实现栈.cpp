class MyStack {
public:
    /** Initialize your data structure here. */
    // q1用来存元素，q2用来取栈顶元素
    queue<int> q1, q2;
    int eleTop;
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        eleTop = x;
        q1.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        // q1转移到q2，大小为1时，该元素为栈顶元素
        while (q1.size() > 1) {
            // 更新弹出栈顶元素后栈顶的值
            if (q1.size() == 2) eleTop = q1.front();
            q2.push(q1.front());
            q1.pop();
        }
        int res = q1.front();
        q1.pop();
        while (!q2.empty()) {
            q1.push(q2.front());
            q2.pop();
        }
        return res;
    }
    
    /** Get the top element. */
    int top() {
        return eleTop;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
