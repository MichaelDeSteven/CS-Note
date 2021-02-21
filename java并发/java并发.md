# Java并发



## 基本概念

* 阻塞：是指等待结果返回之前，线程的状态处于阻塞

* 非阻塞：指等待结果返回之前，线程的状态处于非阻塞

* 同步：需要等待结果返回，才能继续运行

* 异步：不需要等待结果返回，就能继续运行





## 线程

### 原理

#### 栈与栈帧

JVM由堆、栈、方法区组成，其中栈内存由线程使用，每一个线程占用一片栈内存

* 一个栈由多个栈帧组成，一个栈帧对应一个方法
* 每个线程只有一个活动栈帧，即当前线程正在运行的那一个方法

#### 上下文切换

**时机**

* CPU时间片用完
* 发生GC
* 更高优先级线程需要运行
* 调用了让当前线程进入阻塞等待的方法

**过程**

保存当前线程的状态，并恢复另一个线程的状态。具体地Java将当前线程的程序计数器、虚拟机栈中每一个栈帧的局部变量、操作数栈、返回地址等状态都保存起来，另一个线程的状态都恢复，这个过程是比较耗时的



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

具体实现详见设计模式



#### 线程的同步应用









## 管程

### 基本概念

临界资源：被多个线程所并发共享的资源，且同一时间段内只能被一个线程使用

临界区：包含了临界资源的代码段

同步：多个相关的线程需要按一定的次序进行协调来执行任务，在一些关键点必须等待某些线程执行完后当前线程才能执行

互斥：是指线程进入临界区使用临界资源，这一时间段内，其它需要使用临界资源的线程必须等待，直到该线程退出临界区后才能使用，这就是互斥，互斥也可以看作是同步的一种特例

线程安全：函数被多个并发线程所执行，其结果一定都是正确的

管程：用于对线程并发的数据结构，还定义了能为并发线程在该数据结构上所执行的一组操作，这组操作能改变管程的数据从而达到线程同步的目的

条件变量：

乐观锁：

悲观锁：

CAS：

自旋锁：

偏向锁：





### 线程安全

对于静态变量和成员变量来说

* 如果它们没被共享了,则线程安全
* 如果它们被共享了,又分两个情况
  * 如果只有只读操作,则线程安全
  * 如果存在写操作,则需要考虑线程安全问题



对于局部变量来说

* 局部变量不引用对象则为线程安全

* 局部变量引用了对象,分两种情况

  * 对象没有逃离方法访问,则线程安全
  * 对象逃离方法访问,则需要考虑线程安全问题

  

**java常见线程安全类**

* Integer
* String
* StringBuffer
* Vector
* Hashtable
* JUC包下的类



### 对象头Monitor

以32位虚拟机为例

普通对象

```
|--------------------------------------------------------------|
|                   Object Header (64 bits)                    |
|------------------------------------|-------------------------|
|      Mark Word (32 bits)           | Klass Word (32 bits)    |
|------------------------------------|-------------------------|
```

数组对象

```
|---------------------------------------------------------------------------------|
|                             Object Header (96 bits)                             |
|--------------------------------|-----------------------|------------------------|
|      Mark Word(32bits)         |    Klass Word(32bits) |   array length(32bits) |
|--------------------------------|-----------------------|------------------------|
```

![](https://images2017.cnblogs.com/blog/285763/201708/285763-20170807175258143-2067730874.png)

![](https://img-blog.csdnimg.cn/20190612142936955.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly96aGFuZ2JveWkuYmxvZy5jc2RuLm5ldA==,size_16,color_FFFFFF,t_70)



* Mark Word字段记录着hashcode、分代年龄、锁标记位等
* Klass Pointer用来确定该对象是哪个类的实例
* 对于32位虚拟机的Mark Word字段，对象在未被锁定的情况下，25位用来存储对象哈希码，4位用来存储GC分代年龄，2位用来存储锁标志位，剩下1位默认为0，表示是否为偏向锁



**java中每一个对象都存在一个monitor（也称为管程）与之关联**，monitor的数据结构参考HotSpot虚拟机源码ObjectMonitor.hpp

```cpp
ObjectMonitor() {
    _header       = NULL;
    _count        = 0; //记录个数
    _waiters      = 0,
    _recursions   = 0;
    _object       = NULL;
    _owner        = NULL;
    _WaitSet      = NULL; //处于wait状态的线程，会被加入到_WaitSet
    _WaitSetLock  = 0 ;
    _Responsible  = NULL ;
    _succ         = NULL ;
    _cxq          = NULL ;
    FreeNext      = NULL ;
    _EntryList    = NULL ; //处于等待锁block状态的线程，会被加入到该列表
    _SpinFreq     = 0 ;
    _SpinClock    = 0 ;
    OwnerIsThread = 0 ;
  }
```

* owner表示该对象的被哪一个线程所持有
* WaitSet表示等待队列，请求获取该对象的线程处于wait状态的都会被加入
* EntryList用来保存进入同步代码块的线程

过程：没有竞争时的owner为空，假设EntryList不为空，owner为null时，会随机唤醒EntryList中的线程来竞争锁，这时只有一个线程能获得到monitor，此时将owner设置为当前线程



[java对象在内存中的结构](https://www.cnblogs.com/duanxz/p/4967042.html)





### CAS

**概述**

CAS全称为CompareAndSwap，机制就是比较相同再交换，CAS是现代CPU广泛支持的一种对内存共享数据操作的原子指令

**作用**

读源码可以发现CAS指令为Linux内核的cmpxchg_ptr函数

```c++
Atomic::cmpxchg(void *ptr, unsigned long old, unsigned long new)
```

该函数功能是，将old和ptr所指向的内容进行比较，如果相同，则将new写入到ptr，不相同则返回ptr指向的内容



**悲观锁和乐观锁**

* 悲观锁的观点是总是假设最坏的情况，每次去拿数据时都认为别人会修改，所以在每次拿数据时都会上锁，这样别的线程拿数据都会进入阻塞状态，synchronized和ReetrantLock都是悲观锁的实现
* 乐观锁的观点是总是假设最好的情况，每次去拿数据时都认为别人不会修改，就算修改了也没关系，再重试即可。所以不会上锁，但是在更新的时候会判断以下在此期间别人是否修改过该数据，如果有人修改则更新，没人修改则重试，CAS算法思想就是基于乐观锁
* 如果多线程竞争激烈，乐观锁重试次数增多增加了CPU负担，效率会变低，因此最好选择悲观锁
* 多线程竞争不激烈，使用乐观锁性能会比悲观锁好



### synchronized

**语法**

```java
synchronized(对象)
{
 临界区
}
```

* 加在静态方法上表示以该类对象为对象锁
* 加载非静态方法上表示以实例对象为对象锁
* 加载同步代码块上，指定的对象为对象锁



#### **原理**

**字节码层面**

```java
public class code {
    public static void main(String[] args) {
        int c = 0;
        synchronized(code.class) {
            c++;
        }
    }
}
```

对应字节码

```java
 0 iconst_0
 1 istore_1
 2 ldc #2 <concurrence/syn/code>
 4 dup
 5 astore_2
 6 monitorenter			// 该指令是将code类对象设置为Monitor指针
 7 iinc 1 by 1
10 aload_2
11 monitorexit         // 将code类对象Mark Word重置，并唤醒EnrtyList
12 goto 20 (+8)
15 astore_3
16 aload_2
17 monitorexit
18 aload_3
19 athrow
20 return
```



* 执行synchronized，首先使用了monitorenter指令
  * 如果monitor进入数为0，线程可以进入monitor，并将monitor的进入数置为1，当前线程置为monitor的onwer
  * 如果线程已经拥有monitor的所有权，那么允许他重入monitor，monitor进入数加一
  * 若其它线程已经占有monitor的所有权，那么当前线程会被阻塞，直到monitor的进入数为0，才会重新尝试获取monitor
* 执行完后，会调用monitorexit
  * 首先能执行monitorexit指令的线程一定是拥有当前对象的monitor的所有权线程
  * 执行monitorexit会使monitor进入数减一，将进入数为0时，则当前线程不再拥有monitor所有权
  * 当前线程释放锁，如果entryList不为空，则会去entryList唤醒所有线程竞争锁

有两个monitorexit指令的原因是：为了保证抛异常时情况下也能释放锁，所以在同步代码块下添加了一个隐式的try-finally，因此synchronized保证了无论代码执行是正常或者异常终止，最终都会释放锁



**HotSpot虚拟机下的cpp源码层面**

ObjectMonitor.hpp下的monitor数据结构

```cpp
ObjectMonitor() {
_header = NULL;
_count = 0;
_waiters = 0，
_recursions = 0; // 线程的重入次数
_object = NULL; // 存储该monitor的对象
_owner = NULL; // 标识拥有该monitor的线程
_WaitSet = NULL; // 处于wait状态的线程，会被加入到_WaitSet
_WaitSetLock = 0 ;
_Responsible = NULL;
_succ = NULL;
_cxq = NULL; // 多线程竞争锁时的单向列表
FreeNext = NULL;
_EntryList = NULL; // 处于等待锁block状态的线程，会被加入到该列表
_SpinFreq = 0;
_SpinClock = 0;
OwnerIsThread = 0;
}
```





#### **优化**

由于Monitor实现同步的机制本质是操作系统的互斥锁，而互斥锁需要从用户态转为内核态来完成，需要耗费许多时间，这就是重量级锁，在JDK1.6中，虚拟机做了一系列优化，增强了synchronized性能

synchronized引入了“偏向锁”、“轻量级锁”，因此锁的状态由低到高分别为：无锁状态、偏向锁状态、轻量级锁状态、重量级锁状态，值得注意的是锁只能升级而不能降级



#### 无锁状态

此时java对象头Mark Word字段

* 对象哈希码25bit，GC分代年龄4bit，偏向锁标志位1bit，锁标志信息2bit
* 偏向锁标志位为0，锁表标志信息01







#### 偏向锁状态

大多数情况下，锁不存在竞争，而且总是由一个线程多次获得，这种情况下，当线程访问同步代码块并获取锁时，会在对象头和栈帧中的锁记录里存储偏向的线程ID

**获取流程**

* 从当前线程栈中，寻找内存最高可用锁记录，锁记录指针与锁对象相关联
* 判断锁对象的Mark Word字段低3位是否为101
* 如果为101说明开启了偏向锁模式
* 首先将当前线程id与类对象的prototype_header字段进行与运算，得到的值为（线程id字段23位+epoch字段2位+GC分代年龄字段4位+偏向锁标志位字段1位+锁信息标志位字段2位）
* 如果对象锁偏向当前线程，且类对象与对象锁的epoch值相同则什么都不用做
* 如果是类对象的偏向模式关闭，而对象锁已经开启了偏向模式，这时候利用CAS指令来尝试撤销偏向锁
* 如果类对象的epoch值不等于对象锁的epoch，说明对象锁的epoch值过期，需要尝试重偏向
* 重偏向成功则更新了epoch值，失败了则进入monitorenter方法进行锁升级
* 最后一种情况就是要么偏向锁偏向了其它线程，要么是该对象锁为匿名偏向
* 尝试将对象锁偏向线程修改位当前线程，如果失败则进入锁升级
* 走到最后的逻辑都是当前对象锁没有开启偏向模式，那么会进入轻量级锁的逻辑



**撤销**

偏向锁撤销是指获取偏向锁过程中，因为不满足条件（获取hashcode、其他线程使用对象、调用wait\notify方法）需要将锁对象改为非偏向模式

* 偏向锁失败会进入monitorenter方法，首先判断是否为是否使用了偏向锁，如果是那么会进入fast_enter方法
* 判断偏向的线程是否存活，如果已经不存活则直接撤销偏向锁。JVM维护了一个集合保存了所有存活的线程，依据该集合来判断线程是否存活
* 如果线程存活则判断线程是否已经退出同步代码块当中，由于每次线程将锁记录由高往低放入线程栈中（包括了重入的次数），因此可以通过遍历线程栈来判断线程是否在同步块
* 如果线程不处于活动状态则对象锁设置为无锁状态，线程仍然存活则锁记录MarkWork字段置为null，进入轻量级锁升级逻辑





撤销需要注意的是

* 撤销过程中是进入了一个全局安全点，这个过程没有正在执行的字节码



**释放**

* 与偏向锁获取相反，从低到高遍历线程栈中的锁记录
* 如果锁记录与对象锁关联，那么判断是否开启了偏向模式
* 如果为偏向模式则只需释放锁记录，将锁记录指向的obj字段置为null
* 否则将当前锁记录当中的Mark Word替换到锁对象的对象头上，然后进入轻量级或者重量级锁释放逻辑





**批量撤销和批量重偏向**

使用偏向锁在某些场景下可能会导致性能下降，这个时候需要某种机制来解决

* 场景1：一个线程创建了大量对象，并将其作为偏向锁，之后另外的线程也将这些对象作为偏向锁，那么会导致大量的偏向锁撤销操作
* 场景2：存在明显多竞争的场景如生产者消费者队列

批量重偏向（bulk rebias）是用来解决场景1的，批量撤销（bulk revoke）是用来解决场景2的，其做法是以class为单位，为每一个class维护一个偏向锁撤销计数器，每次该类的对象发生撤销时，计数器的值加1，当这个值达到重偏向阈值（默认为20），那么会发生批量重偏向，当达到批量撤销阈值（40），那么会认为该类使用场景为多线程竞争，不适合作为偏向锁，将该class标记为不可偏向，之后对于该class锁，直接走轻量级锁逻辑

* 批量重偏向首先将该类的epoch字段加一，然后遍历所有线程栈，将对象锁为该类的epoch字段更新
* 批量撤销首先将当前类的可偏向标记关闭，然后遍历所有线程栈，将对象锁为该类进行撤销偏向操作





[死磕synchronized的偏向锁](https://github.com/farmerjohngit/myblog/issues/13)





#### 轻量级锁状态

在Java程序运行时，同步代码块中的代码是不存在竞争的，而是不同的线程交替执行同步块中的代码。因此引入了轻量级锁的概念，由于Java是以对象为锁的，因此需要记录该对象方便操作，JVM会在当前线程的栈中创建一个Lock Record锁记录，用来存储对象头的mark word字段，同时还有一个指向对象的指针



**获取**

获取轻量级锁的代码逻辑位于**获取偏向锁代码逻辑**中，当获取偏向锁存在竞争或者对象锁不是偏向模式，那么会进入获取轻量级锁的逻辑

* 创建无锁状态的mark word并设置到锁记录中，锁记录中的mark word称之为Displaced Mark Word
* 然后使用CAS进行替换，将对象锁与Displaced Mark Word进行交换（对象锁所标记信息从01变为00）如果替换失败，表明该对象不是无锁状态，这个时候需要判断是否为当前线程重入
* HotSpot采用了一种简单而高效的方法来处理重入，每次获得锁都添加一个锁记录，在当前线程判断是否存在该对象锁
* 如果为当前线程为重入则直接将Displaced Mark Word设置为null
* 否则需要膨胀为重量级锁





**释放**

* 从低往高遍历栈中的锁记录
* 如果锁记录关联的是该对象则释放锁记录
* 如果锁记录的Displaced Mark Word字段不为null，那么需要用CAS替换对象锁的Mark Word字段
* 如果为null表示重入，直接释放锁记录表示重入次数减一
* CAS替换失败，说明解锁时发生了线程竞争，膨胀为重量级锁



#### 重量级锁状态

重量级锁为传统意义上的锁，利用了操作系统底层的同步机制去实现Java的线程同步，重量级锁状态下，对象的mark word字段为指向一个堆中monitor对象的指针，monitor包含了几个关键的字段cxq、EntryList、owner



**重量级的膨胀和加锁流程**

当出现多个线程竞争的情况下，会进入到slow_enter方法，然后执行inflate函数完成膨胀过程

* inflate为一个for循环，是为了处理多线程同时调用inflate的情况，每个线程根据锁对象的不同状态工作
* 如果为重量级锁则返回
* 如果是膨胀中状态，则进行等待，等待操作使用了自旋锁
* 如果是轻量级锁则进行膨胀操作，轻量级锁膨胀过程如下
  * 分配一个ObjMonitor对象并对其进行初始化
  * 使用CAS操作将状态设置为膨胀中
  * 将monitor对象mark word字段设置为线程栈中的displaced mark word字段
  * 最后将锁对象状态设置为重量级锁状态，此时对象锁的对象头mark word字段的锁标记信息为10
* 如果为无锁状态，则进行膨胀操作，无锁膨胀过程如下
  * 分配一个ObjMonitor对象并对其进行初始化
  * 将monitor对象的owner设置为null
  * 用CAS替换对象头的mark word为重量级锁状态
  * 如果不成功说明另外的线程正在执行inflate，当前线程释放monitor并返回
* 膨胀完成后会调用enter方法获得锁
* 如果为无锁状态、锁重入、持有该对象的轻量级锁的线程进行简单操作即可返回，比如锁重入情况，则重入次数加一
* 否则先尝试自旋获得锁，如果成功则直接返回
* 失败则调用enterI方法，多个线程尝试获得锁时，需要将线程封装成monitor对象然后插入cxq队列的头部等待，cxq为一个单链表
* 如果线程释放锁，则会从cxq队列或者EntryList中挑选一个线程唤醒并尝试去获得锁





**释放**

* 设置owner对象为null，即当前线程释放了锁
* 如果没有等待线程，则直接返回，否则选择一个线程唤醒
* 依据QMode的不同，会执行不同的唤醒策略，默认为0
* 如果QMode为0时，EntryList为空，cxq不为空时，会将cxq所有元素放入EntryList，再从EntryList取出队首元素
* 唤醒该线程并占有锁





#### 自旋锁

由于线程的阻塞与唤醒需要由用户态转为内核态，频繁的阻塞和唤醒会给并发性能带来很大的压力，那么为了不让线程阻塞，就让其进行忙等，看看持有锁的线程能否很快释放锁，自旋锁虽然避免了线程切换的开销，但是也消耗了处理器的时间，如果锁占用时间过长，显然自旋锁等待时间需要一定限度，不然会白白浪费处理器时间，得不偿失。

JDK1.6中，引入了自适应自旋锁，虚拟机可以根据程序运行和性能监控信息不断完善自旋锁信息，自旋锁的自旋时间也会变得灵活，提高了自旋锁的性能



#### 锁消除

锁消除是指是指虚拟机即时编译器（JIT）运行时，对一些代码上要求同步，但是检测到不可被共享的数据竞争的锁消除，锁消除的原理是逃逸分析，如果判断一段代码中，堆上的所有数据都不会逃逸出去被其它线程访问到，那就可以把它们是线程私有，从而无需加锁。





### wait&notify&notifyAll



### park&unpark







## JMM

### 概念

Java内存模型不是真实存在的，它是为了能够屏蔽各种硬件和操作系统的内存访问差异，实现Java程序在各个平台都能达到一致的访问效果，从而使得Java的并发内存访问操作不会产生任何歧义。Java内存模型关心变量从内存取出和写入这样的底层细节，这些变量首先是线程共享的（实例字段、静态字段、数组对象），并不包括局部变量，因为它是线程共享的，不会被共享，自然不会存在竞争问题。Java内存模型没有限制工作内存使用特定的寄存器或缓存来访问主内存，所有变量都存储在主内存，每条线程还拥有自己的工作内存，工作内存保存的是被线程使用的变量的主内存副本，线程对变量的所有操作都必须在工作内存进行，不同线程不能访问不同线程的工作内存，也不能直接读取主内存的数据，线程间变量传递需要经过主内存来完成





### 特性





### volatile原理

volatile是Java虚拟机提供的一种**轻量**级**同步**机制，它有三个特点

* 可见性
* 不保证原子性
* 禁止指令重排





### happens-before规则





## JUC







## 线程池

























# 多线程设计模式



## 两阶段终止





## 保护性暂停



## 生产者消费者模式



## 固定运行顺序





## 交替输出



## 犹豫模式

