class MyQueue {
public:
    /** Initialize your data structure here. */
    // s1栈顶用来取队头，s2栈顶用来取队尾
    stack<int> s1, s2;
    int front;
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if (s1.empty()) front = x;
        s1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        // 将s1的元素移入s2
        while (!s1.empty()) s2.push(s1.top()), s1.pop();
        // 取队头元素
        int res = s2.top();
        // 移除队头元素
        s2.pop();
        // 更新队头元素
        if (!s2.empty()) front = s2.top();
        // s2还原到s1
        while (!s2.empty()) s1.push(s2.top()), s2.pop();
        return res;
    }
    
    /** Get the front element. */
    int peek() {
        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return s1.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
