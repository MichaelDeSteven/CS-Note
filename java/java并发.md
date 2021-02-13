# Java并发



## 基本概念

* 阻塞：是指等待结果返回之前，线程的状态处于阻塞

* 非阻塞：指等待结果返回之前，线程的状态处于非阻塞

* 同步：需要等待结果返回，才能继续运行

* 异步：不需要等待结果返回，就能继续运行





## 线程

### 创建线程

**直接使用Thread**

```java
// 使用lamda简化
Thread t1 = new Thread(()
                       -> {log
                           .debug(Thread.currentThread().getName() + "正在运行");},
                       "t1");
```



**Runnable配合Thread**

```java
// 实现Runnable接口，独立指定运行的内容
public class RunnableImpl implements Runnable {
    @Override
    public void run() {
        log.debug(Thread.currentThread().getName() + "Runnable接口实现");
    }
}
```

```java
// 创建线程
Thread t1 = new Thread(new RunnableImpl(), "t1");
```



**Callable搭配FutureTask**

```java
// 实现了Callable接口，即Runnable+返回值
public class CallableImpl implements Callable {
    @Override
    public Object call() throws Exception {
        log.debug("当前线程执行了");
        return "回调值";
    }
}
```

```java
// 使用FutureTask接收返回值
FutureTask<String> v = new FutureTask(new CallableImpl());
Thread t1 = new Thread(v, "t1");
t1.start();
t1.join();
log.debug(v.get());
```



**对比**

* 直接使用Thread来创建线程简单
* 实现接口会更好一些，能将线程的创建与执行的方法解耦
* Callable接口间接实现了Runnable接口，与Runnable接口相比，Callable能够使用FutureTask接收返回值



### 查看和调试线程

window平台下

* 通过任务管理器能够查看进程与杀死进程
* 使用tasklist可以查看线程
* 使用taskkill可以杀死进程



Linux平台下

```shell
# 查看所有进程
ps -ef
# 杀死某个进程
kill -9 <PID>
# 查看某个进程的所有线程
ps -fT -p <PID>
# 查看系统资源使用情况以及进程占用资源情况
top
# 查看某个进程内的所有线程
top -H -p <PID>
```



java平台下

```shell
jps 查看所有java进程
jstack <PID> 查看某个进程的所有线程状态
```





### Thread基本API

| 方法名           | 功能说明                     | 注意事项                                                     |
| ---------------- | ---------------------------- | ------------------------------------------------------------ |
| start()          | 启动一个新线程               | 调用该方法表示启动一个新线程，并允许run()方法，一个对象多次调用会出现IllegalThreadStateException异常 |
| run()            | 线程启动后会运行的方法       |                                                              |
| join()           | 等待线程运行结束             |                                                              |
| join(long)       | 等待线程运行结束，最多等待秒 |                                                              |
| getId()          | 获取线程id                   |                                                              |
| getName()        | 获取线程名                   |                                                              |
| setName(String)  | 修改线程名                   |                                                              |
| getPriority()    | 获取线程优先级               |                                                              |
| setPriority(int) | 修改线程优先级               | java规定线程优先级为1-10的整数，越大优先级越高               |
| getStatus()      | 获取线程状态                 |                                                              |
| isInterrupt()    | 判断线程是否被打断           | 不会清除打断标记                                             |
| isAlive()        | 判断线程是否存存活           |                                                              |
| interrupt()      | 打断线程                     | 如果被打断线程处于sleep、wait、join会导致被打断线程出现IllegalThreadStateException，并清除打断标记，如果打断正在运行的线程，则会设置清除标记 |
| interrupted()    | 判断当前线程是否被打断       | 会清除打断标记                                               |
| currentThread()  | 获取当前线程                 |                                                              |
| sleep(long n)    | 让当前线程休眠n秒            |                                                              |
| yield()          | 使当前线程让出CPU执行权      |                                                              |

**sleep和yield**

* 两者都是静态本地方法，都可以让出cpu资源
* sleep是让线程从RUNNING进入TIMED WAITING，而yield是让线程从RUNNING进入RUNNABLE
* sleep让线程睡眠指定时间，yield表示主动让出，当空闲时该线程可能又会被cpu调度执行



**isinterrupt和interrupted**

```java
// 不清除打断标记
public boolean isInterrupted() {
    return isInterrupted(false);
}    
// 清除打断标记
public static boolean interrupted() {
    return currentThread().isInterrupted(true);
}
// 均调用了该方法
private native boolean isInterrupted(boolean ClearInterrupted);
```





### 线程状态转换

![](C:\Users\Steven\Desktop\CS-Note\java\pic\java线程状态转移图.png)

* java使用枚举类来表示java线程的6个状态

```java

public enum State {
    NEW,
    
    RUNNABLE,

    BLOCKED,

    WAITING,

    TIMED_WAITING,

    TERMINATED;
}
```





#### New

创建后尚未启动

```java
Thread t1 = new Thread();
log.debug(String.valueOf(t1.getState()));
```



#### Runnable

java中的Runnable是指在JVM中可执行，对于操作系统层面来说未必在执行，比如操作系统可能在IO阻塞等待资源，而对于java层面来说，线程的状态也为Runnable，即该状态可能是操作系统层面线程状态的其中一种（运行状态、阻塞状态、就绪状态）

```java
Thread t1 = new Thread(() -> {
    while (true) {}
});
t1.start();
log.debug(String.valueOf(t1.getState()));
```





#### Timed Waiting

调用sleep或者wait会使线程进入TimedWaiting状态

```java
Thread t1 = new Thread(() -> {
    try {
        Thread.sleep(10000);
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
});
t1.start();
Thread.sleep(100);
log.debug(String.valueOf(t1.getState()));
```



#### Waiting

无限期等待，需要等待其它线程来唤醒，比如使用了join方法等待其它线程执行完毕的线程状态为waiting





#### Blocked

等待获取一个排它锁

```java
// 线程t1资源被线程keep占用，进入blocked状态
Thread keep = new Thread(() -> {
    // 占用资源
    synchronized (Object.class) {
        try {
            Thread.sleep(1000000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
});
keep.start();
Thread t1 = new Thread(() -> {
    // 资源被占用，进入阻塞状态
    synchronized (Object.class) {
        System.out.println("阻塞状态");
    }
});
t1.start();
Thread.sleep(100);
log.debug(String.valueOf(t1.getState()));
```



#### Terminated

线程执行完任务正常结束或者产生异常终止





### 应用

#### 两阶段终止

Two Phase Terminated：在一个线程t1中”优雅“地终结一个线程t2





#### 线程的同步应用

