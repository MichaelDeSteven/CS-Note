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
| isInterrupted()  | 判断线程是否被打断           | 不会清除打断标记                                             |
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

调用sleep或者wait有参方法会使线程进入TimedWaiting状态

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

无限期等待，需要等待其它线程来唤醒，比如使用了join方法、wait无参方法等待其它线程执行完毕的线程状态为waiting





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

具体实现详见多线程设计模式



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

公平锁：

非公平锁：

读写锁：

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



**适用场景**

结合CAS和volatile可以实现无锁并发，适用于线程数少、多核CPU的情况

* CAS是基于乐观锁的思想



**ABA问题**

问题描述：假设原来的值为100，线程A执行CAS



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

* obj.wait()让进入object监视器的线程到waitSet等待
* obj.notify()在obj上正在waitSet等待的线程中挑一个唤醒
* obj.notifyAll()让obj上正在waitSet等待的线程全部唤醒

```java
    /**
     *     synchronized (obj) {
     *         while (&lt;condition does not hold&gt;)
     *             obj.wait();
     *         ... // Perform action appropriate to condition
     *     }
     * wait方法首先需要获得对象锁，如果没有对象锁则会抛出IllegalMonitorStateException异常
     * 使用wait方法会让当前线程在monitor的waitSet等待直到被唤醒
     * @throws  IllegalMonitorStateException  if the current thread is not
     *               the owner of the object's monitor.
     * @throws  InterruptedException if any thread interrupted the
     *             current thread before or while the current thread
     *             was waiting for a notification.  The <i>interrupted
     *             status</i> of the current thread is cleared when
     *             this exception is thrown.
     * @see        java.lang.Object#notify()
     * @see        java.lang.Object#notifyAll()
     */
    public final void wait() throws InterruptedException {
        wait(0);
    }

```

sleep和wait区别

* sleep是Thread的方法，wait是Object的方法

* 原理不同，sleep是让线程主动挂起，线程状态从RUNNABLE变为Timed Waiting，而wait需要获取对象锁，然后会进入waitSet等待，线程状态从RUNNABLE变为Timed Waiting，同时会主动释放对象锁
* sleep不释放以获取的锁资源，wait会释放当前获取的对象锁
* sleep需要指定睡眠的时间，wait可以无限等待
* sleep到了指定睡眠时间会唤醒，wait需要使用notify或者notifyAll来唤醒
* sleep由于等待时会持有锁资源，很容易造成死锁，因此一般采用wait来保证条件不满足时线程等待，这样能够提高效率，防止死锁



### join

线程同步机制的一种，它的底层原理即为wait，通过调用线程来轮询线程的alive状态

```java
t1.join()
// 等下与下面代码
synchronized (t1) {
 // 调用者线程进入 t1 的 waitSet 等待, 直到 t1 运行结束
 while (t1.isAlive()) {
 t1.wait(0);
 }
}
```





### park&unpark







## JMM

### 概念

Java内存模型不是真实存在的，它是为了能够屏蔽各种硬件和操作系统的内存访问差异，实现Java程序在各个平台都能达到一致的访问效果，从而使得Java的并发内存访问操作不会产生任何歧义。Java内存模型关心变量从内存取出和写入这样的底层细节，这些变量首先是线程共享的（实例字段、静态字段、数组对象），并不包括局部变量，因为它是线程共享的，不会被共享，自然不会存在竞争问题。Java内存模型没有限制工作内存使用特定的寄存器或缓存来访问主内存，所有变量都存储在主内存，每条线程还拥有自己的工作内存，工作内存保存的是被线程使用的变量的主内存副本，线程对变量的所有操作都必须在工作内存进行，不同线程不能访问不同线程的工作内存，也不能直接读取主内存的数据，线程间变量传递需要经过主内存来完成

![](C:\Users\Steven\Desktop\CS-Note\java并发\pic\主内存和工作内存.png)

这里的主内存和工作内存并不与JVM内存区域的堆、栈、方法区完全对应，主内存对应Java堆中的对象实例数据部分，一般指的是物理内存，而工作内存是Java虚拟机栈的一部分，由于程序访问的主要是工作区，所以工作内存一般位于寄存器或者高速缓存中



### 缓存与并发

**概述**

并发编程复杂程度很大原因是来源于CPU硬件性能的提升带来的，由于CPU性能和存储器日益增大，因此引入了缓存的问题，CPU和内存中设置了三级缓存，分别为L1\L2\L3高速缓存，比起访问内存的速度，高速缓存的速度明显与CPU速度相匹配，从L1到L3的容量会越来越大，而速度相对而言会越来越慢，CPU访问数据，首先从缓存中取，如果缓存没有则从内存中取。正因此，产生了并发时的缓存不一致问题多核CPU下的高速缓存各不相同，某一个CPU修改缓存的数据，可能与其它CPU的缓存不一致，因此引发的并发情况下缓存不一致问题。



**总线锁和缓存锁**

为了解决缓存一致性问题也就是**保证原子性**，有一个简单的办法是**总线锁**，总线锁，顾名思义就是锁住总线，通过处理器发送的lock指令，总线接收到指令后。其它处理器的请求就会处于阻塞，直到此处理器执行完成，显然这个做最大的缺点就是其他处理器请求被阻塞，系统开销较大。第二种方法即使用**缓存锁**，缓存锁即锁住共享对象所在的缓存行，处理器通过缓存一致性协议，阻止了两个以上的处理器修改缓存所在的内存区域，当其它处理器回写已被锁定的缓存行数据时，会使缓存行无效



**MESI协议**

缓存一致性协议的一种，用2bit表示下面四个状态

* M（Modified）：代表该缓存行中的内容被修改，且该缓存行只被缓存在该CPU中
* E（Exclusive）：该缓存行对应的内存区域只被该CPU缓存
* S（Shared）：缓存对应的内存区域在多个CPU被缓存
* I（Invaild）：表示该缓存行的内容无效



MESI协议中，每个缓存行不仅知道自己的读写操作，同时也监听其它缓存行的读写操作，根据自己的缓存行和其它CPU缓存行的读写操作进行状态转移

它的监听机制也叫做**总线嗅探机制**，它的本质就是总线将信号广播到所有的处理器，每个处理器通过监听总线上传播的数据来检查自己的缓存是否过期，如果处理器发现自己的缓存行对应的内存地址修改，就会将当前处理器的缓存行设置为无效







[MESI状态转移](https://blog.csdn.net/xiaowenmu1/article/details/89705740)



**伪共享问题**

在多核多线程下，由于不同共享变量存在于同一缓存行，某个处理器对某一个共享变量进行修改时，本处理器会将缓存行写回内存，引起了其它处理器对应的缓存行无效，进而影响了同一缓存行下其它共享变量，如果其它处理器需要使用该共享变量，就需要重新从内存相应位置中读取，增加了时间的开销

* 可以利用**空间换时间**的办法解决：缓存行填充



**内存屏障**

硬件层面的”内存屏障“

* sfence：即写屏障，在写指令之后插入写凭证，能让写入的缓存最新数据写回主内存
* lfence：即读屏障，在读指令前插入读屏障，可以让高速缓存的数据失效，重新从主内存加载数据，保证读取的是最新数据
* mfence：即全能屏障，兼具写屏障和读屏障功能

JMM层面的”内存屏障“

* LoadLoad屏障：对于Load1；LL；Load2；保证了Load2及其后面语句执行之前，Load1要读取的语句被读取完毕
* StoreStore屏障：对于Store1；SS；Store2；保证了Store2及其后面语句执行之前，Store1写入可被其它处理器可见
* LoadStore屏障：对于Load1；LS；Store2；保证了Store2及其后面语句执行之前，Load1要读取的语句被读取完毕
* StoreLoad屏障：对于Store1；SL；Load2；保证了Load2及其后面语句执行之前，Store1写入可被其它处理器可见





### 特性

* 原子性：定义了一系列原子性操作，每个操作是一个不可分割的整体，这个整体要么都执行成功，要么都执行失败

* 可见性：线程在修改共享变量时，其它线程能够立即得知这个修改

* 有序性：禁止指令重排的发生



**可见性**

Java线程都有各自的工作内存，数据修改时都是在自己的工作内存，因此是对主存共享变量的副本进行操作的，如果没有写回主内存时，其它线程是不可见的，需要注意的是可见性只保证了一个线程对共享变量进行写操作，其它线程均为可见，如果多个线程对共享变量进行写时不能保证原子性



**有序性**

* 为了更好的性能，编译器、处理器会对指令进行重排序
* 指令重排序的前提是指令不存在数据的依赖性，并不影响结果的执行，单线程下就可以通过指令重排序进行优化
* 但是在多线程环境中，指令重排可能会改变程序的执行结果





### volatile原理

volatile是Java虚拟机提供的一种**轻量**级**同步**机制，它有三个特点

* 可见性
* 不保证原子性
* 禁止指令重排



底层原理为**内存屏障**

**如何保证可见性？**

利用缓存锁和缓存一致性协议进行解决



**怎么禁止指令重排？**

使用内存屏障

JVM在volatile读写操作均会加入内存屏障

* volatile读操作：JMM会将该线程对应的工作内存设为无效，接下来从主内存中读取共享变量，为保证volatile的正确语义，在volatile读操作后依次插入LoadLoad、LoadStore操作，分别表示禁止下面所有读操作与volatile读操作重排序和禁止下面所有写操作与volatile读操作重排序
* volatile写操作：JMM会将线程对应的工作内存中的共享变量值刷新到主内存，为保证volatile的正确语义，在volatile写操作前插入StoreStore、后面插入StoreLoad，分别表示禁止上面普通写与volatile写操作重排序，和防止下面volatile读写操作与volatile写发生重排序

```java
volatile读操作
// 插入LoadLoad
// 插入LoadStore

// 插入StoreStore
volatile写操作
// 插入StoreLoad操作
```





### final原理

final意为不可改变的，该关键字可以修饰类、方法、字段，用final修饰可以保证一定的线程安全

对于final域，需要遵循两个重排序规则·

* 在构造函数内对一个final域写入，与把这个对象的引用赋值给一个引用变量时，这两个操作不能重排序
* 初次读写一个包含final域的对象的引用与读这个final域，这两个操作不能重排序



**写final**

* 写final操作一定会在构造函数return之前执行完，同时还需要保证构造函数内没有溢出

* final写操作后会插入一条写屏障（StoreStore）



**读final**

* 初次读取final域对象引用和读这个final域存在间接依赖，因此编译器需要保证这两个指令之间的有序性
* final读操作前会插入一条读屏障（LoadLoad）



**final引用**

* 与final写操作类似，在构造函数内对final引用对象的成员变量先行发生于读取final引用对象成员变量



### happens-before规则

先行发生原则是对JMM的可见性和有序性的一套总结，如果Java内存模型的所有有序性仅靠volatile和synchronized关键字来完成，显然这个操作是非常麻烦的，而实际编写并发代码中，我们并没有察觉这一点，这是因为Java语言有一套先行发生原则，从而不让我们陷入JMM苦涩难懂的定义。

先行发生是JMM中定义的两项操作的偏序关系（自反、反对称、传递），如果操作A先行发生于操作B，那么操作B之前操作A产生的影响能被B察觉到，这里的影响是指修改了内存共享变量的值、发送消息等，下面的规则就是天然的先行发生关系，这些关系不需要借助同步器协助就已经存在，虚拟机也就不会对这些指令重排序



* 程序次序规则：在一个线程中，书写前的代码先行发生于书写后的代码，即执行代码顺序按照控制流的顺序
* 管程锁定规则：一个unlock操作先行发生于后面对同一个锁的lock操作
* volatile变量规则：对一个volatile变量的写操作先行发生于后面对这个变量的读操作
* 线程启动规则：Thread对象的start方法先行发生于此线程的每一个动作
* 线程终止规则：线程的所有操作先行发生于对此线程的终止检测（join、isAlive）
* 线程中断规则：对线程interrupt方法调用线程发生于被中断线程的代码检测到中断事件的发生
* 对象终结规则：一个对象初始化的完成（构造函数执行完毕）先行发生于它的finalize方法的开始
* 传递性：如果操作A先行发生于B，B先行发生于C，那么A先行发生于C



**先行发生与时间上的先发生并无关系**

```java
private int value = 0;
public void setValue(int value) {
    this.value = value;
}
public int getValue() {
    return value;
}
```

* 这里线程A先执行了setValue，线程B后执行getValue，由于发生在两个线程，所以程序次序规则并不适用，因此执行结果不确定，所以时间上的先发生并不能推导出先行发生

```java
// 在同一线程执行
int i = 10
int j = 1
```

* 上面两条指令在同一线程中执行，按照程序次序规则，int i = 10先行发生于int j = 1，但是int j = 1却有可能时间上先行执行，然而这并不影响程序的正确性，因为线程没办法感知这一点，因此一个操作先行发生不能推导出时间上的先发生

综上所属A先行发生B是指操作A的产生的影响能被操作B察觉，而不是A时间上先发生于B









## JUC

### atomic

提供了原子类，原理是基于CAS实现的



#### 原子整型

原子整数包括了

* AtomicInteger
* AtomicLong
* AtomicBoolean

以AtomicInteger为例，常用的API有如下

```java
public class Api {
    public static void main(String[] args) {
        AtomicInteger x = new AtomicInteger(1);

        System.out.println(x.incrementAndGet()); // 2
        System.out.println(x.getAndDecrement()); // 1
        System.out.println(x.get()); // 1
        do {
            int prev = x.get(); // 1
            int next = prev + 2; // 3
            // 比较，与prev相同则交换，不相同则重试
            if (x.compareAndSet(prev, next)) {
                break;
            }
        } while (true);
        System.out.println(x.get());

        // 除了其它运算符操作
        System.out.println(x.updateAndGet(t -> t / 2));
        System.out.println(updateAndGet(x, t -> t * 3));
    }

    public static int updateAndGet(AtomicInteger i, IntUnaryOperator operator) {
        do {
            int prev = i.get();
            int next = operator.applyAsInt(prev);
            if (i.compareAndSet(prev, next)) {
                return next;
            }
        } while (true);
    }
}

```







#### 原子引用

* AtomicReference
* AtomicStampedReference
* AtomicMarkableReference



原子引用用于并发情况下引用类型的原子替换



#### 原子数组

* AtomicIntegerArray
* AtomicLongArray
* AtomicReferenceArray





#### 字段更新器

* AtomicIntegerFieldUpdater
* AtomicLongFieldUpdater
* AtmoicReferenceUpdater



#### 原子累加器

* LongAddr
* LongAccumulator

在高并发下的性能比atomic包的其它累加器更好



# **//TODO源码解读**

```java
final void longAccumulate(long x, LongBinaryOperator fn,
                          boolean wasUncontended) {
    int h;
    if ((h = getProbe()) == 0) {
        ThreadLocalRandom.current(); // force initialization
        h = getProbe();
        wasUncontended = true;
    }
    boolean collide = false;                // True if last slot nonempty
    for (;;) {
        Cell[] as; Cell a; int n; long v;
        if ((as = cells) != null && (n = as.length) > 0) {
            if ((a = as[(n - 1) & h]) == null) {
                if (cellsBusy == 0) {       // Try to attach new Cell
                    Cell r = new Cell(x);   // Optimistically create
                    if (cellsBusy == 0 && casCellsBusy()) {
                        boolean created = false;
                        try {               // Recheck under lock
                            Cell[] rs; int m, j;
                            if ((rs = cells) != null &&
                                (m = rs.length) > 0 &&
                                rs[j = (m - 1) & h] == null) {
                                rs[j] = r;
                                created = true;
                            }
                        } finally {
                            cellsBusy = 0;
                        }
                        if (created)
                            break;
                        continue;           // Slot is now non-empty
                    }
                }
                collide = false;
            }
            else if (!wasUncontended)       // CAS already known to fail
                wasUncontended = true;      // Continue after rehash
            else if (a.cas(v = a.value, ((fn == null) ? v + x :
                                         fn.applyAsLong(v, x))))
                break;
            else if (n >= NCPU || cells != as)
                collide = false;            // At max size or stale
            else if (!collide)
                collide = true;
            else if (cellsBusy == 0 && casCellsBusy()) {
                try {
                    if (cells == as) {      // Expand table unless stale
                        Cell[] rs = new Cell[n << 1];
                        for (int i = 0; i < n; ++i)
                            rs[i] = as[i];
                        cells = rs;
                    }
                } finally {
                    cellsBusy = 0;
                }
                collide = false;
                continue;                   // Retry with expanded table
            }
            h = advanceProbe(h);
        }
        else if (cellsBusy == 0 && cells == as && casCellsBusy()) {
            boolean init = false;
            try {                           // Initialize table
                if (cells == as) {
                    Cell[] rs = new Cell[2];
                    rs[h & 1] = new Cell(x);
                    cells = rs;
                    init = true;
                }
            } finally {
                cellsBusy = 0;
            }
            if (init)
                break;
        }
        else if (casBase(v = base, ((fn == null) ? v + x :
                                    fn.applyAsLong(v, x))))
            break;                          // Fall back on using base
    }
}
```







#### Unsafe





#### 原子整数简单实现









### 线程池

#### 作用

* 线程的创建与销毁需要消耗系统资源，通过重复利用已创建的线程可以降低资源的消耗
* 线程的创建需要时间，而使用线程池时，当任务到达且有空闲线程时，任务就能立即执行，提高了响应时间
* 使用线程池可以对创建的线程进行统一的监控和管理，提高线程的可管理性



#### 实现原理

![](C:\Users\Steven\Desktop\CS-Note\java并发\pic\线程池实现原理.png)

**步骤**

1. 用户先向线程池提交任务
2. 如果核心线程池没有满，则创建线程执行当前任务，否则执行3
3. 判断阻塞队列是否已满，没有满则将任务存储在队列中，等待当前线程池的核心线程执行
4. 阻塞队列已满，判断线程池是否已满（是否存在急救线程）
5. 如果没满，则创建急救线程执行任务
6. 如果满了则按照指定的拒绝策略对任务进行处理

急救线程：是指核心线程池满了，且阻塞队列也满了，临时创建出来执行任务，执行完毕后，待一定时间没有新的任务时，则会自动销毁





#### 拒绝策略

```java
// 拒绝策略抽象接口，采用策略模式，来实现具体的拒绝策略
public interface RejectedExecutionHandler {
    void rejectedExecution(Runnable r, ThreadPoolExecutor executor);
}
```

JDK提供了四种拒绝策略

* 直接让调用者执行任务

```java
public static class CallerRunsPolicy implements RejectedExecutionHandler {
    public CallerRunsPolicy() { }
    // 如果线程池没有被关闭，则在使用调用者线程执行任务
    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
        if (!e.isShutdown()) {
            r.run();
        }
    }
}
```

* 丢弃任务，并抛出异常

```java
public static class AbortPolicy implements RejectedExecutionHandler {
    public AbortPolicy() { }
    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
        throw new RejectedExecutionException("Task " + r.toString() +
                                             " rejected from " +
                                             e.toString());
    }
}
```

* 忽略任务

```java
public static class DiscardPolicy implements RejectedExecutionHandler {
    public DiscardPolicy() { }

    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
    }
}
```

* 如果线程池没有被关闭，那么取出阻塞队列的最早的任务，使用当前任务进行替代

```java
public static class DiscardOldestPolicy implements RejectedExecutionHandler {
    public DiscardOldestPolicy() { }

    public void rejectedExecution(Runnable r, ThreadPoolExecutor e) {
        if (!e.isShutdown()) {
            e.getQueue().poll();
            e.execute(r);
        }
    }
}
```

拒绝策略除此之外还有

* 抛出异常前会记录日志，同时dump线程栈信息，方便定位问题
* 创建一个新的线程执行任务
* 等待指定时间后尝试放入队列
* 使用拒绝策略链，逐一尝试每个拒绝策略





#### 线程池状态



| 线程池状态 | 高3位 | 含义                                                         |
| ---------- | ----- | ------------------------------------------------------------ |
| RUNNING    | 111   |                                                              |
| SHUTDOWN   | 000   | 不会接收新任务，但会处理阻塞队列剩余任务                     |
| STOP       | 001   | 会中断正在执行的任务，并抛弃阻塞队列任务                     |
| TIDYING    | 010   | 任务全部执行完毕，活动线程为0，将调用terminated()即将进入终结状态 |
| TERMINATED | 011   | 终结状态                                                     |





#### 构造方法

```java
public ThreadPoolExecutor(int corePoolSize,
                          int maximumPoolSize,
                          long keepAliveTime,
                          TimeUnit unit,
                          BlockingQueue<Runnable> workQueue,
                          ThreadFactory threadFactory,
                          RejectedExecutionHandler handler)
```

**参数说明**

* corePoolSize：核心线程数
* maximumPoolSize：线程池最大线程数（核心线程数+急救线程数）
* keepAliveTime：急救线程空闲最长等待时间，超过则销毁
* unit：时间单元
* workQueue：阻塞队列
* threadFactory：线程工厂，设置线程的信息，如名称
* handler：拒绝策略





#### 提交任务

```java
// 执行任务
void execute(Runnable command);
// 提交任务task，带有返回值
public Future<?> submit(Runnable task)
// 提交所有任务
public <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks)
// 提交所有任务，带有超时时间
public <T> List<Future<T>> invokeAll(Collection<? extends Callable<T>> tasks,long timeout, TimeUnit unit)
// 提交所有任务，执行完第一个任务则直接返回
public <T> T invokeAny(Collection<? extends Callable<T>> tasks)
// 提交所有任务，执行完第一个任务则直接返回，带有超时时间
public <T> T invokeAny(Collection<? extends Callable<T>> tasks,long timeout, TimeUnit unit)
```





#### 关闭线程池

**shutdown**

```java
public void shutdown()
```

**shutdownNow**

```java
public List<Runnable> shutdownNow()
```



#### 各类线程池

根据线程池的构造方法，JDK的Executor提供了各类线程池

**newFixedThreadPool**

```java
public static ExecutorService newFixedThreadPool(int nThreads) {
    return new ThreadPoolExecutor(nThreads, nThreads,
                                  0L, TimeUnit.MILLISECONDS,
                                  new LinkedBlockingQueue<Runnable>());
}
```

特点

* LinkedBlockingQueue基于链表的无界阻塞队列，此队列按FIFO排序元素，因此不执行拒绝策略
* 最大线程数等于核心线程数，无需超时时间
* 适用于任务量已知，相对耗时的任务



**newCachedThreadPool**

```java
public static ExecutorService newCachedThreadPool() {
    return new ThreadPoolExecutor(0, Integer.MAX_VALUE,
                                  60L, TimeUnit.SECONDS,
                                  new SynchronousQueue<Runnable>());
}
```

特点

* 阻塞队列采用SynchronousQueue，没有存储空间的阻塞队列，每个插入操作必须等待线程来调用移除操作

* 核心线程数为0，急救线程数最大为Integer.MAX_VALUE，急救线程空闲剩余时间为60L
* 适用于任务数比较密集，每个任务执行时间短



**newSingleThreadPool**

```java
public static ExecutorService newSingleThreadExecutor() {
    return new FinalizableDelegatedExecutorService
        (new ThreadPoolExecutor(1, 1,
                                0L, TimeUnit.MILLISECONDS,
                                new LinkedBlockingQueue<Runnable>()));
}
```

特点

* 阻塞队列使用LinkedBlockingQueue无界阻塞队列
* 适用于单个线程执行周期性的任务，同时保证每个任务按顺序执行



#### 线程池配置





#### 手写线程池

PS：面试必备





### Frok/Join





### AQS

AQS俗称队列同步器，是用来构建锁和同步组件的基本框架，几乎任一同步器能够实现其他形式的同步器，如可重入锁可以实现信号量，也可以用信号量来实现可重入锁，但是这样会带来复杂度、不灵活等问题，因此需要一种同步器能用最简洁和本质的方法同时性能来构建其它的同步器，AQS就为构造几乎任意类型同步器提供了一种通用机制



#### 实现目标

* 能够实现阻塞版本获取锁和非阻塞版本获取锁
* 获取锁超时机制
* 中断取消机制
* 独占机制以及共享机制
* 条件不满足时等待机制（条件变量）



#### 设计和实现

同步器的设计基本思路很直接

* acquire获取锁

```java
// 不允许获取同步状态
while (synchronization state does not allow acquire) {
// 如果没有入队则设置结点并进入同步队列
enqueue current thread if not already queued;
// 可能进入阻塞等待
possibly block current thread;
}
// 获取到同步
dequeue current thread if it was queued;

总结：线程获取同步状态失败，如果没有入队，那么包装成Node并加入同步队列，自旋不断获取同步状态，同时也能选择阻塞当前线程
    线程如果获取到了同步状态，那么当前线程出队
```



* release释放锁

```java
// 更新同步状态
update synchronization state;
// 阻塞等待的线程满足获取锁条件则解锁
if (state may permit a blocked thread to acquire)
unblock one or more queued threads;

获取到了同步状态，则恢复阻塞的线程
```



完成上述操作需要三个基本组成部分

* 同步状态的原子性维护
* 阻塞以及恢复线程
* 同步队列的维护



**同步状态**

* AQS类使用int来维持同步状态，同时给出了同步状态的getter/setter方法和CAS操作来访问和更新同步状态，这些方法依赖了volatile和CAS机制
* 使用AQS来实现同步器时，需要实现tryAcquire和tryRelease，这两个方法需要依赖同步状态访问和更新方法来实现，同时AQS采用模板方法模式，acquire和release定好了整个同步状态的获取和释放的流程



**阻塞**

* JSR166之前都是基于Monitor管程来管理线程的阻塞和恢复，几乎没有JAVA API层面的方法来实现
* API唯一拥有这种功能是Thread方法下的suspend和resume，但是这两个方法有缺陷，如果先调用resume再调用suspend并没有效果，很容易造成死锁的发生，现在这两个方法已经被弃用
* locks包下的LockSupport的park&unpark解决了上面的问题，park可以用来阻塞当前线程，而unpark可以解除阻塞，同时unpark可以先于park调用，这两个方法是以线程为参数的，而不需要获取Monitor





**同步队列**

* 如果说AQS是JUC的核心，那么同步队列就是AQS的基石，同步队列的最佳选择就是使用不依赖任何锁的不阻塞数据结构
* AQS选择了基于CLH锁基本思想作为了同步队列，该队列是FIFO队列，所以并不支持基于优先级的队列
* 选择CLH锁的原因就是它很适合用来实现超时和阻塞的功能





**CLH锁**

```java
// 入队
do { 
	pred = tail;
} while(!tail.compareAndSet(pred, node));

// 出队
while (pred.status != RELEASED) ; // spin
// 出队只需简单地将node结点设置为head
head = node;
```

* CLH锁是一个单向队列，一开始head和tail指向同一个dummy，每个结点指向前一个结点
* CLH锁有出队入队操作快的优点，同时该操作是无锁操作
* 即使在竞争的情况下，线程也总有机会插入同步队列
* 判断线程是否阻塞，也只要简单地判断线程对应的结点是否为head结点
* 结点的relase状态保存在了前驱结点上



AQS的同步队列主要对CLH锁做了两点改进

* 每个结点设置一个指针，指向后继结点，这样做的原因是在CLH锁，下一个要获取锁的结点是自旋，那么结点修改自身的状态，那么即使不需要链接，后继结点也会通过自旋+CAS操作来成功获取锁，但是在阻塞同步器中，下一个要获取的结点是阻塞的，因此结点需要能知道后继结点并使用unpark将其唤醒
  * 结点的链接是双链表链接的操作，需要两步
  * node.prev = pred，这一步会有CAS的原子操作保证，因此每个结点一定能够正确找到它真正的前驱结点
  * pred.next = node，这一步只是简单的赋值操作，因此后继结点可能为null或者状态为cancelled
* 第二个主要的改进是每个结点使用状态字段来控制线程阻塞而不是自旋

同步队列的底层数据结构为双向链表，Node结点记录则结点的状态、线程的信息、前驱结点、后继结点等。同步队列基于CLH锁的思想



**等待状态**

* CANCELLED：值为1，节点由于等待超时或者被中断，需要从同步队列中取消等待，节点进入该状态将不会变化
* SIGNAL：值为-1，后继节点处于等待状态，而当前节点将要被释放或者取消，当前节点将会通知后继节点，使得后继节点的线程得以运行
* CONDITION：值为-2，当前节点在等待队列中，如果别的线程使用Condition中的signal方法，当前节点将会从等待队列转移到同步队列中，加入到对同步状态的获取中
* PROPAGATE：值为-3，表示下一次共享式获取将被无条件传播下去
* INITIAL：值为0，初始状态





#### 独占式同步状态获取与释放



```java
// 模板方法：子类实现tryAcquire
public final void acquire(int arg) {
    if (!tryAcquire(arg) &&
        acquireQueued(addWaiter(Node.EXCLUSIVE), arg))
        selfInterrupt();
}
// 将线程包装成Node结点，插入同步队列队尾
private Node addWaiter(Node mode) {
    // 创建Node结点，保存当前线程以及Node结点状态
    Node node = new Node(Thread.currentThread(), mode);
    // 如果队列不为空，首先尝试直接将Node节点加入队尾
    Node pred = tail;
    if (pred != null) {
        node.prev = pred;
        // 使用CAS操作，如果没有多线程竞争，那么加入队尾成功，直接返回Node结点
        if (compareAndSetTail(pred, node)) {
            pred.next = node;
            return node;
        }
    }
    // 如果队列为空或者node没有成功设置为tail，则进入enq
    enq(node);
    return node;
}
private Node enq(final Node node) {
    // 自旋操作，直到结点顺利被加入同步队列
    for (;;) {
        Node t = tail;
        // 如果同步队列为空，初始化一个Node结点
        if (t == null) { // Must initialize
            if (compareAndSetHead(new Node()))
                tail = head;
        // 同步队列不为空，尝试将其设置为tail结点，成功则返回
        } else {
            node.prev = t;
            if (compareAndSetTail(t, node)) {
                t.next = node;
                return t;
            }
        }
    }
}

// 使用unsafe包下的CAS操作
private final boolean compareAndSetHead(Node update) {
    return unsafe.compareAndSwapObject(this, headOffset, null, update);
}

private final boolean compareAndSetTail(Node expect, Node update) {
    return unsafe.compareAndSwapObject(this, tailOffset, expect, update);
}

// 尝试获取同步状态
final boolean acquireQueued(final Node node, int arg) {
    // 默认failed=true表示获取同步状态失败
    boolean failed = true;
    try {
        // 默认中断标志为false
        boolean interrupted = false;
        for (;;) {
            // 获取node的直接前驱结点p
            final Node p = node.predecessor();
            // 如果p为head结点，那么node结点尝试获取同步状态
            if (p == head && tryAcquire(arg)) {
                // 获取成功则将node设置为head结点，释放p，同时failed为false表示获取同步状态成功
                setHead(node);
                p.next = null; // help GC
                failed = false;
                return interrupted;
            }
            // 如果获取同步状态失败则判断是否需要上锁等待，如果要上锁等待还要判断线程是否中断
            if (shouldParkAfterFailedAcquire(p, node) &&
                parkAndCheckInterrupt())
                interrupted = true;
        }
    } finally {
        // 只有当线程被中断时，failed才为true
        if (failed)
            cancelAcquire(node);
    }
}
// 获取同步状态失败后根据节点状态判断是否需要进入等待状态
private static boolean shouldParkAfterFailedAcquire(Node pred, Node node) {
    int ws = pred.waitStatus;
    // 前驱节点已经是SIGNAL状态准备获取同步状态，因此node节点上锁等待即可
    if (ws == Node.SIGNAL)
        return true;
    // CANCELLED状态值为1，唯一一个状态大于0
    if (ws > 0) {
        // p节点将从同步队列中取消等待，将node节点挪到最后一个节点不是CANCELLED状态中
        do {
            node.prev = pred = pred.prev;
        } while (pred.waitStatus > 0);
        pred.next = node;
    } else {
        // 状态为不为CANCELLED或SIGNAL时，在等待之前，使用CAS操作尝试将前驱节点变为SIGNAL状态
        // 成功的话下一次进入该函数就会返回true进入parkAndCheckInterrupt停止自旋
        compareAndSetWaitStatus(pred, ws, Node.SIGNAL);
    }
    // 前驱节点不为SIGNAL状态node节点一定会进入等待
    return false;
}

// 上锁并检查线程是否中断
private final boolean parkAndCheckInterrupt() {
    LockSupport.park(this);
    return Thread.interrupted();
}

// 尝试将该节点从同步队列中取消
private void cancelAcquire(Node node) {
    // Ignore if node doesn't exist
    if (node == null)
        return;

    node.thread = null;

    // 跳过前驱节点为CANCELLED状态，node节点的直接前驱节点状态一定不为CANCELLED
    Node pred = node.prev;
    while (pred.waitStatus > 0)
        node.prev = pred = pred.prev;

    // predNext即为第一个不为CANCELLED状态的前驱节点
    Node predNext = pred.next;

    // 将node节点设置为CANCELLED
    node.waitStatus = Node.CANCELLED;

    // 如果node为tail，使用CAS将tail修改为前驱结点
    if (node == tail && compareAndSetTail(node, pred)) {
        compareAndSetNext(pred, predNext, null);
    } else {
        // 如果前驱结点不为head且（前驱结点状态为SIGNAL或者能通过CAS成功将其修改为SIGNAL状态）
        // 那么将node的前驱结点和后驱结点相连
        int ws;
        if (pred != head &&
            ((ws = pred.waitStatus) == Node.SIGNAL ||
             (ws <= 0 && compareAndSetWaitStatus(pred, ws, Node.SIGNAL))) &&
            pred.thread != null) {
            Node next = node.next;
            if (next != null && next.waitStatus <= 0)
                compareAndSetNext(pred, predNext, next);
        } else {
            // 前驱结点为head那么将node结点解锁
            unparkSuccessor(node);
        }

        node.next = node; // help GC
    }
}
```



![](C:\Users\Steven\Desktop\CS-Note\java并发\pic\acquire.jpg)



**释放**

```java
public final boolean release(int arg) {
    if (tryRelease(arg)) {
        Node h = head;
        // head不为空且head状态不为0则唤醒后继结点
        if (h != null && h.waitStatus != 0)
            unparkSuccessor(h);
        return true;
    }
    return false;
}
private void unparkSuccessor(Node node) {
    // 如果等待状态小于0则尝试置为0
    int ws = node.waitStatus;
    if (ws < 0)
        compareAndSetWaitStatus(node, ws, 0);

    // 找到node有效的后继结点唤醒
    Node s = node.next;
    // 后继结点为null或者状态为CANCELLED则从tail向前遍历找到后继结点
    if (s == null || s.waitStatus > 0) {
        s = null;
        for (Node t = tail; t != null && t != node; t = t.prev)
            if (t.waitStatus <= 0)
                s = t;
    }
    // 唤醒后继节点
    if (s != null)
        LockSupport.unpark(s.thread);
}
```



![](C:\Users\Steven\Desktop\CS-Note\java并发\pic\release.jpg)



#### 共享式同步状态获取与释放

**获取**

```java
// 先尝试获取共享锁，失败则进入同步队列
public final void acquireShared(int arg) {
    if (tryAcquireShared(arg) < 0)
        doAcquireShared(arg);
}
private void doAcquireShared(int arg) {
    // 将线程包装成SHARED状态插入等待队列
    final Node node = addWaiter(Node.SHARED);
    boolean failed = true;
    try {
        boolean interrupted = false;
        // 自旋获取锁
        for (;;) {
            // 获取node的前驱结点
            final Node p = node.predecessor();
            // 如果前驱结点head结点即持有锁的结点
            if (p == head) {
                // 那么再次尝试获取共享锁
                int r = tryAcquireShared(arg);
                if (r >= 0) {
                    // 获取成功则
                    setHeadAndPropagate(node, r);
                    p.next = null; // help GC
                    // 与独占模式不同的是，打断线程逻辑放到了这里
                    if (interrupted)
                        selfInterrupt();
                    failed = false;
                    return;
                }
            }
            if (shouldParkAfterFailedAcquire(p, node) &&
                parkAndCheckInterrupt())
                interrupted = true;
        }
    } finally {
        if (failed)
            cancelAcquire(node);
    }
}

private void setHeadAndPropagate(Node node, int propagate) {
    Node h = head; // Record old head for check below
    setHead(node);
    // 如果成功获取到读锁或者头结点为空或者头结点且（结点的后继结点为空或者后继结点为共享模式）
    // 那么使用doReleaseShared方法在唤醒后继结点
    if (propagate > 0 || h == null || h.waitStatus < 0 ||
        (h = head) == null || h.waitStatus < 0) {
        Node s = node.next;
        if (s == null || s.isShared())
            doReleaseShared();
    }
}
private void setHead(Node node) {
    head = node;
    node.thread = null;
    node.prev = null;
}
```







**释放**

```java
public final boolean releaseShared(int arg) {
    if (tryReleaseShared(arg)) {
        doReleaseShared();
        return true;
    }
    return false;
}
private void doReleaseShared() {
    // 自旋
    for (;;) {
        Node h = head;
        // head不为空且存在后继结点
        if (h != null && h != tail) {
            int ws = h.waitStatus;
            // head结点状态为SIGNAL
            if (ws == Node.SIGNAL) {
                // 使用CAS操作将head结点状态变成0，失败则重试
                if (!compareAndSetWaitStatus(h, Node.SIGNAL, 0))
                    continue;            // loop to recheck cases
                // 成功则唤醒后继结点
                unparkSuccessor(h);
            }
            // 等待状态为0且使用CAS操作将head结点状态改为PROPAGATE状态失败，则重试
            else if (ws == 0 &&
                     !compareAndSetWaitStatus(h, 0, Node.PROPAGATE))
                continue;                // loop on failed CAS
        }
        // unparkSuccessor执行完后如果head结点没有变化则退出
        if (h == head)                   // loop if head changed
            break;
    }
}
```








#### 独占式超时同步状态获取与释放

**获取**

```java
public final boolean tryAcquireNanos(int arg, long nanosTimeout)
    throws InterruptedException {
    if (Thread.interrupted())
        throw new InterruptedException();
    return tryAcquire(arg) ||
        doAcquireNanos(arg, nanosTimeout);
}

private boolean doAcquireSharedNanos(int arg, long nanosTimeout)
    throws InterruptedException {
    if (nanosTimeout <= 0L)
        return false;
    final long deadline = System.nanoTime() + nanosTimeout;
    final Node node = addWaiter(Node.SHARED);
    boolean failed = true;
    try {
        for (;;) {
            final Node p = node.predecessor();
            if (p == head) {
                int r = tryAcquireShared(arg);
                if (r >= 0) {
                    setHeadAndPropagate(node, r);
                    p.next = null; // help GC
                    failed = false;
                    return true;
                }
            }
            nanosTimeout = deadline - System.nanoTime();
            if (nanosTimeout <= 0L)
                return false;
            if (shouldParkAfterFailedAcquire(p, node) &&
                nanosTimeout > spinForTimeoutThreshold)
                LockSupport.parkNanos(this, nanosTimeout);
            if (Thread.interrupted())
                throw new InterruptedException();
        }
    } finally {
        if (failed)
            cancelAcquire(node);
    }
}
```



**释放**

```java

```



#### 应用

![](C:\Users\Steven\Desktop\CS-Note\java并发\pic\主要用到AQS的并发工具类.png)









### ReentrantLock

![](C:\Users\Steven\Desktop\CS-Note\java并发\pic\Reentrantlock类图.png)



#### 非公平锁原理



**加锁源码**

```java
// 构造函数默认非公平锁
public ReentrantLock() {
    sync = new NonfairSync();
}

// NonfairSync的方法
final void lock() {
    // 使用CAS来尝试获取锁，1表示锁已被获得
    if (compareAndSetState(0, 1))
        // 成功则将独占线程设置为当前线程
        setExclusiveOwnerThread(Thread.currentThread());
    else
        // 获取失败则使用acquire方法
        acquire(1);
}

public final void acquire(int arg) {
    if (
        // 使用非公平锁的方式去尝试获得锁，失败后才让该线程入队AQS同步队列
        !tryAcquire(arg) &&
        acquireQueued(addWaiter(Node.EXCLUSIVE), arg))
        selfInterrupt();
}

protected final boolean tryAcquire(int acquires) {
    return nonfairTryAcquire(acquires);
}

final boolean nonfairTryAcquire(int acquires) {
    final Thread current = Thread.currentThread();
    // 获取当前的state，c也代表锁重入的次数
    int c = getState();
    // 0表示锁被释放
    if (c == 0) {
        // 当前线程尝试获取锁
        if (compareAndSetState(0, acquires)) {
            // 设置独占线程
            setExclusiveOwnerThread(current);
            // 忽略了AQS同步队列，体现了非公平锁
            return true;
        }
    }
    // 锁被当前线程持有
    else if (current == getExclusiveOwnerThread()) {
        // 重入数+1
        int nextc = c + acquires;
        if (nextc < 0) // overflow
            throw new Error("Maximum lock count exceeded");
        setState(nextc);
        return true;
    }
    return false;
}
```



**解锁源码**

```java
public void unlock() {
    // 锁重入数-1
    sync.release(1);
}
public final boolean release(int arg) {
    // 只有锁被释放、AQS不为空且队头的状态为SIGNAL才需要unpark后继结点
    if (tryRelease(arg)) {
        Node h = head;
        if (h != null && h.waitStatus != 0)
            unparkSuccessor(h);
        return true;
    }
    return false;
}
protected final boolean tryRelease(int releases) {
    // 重入数--
    int c = getState() - releases;
    // 当前线程不是持有这把锁的主人则抛出异常
    if (Thread.currentThread() != getExclusiveOwnerThread())
        throw new IllegalMonitorStateException();
    boolean free = false;
    // 重入数为0表示锁被释放，将独占线程设为null
    if (c == 0) {
        free = true;
        setExclusiveOwnerThread(null);
    }
    // 设置为重入数
    setState(c);
    return free;
}
```







#### 不可打断

即使当前线程被打断，也会留在AQS队列当中，直到获取到锁后才得知自己被打断

```java

public final void acquire(int arg) {
    // 进入if则当前线程中断
    if (!tryAcquire(arg) &&
        acquireQueued(addWaiter(Node.EXCLUSIVE), arg))
        selfInterrupt();
}

final boolean acquireQueued(final Node node, int arg) {
    boolean failed = true;
    try {
        // 默认没有被打断
        boolean interrupted = false;
        for (;;) {
            final Node p = node.predecessor();
            // 当前获取到锁才能返回
            if (p == head && tryAcquire(arg)) {
                setHead(node);
                p.next = null; // help GC
                failed = false;
                // 返回当前线程是否被中断
                return interrupted;
            }
            if (
                // 获取锁失败判断是否应该park
                shouldParkAfterFailedAcquire(p, node) &&
                // park操作&判断当前线程是否被打断
                parkAndCheckInterrupt())
                interrupted = true;
        }
    } finally {
        if (failed)
            cancelAcquire(node);
    }
}
private final boolean parkAndCheckInterrupt() {
    LockSupport.park(this);
    // 判断当前线程是否被打断，且清除中断标记
    return Thread.interrupted();
}

```





#### 可打断

```java
public final void acquireInterruptibly(int arg)
    throws InterruptedException {
    // 当前线程被中断直接抛出异常
    if (Thread.interrupted())
        throw new InterruptedException();
    if (!tryAcquire(arg))
        doAcquireInterruptibly(arg);
}
private void doAcquireInterruptibly(int arg)
    throws InterruptedException {
    final Node node = addWaiter(Node.EXCLUSIVE);
    boolean failed = true;
    try {
        for (;;) {
            final Node p = node.predecessor();
            if (p == head && tryAcquire(arg)) {
                setHead(node);
                p.next = null; // help GC
                failed = false;
                return;
            }
            // 当前线程被中断直接抛出异常 
            if (shouldParkAfterFailedAcquire(p, node) &&
                parkAndCheckInterrupt())
                throw new InterruptedException();
        }
    } finally {
        if (failed)
            cancelAcquire(node);
    }
}
```







#### 公平锁实现原理

**获取锁**

```java
final void lock() {
    acquire(1);
}
public final void acquire(int arg) {
    if (!tryAcquire(arg) &&
        acquireQueued(addWaiter(Node.EXCLUSIVE), arg))
        selfInterrupt();
}
// FairSync类的tryAcquire实现
protected final boolean tryAcquire(int acquires) {
    final Thread current = Thread.currentThread();
    int c = getState();
    // 有机会获得锁
    if (c == 0) {
        if (
            // 同步队列没有前驱结点才去竞争
            !hasQueuedPredecessors() &&
            compareAndSetState(0, acquires)) {
            setExclusiveOwnerThread(current);
            // 获取到了锁
            return true;
        }
    }
    else if (current == getExclusiveOwnerThread()) {
        int nextc = c + acquires;
        if (nextc < 0)
            throw new Error("Maximum lock count exceeded");
        setState(nextc);
        return true;
    }
    return false;
}

public final boolean hasQueuedPredecessors() {
    // The correctness of this depends on head being initialized
    // before tail and on head.next being accurate if the current
    // thread is first in queue.
    Node t = tail; // Read fields in reverse initialization order
    Node h = head;
    Node s;
    return h != t &&
        ((s = h.next) == null || s.thread != Thread.currentThread());
}
```



**释放锁**

```java
// 与非公平锁释放锁流程一致
public void unlock() {
    sync.release(1);
}
public final boolean release(int arg) {
    if (tryRelease(arg)) {
        Node h = head;
        if (h != null && h.waitStatus != 0)
            unparkSuccessor(h);
        return true;
    }
    return false;
}
protected final boolean tryRelease(int releases) {
    int c = getState() - releases;
    if (Thread.currentThread() != getExclusiveOwnerThread())
        throw new IllegalMonitorStateException();
    boolean free = false;
    if (c == 0) {
        free = true;
        setExclusiveOwnerThread(null);
    }
    setState(c);
    return free;
}
```



#### 条件变量实现原理

一个条件变量对应一个等待队列

**awit**

```java
final ConditionObject newCondition() {
    return new ConditionObject();
}
public final void await() throws InterruptedException {
    // 中断则抛出异常
    if (Thread.interrupted())
        throw new InterruptedException();
    // 创建等待队列结点
    Node node = addConditionWaiter();
    int savedState = fullyRelease(node);
    int interruptMode = 0;
    // 进入等待队列
    while (!isOnSyncQueue(node)) {
        LockSupport.park(this);
        if ((interruptMode = checkInterruptWhileWaiting(node)) != 0)
            break;
    }
    // 退出等待队列，尝试获取锁，加入AQS同步队列
    if (acquireQueued(node, savedState) && interruptMode != THROW_IE)
        interruptMode = REINTERRUPT;
    if (node.nextWaiter != null) // clean up if cancelled
        unlinkCancelledWaiters();
    if (interruptMode != 0)
        reportInterruptAfterWait(interruptMode);
}
// 由于await操作已经获取到锁，因并不需要CAS操作
private Node addConditionWaiter() {
    Node t = lastWaiter;
    // If lastWaiter is cancelled, clean out.
    if (t != null && t.waitStatus != Node.CONDITION) {
        unlinkCancelledWaiters();
        t = lastWaiter;
    }
    Node node = new Node(Thread.currentThread(), Node.CONDITION);
    if (t == null)
        firstWaiter = node;
    else
        t.nextWaiter = node;
    lastWaiter = node;
    return node;
}
// 调用了await那么该线程的结点一定是同步队列的头结点，将Node结点添加到等待队列队尾后，需要释放锁
final int fullyRelease(Node node) {
    boolean failed = true;
    try {
        int savedState = getState();
        if (release(savedState)) {
            failed = false;
            return savedState;
        } else {
            throw new IllegalMonitorStateException();
        }
    } finally {
        if (failed)
            node.waitStatus = Node.CANCELLED;
    }
}
// 判断结点是否在同步队列当中
final boolean isOnSyncQueue(Node node) {
    // 结点状态为CONDITION或者前驱结点为null则一定不在同步队列
    if (node.waitStatus == Node.CONDITION || node.prev == null)
        return false;
    // 如果有后继结点则一定在同步队列中
    if (node.next != null) // If has successor, it must be on queue
        return true;

    return findNodeFromTail(node);
}
// 从后向前遍历同步队列，判断node是否在同步队列
private boolean findNodeFromTail(Node node) {
    Node t = tail;
    for (;;) {
        if (t == node)
            return true;
        if (t == null)
            return false;
        t = t.prev;
    }
}
// 从条件变量移除所有ws不为CONDITION的结点
private void unlinkCancelledWaiters() {
    Node t = firstWaiter;
    Node trail = null;
    while (t != null) {
        Node next = t.nextWaiter;
        if (t.waitStatus != Node.CONDITION) {
            t.nextWaiter = null;
            if (trail == null)
                firstWaiter = next;
            else
                trail.nextWaiter = next;
            if (next == null)
                lastWaiter = trail;
        }
        else
            trail = t;
        t = next;
    }
}
```



**signal**

```java
public final void signal() {
    // 检查当前线程是否为当前锁的线程，不是抛出异常
    if (!isHeldExclusively())
        throw new IllegalMonitorStateException();
    // 唤醒等待队列第一个结点
    Node first = firstWaiter;
    if (first != null)
        doSignal(first);
}
protected final boolean isHeldExclusively() {
    return getExclusiveOwnerThread() == Thread.currentThread();
}
private void doSignal(Node first) {
    do {
        if ( (firstWaiter = first.nextWaiter) == null)
            lastWaiter = null;
        first.nextWaiter = null;
    } while (
        // 直到将结点成功移动到同步队列
        !transferForSignal(first) &&
             (first = firstWaiter) != null);
}
// 将结点从等待队列移动到同步队列
final boolean transferForSignal(Node node) {
    // 失败说明当前节点已被取消
    if (!compareAndSetWaitStatus(node, Node.CONDITION, 0))
        return false;

    // 将结点插入同步队列队尾
    Node p = enq(node);
    int ws = p.waitStatus;
    // 前驱结点ws为CANCELLED或者将前驱结点状态修改为SIGNAL失败则直接唤醒node结点
    if (ws > 0 || !compareAndSetWaitStatus(p, ws, Node.SIGNAL))
        LockSupport.unpark(node.thread);
    return true;
}
```



**awaitNanos（时限版本的await）**

```java
public final long awaitNanos(long nanosTimeout)
    throws InterruptedException {
    if (Thread.interrupted())
        throw new InterruptedException();
    Node node = addConditionWaiter();
    int savedState = fullyRelease(node);
    final long deadline = System.nanoTime() + nanosTimeout;
    int interruptMode = 0;
    // 没有到同步队列前，先阻塞指定时间
    while (!isOnSyncQueue(node)) {
        // 超时则
        if (nanosTimeout <= 0L) {
            transferAfterCancelledWait(node);
            break;
        }
        // 使用了parkNaos
        if (nanosTimeout >= spinForTimeoutThreshold)
            LockSupport.parkNanos(this, nanosTimeout);
        // 检查当前线程是否被中断过，如果被打断则退出等待队列
        if ((interruptMode = checkInterruptWhileWaiting(node)) != 0)
            break;
        nanosTimeout = deadline - System.nanoTime();
    }
    // 退出等待队列
    if (acquireQueued(node, savedState) && interruptMode != THROW_IE)
        interruptMode = REINTERRUPT;
    if (node.nextWaiter != null)
        unlinkCancelledWaiters();
    if (interruptMode != 0)
        reportInterruptAfterWait(interruptMode);
    return deadline - System.nanoTime();
}
```



#### ReentrantLock和synchronized





### ReentrantReadWriteLock

读写锁内部类有SynC类（实现了AQS），ReadLock、WriteLock（实现了Lock接口）



#### 写锁上锁

```java
public void lock() {
    sync.acquire(1);
}
public final void acquire(int arg) {
    if (!tryAcquire(arg) &&
        acquireQueued(addWaiter(Node.EXCLUSIVE), arg))
        selfInterrupt();
}
protected final boolean tryAcquire(int acquires) {
    Thread current = Thread.currentThread();
    int c = getState();
    int w = exclusiveCount(c);
    // 读或者写次数不为0
    if (c != 0) {
        // 写锁获取次数为0而获取锁次数不为0说明一定存在读锁或者当前线程不持有锁，则获取失败
        if (w == 0 || current != getExclusiveOwnerThread())
            return false;
        // 溢出
        if (w + exclusiveCount(acquires) > MAX_COUNT)
            throw new Error("Maximum lock count exceeded");
        // 重入数+1
        setState(c + acquires);
        return true;
    }

    // 如果写者需要等待或者CAS修改失败则获取失败
    // 公平锁：同步队列存在结点
    // 非公平：无论是否存在结点都可以尝试获取
    if (writerShouldBlock() ||
        !compareAndSetState(c, c + acquires))
        return false;
    // 当前线程独占该锁
    setExclusiveOwnerThread(current);
    return true;
}
static final int SHARED_SHIFT   = 16;
static final int EXCLUSIVE_MASK = (1 << SHARED_SHIFT) - 1;
// 低16位为写锁获取次数
static int exclusiveCount(int c) { return c & EXCLUSIVE_MASK; }

// 非公平
final boolean writerShouldBlock() {
    return false; // writers can always barge
}

// 公平
final boolean writerShouldBlock() {
    return hasQueuedPredecessors();
}
```







#### 写锁释放

```java
// AQS的方法
public final boolean release(int arg) {
    if (tryRelease(arg)) {
        Node h = head;
        if (h != null && h.waitStatus != 0)
            unparkSuccessor(h);
        return true;
    }
    return false;
}
protected final boolean tryRelease(int releases) {
    // 线程没有持有锁，抛出异常
    if (!isHeldExclusively())
        throw new IllegalMonitorStateException();
	// 同步状态减去写状态
    int nextc = getState() - releases;
	// 当前写状态是否为0，为0则释放写锁
    boolean free = exclusiveCount(nextc) == 0;
    if (free)
        setExclusiveOwnerThread(null);
	//3. 不为0则更新同步状态
    setState(nextc);
    return free;
}
```



#### 读锁上锁

```java
public final void acquireShared(int arg) {
    if (tryAcquireShared(arg) < 0)
        doAcquireShared(arg);
}
protected final int tryAcquireShared(int unused) {
    // 如果写锁被其他线程持有则失败
    Thread current = Thread.currentThread();
    int c = getState();
    if (exclusiveCount(c) != 0 &&
        getExclusiveOwnerThread() != current)
        return -1;
    // 
    int r = sharedCount(c);
    // 读者不应该阻塞，且读入数小于最大值且读锁次数加一的CAS操作成功
    if (!readerShouldBlock() &&
        r < MAX_COUNT &&
        compareAndSetState(c, c + SHARED_UNIT)) {
        if (r == 0) {
            // 当前线程第一次获取读锁，那么标记读者线程为当前线程，读取数设置为1
            firstReader = current;
            firstReaderHoldCount = 1;
        } else if (firstReader == current) {
            // 读者线程为当前线程，读取次数+1
            firstReaderHoldCount++;
        } else {
            // 读者线程不为当前线程
            HoldCounter rh = cachedHoldCounter;
            // 将该线程持有锁的次数记录在线程本地变量中，方便获取线程持有锁次数的信息
            if (rh == null || rh.tid != getThreadId(current))
                cachedHoldCounter = rh = readHolds.get();
            else if (rh.count == 0)
                readHolds.set(rh);
            rh.count++;
        }
        // 读者成功获取
        return 1;
    }
    // CAS操作失败或者读取次数已满自旋尝试
    return fullTryAcquireShared(current);
}
// 高16位为读锁线程的占有数
static int sharedCount(int c)    { return c >>> SHARED_SHIFT; }

// 公平锁，同步队列不为空则为true
final boolean readerShouldBlock() {
    return hasQueuedPredecessors();
}
// 非公平锁
final boolean readerShouldBlock() {
    return apparentlyFirstQueuedIsExclusive();
}
// 为了避免写者的饥饿现象，应该检查同步队列即将获取锁的结点是否为写者
// 头结点不为空且后继结点也不为空且后继节点不为share模式则读者应该等待
final boolean apparentlyFirstQueuedIsExclusive() {
    Node h, s;
    return (h = head) != null &&
        (s = h.next)  != null &&
        !s.isShared()         &&
        s.thread != null;
}


final int fullTryAcquireShared(Thread current) {
    HoldCounter rh = null;
    for (;;) {
        int c = getState();
        // 如果有写锁且写锁的占有者不是当前线程，这失败
        if (exclusiveCount(c) != 0) {
            if (getExclusiveOwnerThread() != current)
                return -1;
            // else we hold the exclusive lock; blocking here
            // would cause deadlock.
        } else if (readerShouldBlock()) {
            // Make sure we're not acquiring read lock reentrantly
            if (firstReader == current) {
                // assert firstReaderHoldCount > 0;
            } else {
                // 当前线程不是第一个持有读锁
                if (rh == null) {
                    rh = cachedHoldCounter;
                    if (rh == null || rh.tid != getThreadId(current)) {
                        rh = readHolds.get();
                        if (rh.count == 0)
                            readHolds.remove();
                    }
                }
                if (rh.count == 0)
                    return -1;
            }
        }
        if (sharedCount(c) == MAX_COUNT)
            throw new Error("Maximum lock count exceeded");
        if (compareAndSetState(c, c + SHARED_UNIT)) {
            if (sharedCount(c) == 0) {
                firstReader = current;
                firstReaderHoldCount = 1;
            } else if (firstReader == current) {
                firstReaderHoldCount++;
            } else {
                if (rh == null)
                    rh = cachedHoldCounter;
                if (rh == null || rh.tid != getThreadId(current))
                    rh = readHolds.get();
                else if (rh.count == 0)
                    readHolds.set(rh);
                rh.count++;
                cachedHoldCounter = rh; // cache for release
            }
            return 1;
        }
    }
}
```







#### 读锁释放

```java
public final boolean releaseShared(int arg) {
    if (tryReleaseShared(arg)) {
        doReleaseShared();
        return true;
    }
    return false;
}
protected final boolean tryReleaseShared(int unused) {
    Thread current = Thread.currentThread();
    // 第一个读者为当前线程
    if (firstReader == current) {
        // assert firstReaderHoldCount > 0;
        // 重入数为0
        if (firstReaderHoldCount == 1)
            firstReader = null;
        // 重入数--
        else
            firstReaderHoldCount--;
    } else {
        // 取出当前线程本地变量
        HoldCounter rh = cachedHoldCounter;
        if (rh == null || rh.tid != getThreadId(current))
            rh = readHolds.get();
        int count = rh.count;
        if (count <= 1) {
            readHolds.remove();
            if (count <= 0)
                throw unmatchedUnlockException();
        }
        --rh.count;
    }
    // 自旋修改读锁重入数--
    for (;;) {
        int c = getState();
        int nextc = c - SHARED_UNIT;
        if (compareAndSetState(c, nextc))
            return nextc == 0;
    }
}
```





#### 锁降级

* 重入时，锁不支持升级，即持有读锁的情况下去获取写锁，会导致写锁的永久等待
* 重入时，支持锁降级，即持有写锁的情况下可以去获取读锁











### Semaphore

* 信号量，用来控制并发访问线程数量，保证多个线程能够合理使用资源

#### 加锁流程

```java
// 获取当前许可个数
public void acquire(int permits) throws InterruptedException {
    if (permits < 0) throw new IllegalArgumentException();
    sync.acquireSharedInterruptibly(permits);
}
public void acquireUninterruptibly(int permits) {
    if (permits < 0) throw new IllegalArgumentException();
    sync.acquireShared(permits);
}
public final void acquireShared(int arg) {
    if (tryAcquireShared(arg) < 0)
        doAcquireShared(arg);
}

// 非公平锁
protected int tryAcquireShared(int acquires) {
    return nonfairTryAcquireShared(acquires);
}

final int nonfairTryAcquireShared(int acquires) {
    for (;;) {
        int available = getState();
        int remaining = available - acquires;
        if (remaining < 0 ||
            compareAndSetState(available, remaining))
            return remaining;
    }
}


// 公平锁
protected int tryAcquireShared(int acquires) {
    for (;;) {
        if (hasQueuedPredecessors())
            return -1;
        int available = getState();
        int remaining = available - acquires;
        if (remaining < 0 ||
            compareAndSetState(available, remaining))
            return remaining;
    }
}
```





#### 解锁流程

```java
public void release() {
    sync.releaseShared(1);
}
public final boolean releaseShared(int arg) {
    if (tryReleaseShared(arg)) {
        doReleaseShared();
        return true;
    }
    return false;
}
protected final boolean tryReleaseShared(int releases) {
    for (;;) {
        int current = getState();
        int next = current + releases;
        if (next < current) // overflow
            throw new Error("Maximum permit count exceeded");
        if (compareAndSetState(current, next))
            return true;
    }
}
private void doReleaseShared() {
    for (;;) {
        Node h = head;
        if (h != null && h != tail) {
            int ws = h.waitStatus;
            if (ws == Node.SIGNAL) {
                if (!compareAndSetWaitStatus(h, Node.SIGNAL, 0))
                    continue;            // loop to recheck cases
                unparkSuccessor(h);
            }
            else if (ws == 0 &&
                     !compareAndSetWaitStatus(h, 0, Node.PROPAGATE))
                continue;                // loop on failed CAS
        }
        if (h == head)                   // loop if head changed
            break;
    }
}
```



















# 多线程设计模式



## 两阶段终止





## 保护性暂停



## 生产者消费者模式



## 固定运行顺序





## 交替输出



## 犹豫模式





## 工作线程

