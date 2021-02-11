class CQueue {
public:
    // s1用来存放元素，s2栈顶即为队列头部元素
    stack<int> s1, s2;
    CQueue() {
    }
    
    void appendTail(int value) {
        s1.push(value);
    }
    
    int deleteHead() {
        if (s1.empty()) return -1;
        while (s1.size() > 1) s2.push(s1.top()), s1.pop();
        int res;
        res = s1.top(), s1.pop();
        while (!s2.empty()) s1.push(s2.top()), s2.pop();
        return res;
    }
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */
