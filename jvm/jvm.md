# JVM梳理

## 概述

### Java程序的执行

![](https://cdn2.howtodoinjava.com/wp-content/uploads/2018/05/Java-Execution-Flow.png)

1. 解释器将java文件编译成字节码class文件
2. class文件可以在任何平台或操作系统的Java虚拟机中执行
3. Java虚拟机将class文件翻译成机器码
4. 执行java程序



可以看出java虚拟机是作为java与不同程序系统之间的桥梁，使得java具有跨平台的特性，同时有了Java虚拟机，我们就不用手动进行垃圾回收，因此Java虚拟机是java的核心，有了java虚拟机，java才有以下两个重要特点

* 一次编写，到处运行
* 自动进行垃圾回收



### 辨析JVM、JRE、JDK

![](https://img2020.cnblogs.com/blog/2052073/202006/2052073-20200619132023121-255773537.png)



* JVM（Java Virtual Machine）：指java虚拟机
* JRE（Java Runtime Environment）：指java运行时环境，即java虚拟机+Java的基本类库
* JDK（Java Devlopment Kit）：指java开发工具包，包含了jre和其它java的工具类



## JVM运行时内存区域

![](C:\Users\Steven\Desktop\复盘\jvm\JVM运行时内存区域.png)



### 程序计数器

由于java多线程是采用线程切换每个线程轮流分配处理器（时间片）的方式，所以每次线程切换需要保留现场，因此Java虚拟机需要使用程序计数器来保存下一条字节码指令的地址。

#### 作用

* 用来存放下一条字节码指令的地址，如果当前线程执行的是一个Java方法那么程序计数器记录的是这个正在执行的虚拟机字节码指令的地址，如果执行的是本地方法，那么程序计数器值则为空。



#### 特点

* 线程私有
* 是所有JVM运行时内存区域唯一不会产生Out of Memory Error的区域（JVM规范）



### Java虚拟机栈

#### 作用

* 虚拟机栈描述了线程方法执行的内存模型，当方法开始执行时，会创建一个**栈帧**，栈帧存放了局部变量表、方法出口、动态链接、操作数栈等信息，方法的调用到结束，分别对应了栈帧压入虚拟机栈和弹出虚拟机栈



#### 特点

* 线程私有，且与线程周期时间相同

Java虚拟机规范中规定了虚拟机栈的两种异常状况

* OutOfMemoryError：虚拟机栈动态拓展时无法申请到足够的内存大小
* StackOverflowError：栈帧过多，线程请求栈的深度大于虚拟机允许的深度



### 本地方法栈

#### 作用

* 与虚拟机栈类似，虚拟机栈执行的是java方法，而本地方法栈用来执行本地方法



#### 特点

* 与虚拟机栈特点类似





### 堆

#### 作用

* 用来存放对象的实例和数组



#### 特点

* 所有线程共享
* 是垃圾回收的主要区域
* OutOfMemoryError：堆没有完成实例分配且堆无法再进行拓展



#### 划分

划分目的是为了更快更好的回收和分配内存，java堆主要划分为新生代（Eden空间、From Survivor To Survivor）和老年代





### 方法区

#### 作用

* 用来存放已被虚拟机加载的类型信息、常量、静态变量和编译器编译后的代码，在Java虚拟机规范中，方法区属于堆上的一个逻辑部分，为了和堆进行区分，方法区也叫做**非堆**

#### 方法区的实现

* Java虚拟机规范中并没有指定方法区的实现，因此方法区有不同的实现方式，其中永久代（Permanent Generation）和元空间（Meta-space）都是方法区的实现

##### 永久代

JDK8之前HotSpot方法区的实现采用永久代

* 很多人习惯上将方法区称为永久代，其实方法区与永久代并不等同，而是为了方法区像java堆内存管理一样，省去专门为方法区编写代码工作，引入永久代使得方法区像java堆一样进行分代回收，一句话就是永久代只是方法区的一种实现，jdk8已取消永久代的概念

为什么取消永久代？

* 首先方法区主要是存储类和方法的信息难以确定大小

* 字符串常量池中的字符串，而永久代有默认的大小(-XX: MaxPermSize的上限)，因此容易导致性能问题和内存溢出错误
* 其次合并Hotspot和JRockit时，JRockit并没有永久代，开发人员因此决定放弃永久代，而改用本地内存



永久代溢出：java.lang.OutOfMemoryError: PermGen space



##### 元空间

元空间与永久区的不同

* 元空间不在Java虚拟机里，而是使用本地内存，因此元空间默认大小只受本地内存大小影响

* 元空间溢出：java.lang.OutOfMemoryError: PermGen space





### 运行时常量池

位于方法区，用来存放编译期生成的各种字面量和符号引用



* 常量池：也叫做常量池表（Constant Pool Table），虚拟机根据这张表可以找到要执行的类名、方法名、参数类型和字面量等信息
* 运行时常量池，class文件中的常量池表被加载到运行时常量池中，同时将符号引用翻译成真实的内存地址



#### StringTable



##### 特性

* 常量池中的字符串仅仅是符号，第一次用到才变为对象
* 利用串池的机制（数据结构为hashtable实现），避免了重复创建对象
* 字符串拼接的原理是StringBuilder
* 字符串拼接的原理是编译期优化
* String中的intern方法，主动将串池中没有的字符串对象放入串池
  * 1.8将字符串对象尝试放入串池，如果有则不会放入，如果没有则放入串池，并返回串池中的字符串对象
  * 1.6将字符串对象尝试放入串池，如果有则不会放入，如果没有则放入串池，并拷贝一份新的字符串对象放入串池并返回



```java
// 串池["ab", "a", "b"]
String x = "ab";
String s = new String("a") + new String("b");

// 堆  new String("a")   new String("b") new String("ab")
String s2 = s.intern(); // 将这个字符串对象尝试放入串池，如果有则并不会放入，如果没有则放入串池， 会把串池中的对象返回

System.out.println( s2 == x);		// true
System.out.println( s == x );		// false
```



```java
// 1.8环境
// 串池["a", "b", "ab"]
String s = new String("a") + new String("b");

// 堆  new String("a")   new String("b") new String("ab")
String s2 = s.intern(); // 将这个字符串对象尝试放入串池，如果有则并不会放入，如果没有则放入串池， 会把串池中的对象返回
String x = "ab";
System.out.println( s2 == x);		// true
System.out.println( s == x );		// true
```

```java
// 1.6环境
// 串池["a", "b", "ab"]
String s = new String("a") + new String("b");

// 堆  new String("a")   new String("b") new String("ab")
String s2 = s.intern(); // 将这个字符串对象尝试放入串池，如果有则并不会放入，如果没有则放入串池， 会把串池中的对象返回
String x = "ab";
System.out.println( s2 == x);		// true
System.out.println( s == x );		// false
```



##### 位置

* 1.6中StringTable位于永久代(Permanent Generation)
* 1.8中StringTable位于堆中



##### 垃圾回收

* 常量池中没有引用的字面量会被回收



##### 性能调优

* 调整-XX:StringTableSize=桶的个数



#### 特点

* 所有线程共享
* OutOfMemoryError：方法区无法内存分配需求





### 直接内存

#### 定义

并不位于java运行时内存区域，jdk1.4加入的NIO类，是基于通道与缓冲区的I/O方式，它可以使用Native函数直接分配堆外内存，通过存储在一个DirectByteBuffer对象作为这个内存的引用进行操作，在一些场景能提高性能，避免了在java堆和Native堆中来回复制数据。

* 常用于NIO操作，用于数据缓冲区
* 分配回收成本较高，但读写性能好
* 不受JVM内存回收管理

#### 分配和回收

* 底层原理使用了Unuseful，其中方法setMemory为分配内存，freeMemory为释放内存
* DirectByteBuffer对象构造方法还设置了虚引用cleaner，当对象没有引用可以垃圾回收时，cleaner会调用clean方法来调用unsafe.freeMemory来释放直接内存



```java
// DirectByteBuffer构造方法
DirectByteBuffer(int cap) {                   // package-private
    super(-1, 0, cap, cap);
    boolean pa = VM.isDirectMemoryPageAligned();
    int ps = Bits.pageSize();
    long size = Math.max(1L, (long)cap + (pa ? ps : 0));
    Bits.reserveMemory(size, cap);

    long base = 0;
    try {
        base = unsafe.allocateMemory(size);
    } catch (OutOfMemoryError x) {
        Bits.unreserveMemory(size, cap);
        throw x;
    }
    unsafe.setMemory(base, size, (byte) 0);
    if (pa && (base % ps != 0)) {
        // Round up to page boundary
        address = base + ps - (base & (ps - 1));
    } else {
        address = base;
    }
    cleaner = Cleaner.create(this, new Deallocator(base, size, cap));
    att = null;
}
```













### 线程运行诊断

基本思路是定位和排查，找到有问题的代码

* top命令可以排查哪个进程对CPU占用率高
* ps H -eo pid,tid,%cpu | grep 进程的id（用ps命令进一步定位是进程中哪个线程引起的）
* jstack 进程id
  * 能根据线程id找到有问题的线程，进一步定位到问题代码

#### CPU占用率过高

```java
package t1;

/**
 * @description: demo03
 * @author: Steven
 * @time: 2020/9/14 9:53
 */
/**
 * 演示 cpu 占用过高
 */
public class demo03 {

    public static void main(String[] args) {
        new Thread(null, () -> {
            System.out.println("1...");
            while(true) {

            }
        }, "thread1").start();


        new Thread(null, () -> {
            System.out.println("2...");
            try {
                Thread.sleep(1000000L);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }, "thread2").start();

        new Thread(null, () -> {
            System.out.println("3...");
            try {
                Thread.sleep(1000000L);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }, "thread3").start();
    }
}
```

* 运行程序

  ![](C:\Users\Steven\Desktop\复盘\jvm\运行demo03.png)

* 查看cpu占用率

  ![](C:\Users\Steven\Desktop\复盘\jvm\cpu占用情况.png)

* 排查是进程中哪个线程引起的

  ![](C:\Users\Steven\Desktop\复盘\jvm\定位线程.png)

* 使用jstack来定位问题代码

将tid转化成十六进制0x253，找到jstack对应的nid（操作系统映射的tid），最后找到了问题代码第16行

![](C:\Users\Steven\Desktop\复盘\jvm\定位到了问题代码.png)



#### 程序迟迟没有结束

```java
package t1;

/**
 * @description: 演示死锁
 * @author: Steven
 * @time: 2020/9/14 9:13
 */
class A{};
class B{};
public class demo02 {
    static A a = new A();
    static B b = new B();


    public static void main(String[] args) throws InterruptedException {
        new Thread(()->{
            synchronized (a) {
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                synchronized (b) {
                    System.out.println("我获得了 a 和 b");
                }
            }
        }).start();
        Thread.sleep(1000);
        new Thread(()->{
            synchronized (b) {
                synchronized (a) {
                    System.out.println("我获得了 a 和 b");
                }
            }
        }).start();
    }
}
```



* 使用nohup java t1.demo02 &命令将该程序在Linux后台下执行

![](C:\Users\Steven\Desktop\复盘\jvm\程序久久不结束.png)

* 使用jstack 388命令定位问题代码

  ![](C:\Users\Steven\Desktop\复盘\jvm\死锁问题代码.png)



### 性能监控与故障处理工具

#### 细目表

| 名称      | 主要作用                                                     |
| --------- | ------------------------------------------------------------ |
| jps       | JVM Process Status Tool，显示HotSpot虚拟机内的所有进程       |
| jmap      | Memory Map for Java，生成虚拟机的内存转储快照                |
| jstack    | Stack Trace for Java，显示虚拟机的线程快照                   |
| jconsole  | Java Console，用来监控Java虚拟机的可视化工具                 |
| jvisualvm | Java visualVM，图形化工具，提供内存CPU分析、堆转储分析、内存泄漏检测 |



#### 常用命令

* jps
* jmap -heap [pid]
* jconsole
* jvisualvm：





### 相关参数

* -Xss256k，设置Java虚拟机栈的大小为256k
* -Xmx8m，设置jvm分配内存时最大为8m
* -Xms500m，设置jvm运行过程时总大小为500m
* -XX:MaxPermSize=10m，JDK1.6下设置永久代空间大小为10m
* -XX:MaxMetaspaceSize=8m，设置元空间大小为8m
* -XX:-UseGCOverheadLimit，关闭当GC花费了98%时间回收不到2%的内存则抛出异常的功能
* -XX:StringTableSize=桶的大小
*  -XX:+PrintStringTableStatistics，打印StringTable的统计信息
* -XX:+PrintGCDetails -verbose:gc，开启GC的详细信息
* -XX:+DisableExplicitGC，禁用显式垃圾回收（System.gc()）







## 垃圾回收

垃圾收集三问

* 哪些内存需要回收？

Java堆和方法区的内存分配和回收是动态的，只有在运行时才知道创建了哪些对象和创建了多少对象，因此内存回收主要针对Java堆和方法区

* 什么时候回收？

对象“死去”时才进行回收，因此回收的第一步是判断对象是否“死去”

* 如何回收？

采用垃圾回收算法完成对垃圾的回收





### 如何判断对象可以回收

判断对象是否存活主要有两种算法：引用计数法和可达性算法



#### 引用计数法

**做法**

维护一块内存地址来保存对象的引用次数，对象A每被引用一次，则该对象的引用次数加一，若该对象A的引用次数为0说明对象没有被任何对象引用，因此对象A可以被回收



**优点**

* 简单高效



**缺点**

* 若存在循环引用的对象则这些对象无法回收



#### 可达性算法

**做法**

基本思路是通过**GC Roots**对象为根结点根据引用关系，若对象与GC Roots对象之间直接或者间接引用则对象可达，以GC Roots为根对象根据引用关系向下搜索，搜索走过的路径称为引用链，若对象没有被任何引用链相连，则说明对象不可达。

哪些可以作为GC Roots对象？

* Java虚拟机中栈帧的本地变量表所引用的对象
* 方法区中类静态属性所引用的对象
* 方法区中常量所引用的对象，如StringTable的引用
* 被同步锁（synchronized）持有的对象
* JNI引用的对象
* Java虚拟机内部的引用，如Class对象、类加载器

除了上述作为固定的GC Roots对象集合外，根据用户所选的垃圾收集器和当前回收的内存区域的不用，会临时性地加入其它对象，共同构成GC Roots对象集合。

* 如分代收集时回收新生代，这时需要考虑老年代中的对象可能引用了新生代地对象，因此需要将老年代的一些对象到GC Roots集合





#### finalize方法

当对象不可达即将被回收时回调用finalize方法，让此对象处理它生前的事（可复活）

**对象复活的条件**

1. finalize方法被覆盖
2. finalize方法第一次被调用

若不满足上述两个条件则对象已死



**执行finalize方法的过程**

若对象第一次执行了finalize方法则该对象会被放入F-Queue的队列中，并且虚拟机会自动的创建一条优先级低的线程finalizer来执行finalize()方法，只要finalize方法重新与引用链上任何一个对象建立关系则该对象是可复活的。



### 引用类型

Java中引用的传统定义为一个引用对象存放着内存起始地址，这说明这个对象是这块内存、某个对象的引用



#### 强引用

* 只要有存在引用，就一定不会被回收
* 例：Object obj = new Object()

#### 软引用

* 有用但是非必须的对象，触发第二次垃圾回收（Full GC）时，软引用对象会被列入回收对象
* 通过SoftReference类来实现软引用
* 应用场景：网页缓存、图片缓存



```java
// 虚拟机参数：-Xmx20m -XX:+PrintGCDetails -verbose:gc
public static void main(String[] args) {
    List<SoftReference<byte[]>> list = new ArrayList<>();
    for (int i = 0; i < 5; i++) {
        SoftReference<byte[]> ref = new SoftReference<>(new byte[_4MB]);
        list.add(ref);
        for (SoftReference<byte[]> t : list) System.out.print(t.get() + " ");
        System.out.println(list.size());
    }
    System.out.println("循环结束:" + list.size());
    for (SoftReference<byte[]> ref : list) {
        System.out.println(ref.get());
    }
}
```



#### 弱引用

* 非必须对象，当触发第一次垃圾回收（Full GC）时，弱引用对象会被回收
* 通过WeakReference类来实现弱引用





#### 虚引用

* 引用关系最弱的类型，不对对象的生命周期产生影响，无法通过虚引用获得引用的实例对象，目的是为了在这个对象垃圾回收时收到一个系统通知
* 通过PhantomReference来实现虚引用，必须配合引用队列使用



### 回收算法

#### 标记清除

分为两个阶段标记和清除：标记所有存活的对象，标记完成后，再统一回收所有未被标记的对象

优点：简单

缺点：若每次需要回收的对象过多，执行效率会变慢，清除后会产生大量不连续的内存碎片，内存碎片过多可能导致分配较大的对象空间不足而再次引发垃圾回收



#### 标记复制

将可用内存分为大小相等的两块，每次只使用其中的一块，垃圾回收时，将存活的对象复制到另一块上去，然后再把使用过的内存空间一次清理掉。

优点：不必考虑内存碎片问题

缺点：内存空间浪费



**改进**

新生代对象的特点：朝升夕灭（新生代大部分对象存活率低，因此并不需要1：1分配内存空间）

**Appel式回收**

将新生代分为一块较大的Eden区和两个较小的Survivor，HotSpot虚拟机默认Eden和Survivor的大小比例为8：1，每次垃圾回收时，将Eden区和一块Survivor区仍然存活的对象复制到另一块Survivor区，然后直接清理掉Eden区和使用过的Survivor区空间

当Survivor区的大小不足以容纳所有存活的对象时，需要依赖于其他内存区域进行分配担保



#### 标记整理

一般使用与老年区，标记阶段同标记清除是一样的，但在整理阶段时，将所有存活的对象向内存空间一端移动。

缺点：移动对象需要Stop the world而且移动的对象若存在引用则需要修改引用关系，用户线程延时增加，时间效率低于标记清除

优点：移动对象吞吐量相对高





#### 分代垃圾回收

不同的对象有不同的生命周期，因此我们可以对不同生命周期的对象，采用不同的收集方式，提高回收的执行效率

新生代特点：生命周期短、存活率低、回收频繁

老年代：生命周期长、存活率高、回收不频繁

* 结论：在新生代中采用标记复制算法，老年代采用标记清除或者标记整理算法



#### 增量垃圾回收

一次性进行垃圾回收，会造成较长的“Stop the world”状态，将严重影响用户体验，采用增量垃圾回收的方式，每次让用户线程和垃圾回收线程交替执行，每次垃圾回收线程只回收一小片区域的空间，接着切换用户线程执行，直到垃圾回收完毕



#### 分区垃圾回收

将堆空间划分成若干个小区间，每个小区间独立使用，独立回收，G1回收器使用的是这种方式





### 补充

#### System.gc()方法

调用垃圾回收与Runtime.getRuntime.gc()，并不保证垃圾回收



#### 内存溢出和内存泄漏

**内存溢出（OOM）**：设置的堆空间过小，创建了大量大对象，并且长时间不能被垃圾收集器回收

**内存泄漏**：对象不被程序使用，但是GC又不能回收这些对象

**举例**

1. 单例模式的对象如果生命周期与应用程序的生命周期一样长，同时持有外部对象的应用，那么外部对象是不能被回收的

2. 一些提供close()的资源未被关闭，如数据库连接，socket连接，io等





#### 垃圾回收的并行与并发

**垃圾回收并行：**多条垃圾回收线程并行，用户线程暂停

**垃圾回收串行**：相较于并行概念，单线程执行

**垃圾回收并发：**垃圾回收线程与用户线程同时执行，垃圾回收线程在执行时不会影响用户程序的执行



#### STW

Stop the world发生在垃圾回收时，暂停应用进程。

如果没有Stop the world，而对象的引用关系会不断变化，不能保证一致性，GC会发生一些严重的问题



#### 并发的可达性分析







#### 根结点枚举

问题：虽然使用了可达性算法明确了GC ROOT对象进而能够找到所有可以进行垃圾回收的对象，但是若从所有GC ROOT对象遍历，查找过程中的可能会消耗大量的时间，而且根节点枚举的过程中会面临Stop the world的困扰

HotSpot的解决方案：使用一组称为OopMap数据结构（Ordinary Object pointer），一旦类加载动作完成时，HotSpot就会把对象内什么偏移量上是什么类型的数据计算出来，在即时编译过程中，会在特定的位置下记录栈和寄存器里哪些是引用。



#### 安全点与安全区域

**安全点**

程序执行时，并非所有地方都能GC，在HotSpot中我们维护了一个数据结构OopMap，若每时每刻都进行GC，显然为每一条指令都生成这样一个数据结构，那么GC的代价将会变得很高，因此只有在特定的位置下停顿下来进行GC，这个特定的位置称为安全点

安全点的选择原则：是否具有让程序能够长时间执行的特征，长时间执行最明显的特征就是指令复用例如方法调用、循环跳转、异常跳转

安全点还需要考虑GC时如何让所有的线程都跑到了最近的安全点，然后停顿下来

* 抢占式中断：发生GC时中断所有线程，当某线程还没到达安全时，就恢复线程，让线程跑到最近安全点
* 主动式中断：设置一个中断标志，各个线程线程不断主动轮询这个标志，若中断标志为真则线程到最近的安全点主动中断挂起



**安全区域**

由于用户线程和垃圾回收线程都是轮流切换和执行的，因此用户线程有可能处于阻塞或者睡眠状态，因此需要引入安全区域。

安全区域是安全点的拉伸，这个区域确保了某一段代码中的引用关系不变，在这段代码的任何一个点都能进行GC



#### 记忆集与卡表

记忆集（Remember Set）是为了解决分代垃圾回收和分区垃圾回收时对象跨代引用、跨区引用的情况，使用记忆集能避免扫描整个老年代的对象，提高垃圾回收的效率



卡表是记忆集的具体实现，可以根据记录粒度来选择不同的卡表

字长精度：精确记录一个及其字长，该字长含跨代指针

对象精度：精确记录一个对象，该对象字段含跨代指针

卡精度：精确记录一个内存区域，该内存区域含跨代指针



卡表每一个元素都对应一块内存区域，这些元素称为卡页，当卡页中含跨代指针时，称为脏元素，在垃圾回收时，只需将变脏的卡页一并加入GC Root中一并扫描即可





#### 写屏障





### 垃圾收集器

#### Serial收集器/Serial Old收集器

![](C:\Users\Steven\Desktop\复盘\jvm\serial.png)

Serial收集器用于新生代，采用复制算法

Serial Old收集器是针对老年代，采用的是标记-整理算法，JDK5之前与Scanvenge收集器配合，另外是作为CMS收集器发生失败后的后备预案



优势：简单高效，由于没有线程交互，进行垃圾收集时能获得最高的单线程收集效率

缺点：需要暂停所有的用户线程，造成用户的时延过大

Serial应用场景：适用于单cpu的客户端模式

Serial Old应用场景：适用于后台运算而不需要太多交互的场景



#### ParNew垃圾回收器

![](C:\Users\Steven\Desktop\复盘\jvm\ParNew.png)

ParNew是Serial收集器的多线程并行版本

应用场景：多CPU环境服务端与CMS收集器配合





#### Parallel Scavenge收集器/Parallel Old收集器

Parallel Scavenge是新生代的收集器，并行收集

* 与CMS等收集器的关注点不同的是，Parallel Scavernge收集器目标是达到一个可控制的吞吐量，因此也称为吞吐量优先收集器
* 与ParNew收集器的最大区别是Parallel收集器拥有自适应条件策略，即虚拟机会根据当前系统运行情况收集性能监控信息，动态调整这些参数以提供适合的最大停顿时间或者最大吞吐量



Parallel Old是Parallel Scavenge的老年代版本



Parallel应用场景：应用于多核的配置高的服务器端

Parallel Old应用场景：适用于后台运算而不需要太多的交互场景



#### CMS收集器

![](C:\Users\Steven\Desktop\复盘\jvm\CMS.png)

CMS回收器是以获取最短回收停顿时间为目标的收集器，CMS垃圾回收分为4个过程

初始标记：只标记与GC Roots能直接关联的对象，需要STW

并发标记：从GC Roots直接关联对象开始遍历整个图，过程耗时较长但是不需要停顿用户线程

重新标记：为了修正并发标记时，因用户线程继续运作而导致的标记变动的那一部分对象的标记记录，需要STW

并发清除：清理掉死亡的对象



缺点

* 对CPU的资源敏感：并发阶段会因为占用一部分线程而导致应用程序变慢，从而降低总吞吐量
* 无法处理浮动垃圾：浮动垃圾是指在标记结束后又产生了新的垃圾对象，这一部分垃圾只能在下一次垃圾收集时才能清掉它们。由于用户线程还在运行，所以我们需要预留一部分空间供并发收集的程序运作使用，若预留的空间不满足分配新对象的需要，就会触发并发失败，这是CMS垃圾回收会要启动后备方案，采用Serial Old，冻结用户线程，再次进行GC，这样停顿时间就会变长
* 会产生内存碎片：CMS是基于并发清除算法的，所以收集结束时会有大量空间碎片产生



应用场景：互联网应用或者基于浏览器B/S系统的服务端



#### G1收集器

G1收集器是基于分代垃圾回收和分区垃圾回收，首先将Java堆划分成若干个大小相等的Region，每个Region根据需要扮演不同的角色（Eden、Survivor、老年代、Humongous存储大对象），回收时是以Region为最小回收单位进行回收，G1收集器会跟踪各个Region里面的垃圾堆积价值大小，这里的回收价值是指回收所能获得的大小以及回收时间，后台会维护一个优先级列表，回收时，优先处理回收价值收益最大的那些Region。



问题

将Java堆划分成若干个Region后，Region里存在的跨Region对象如何解决？





如何建立可靠的停顿时间预测模型？





为什么需要设置Humongous区

对于堆中的大对象，默认直接分配到老年代，但是如果是短期存在的大对象，就会对垃圾回收产生负面影响。



G1收集器与CMS收集器相比有哪些优势？







应用：面向服务端应用

#### 相关参数

-XX :+UseSerialGC，新生代使用SerialGC收集器，老年代使用SerialOldGC收集器

-XX:+UseParNewGC，新生代使用并行版本的Serial收集器

-XX:+UseParallelGC，新生代采用Parallel Scavenge收集器与-XX:+UseParallelOldGC相互激活

-XX:+UseParallelOldGC，新生代采用ParallelOld收集器与-XX:+UseParallelGC相互激活

-XX:ParallelGCThreads设置新生代并行收集器的线程数

-XX:+UseAdaptiveSizePolicy，Parallel收集器激活动态调整

-XX:+ConcMarkSweepGC，老年代使用CMS收集器，同时触发新生代使用ParNewGC







![image-20201026101222181](C:\Users\Steven\Desktop\复盘\jvm\垃圾回收器组合.png)









## 虚拟机执行的子系统

### Class文件结构

一次编写、到处运行的基石是字节码，而Class文件是将java编译器将Java代码编译为存储字节码的Class文件，这样Class文件能够运行在不同硬件平台和操作系统上的Java虚拟机。



根据Java虚拟机规范的规定，Class文件格式采用一种类似于C语言结构体的伪结构来存储数据，这种伪结构有两种数据类型，无符号数和表。

* 无符号数属于基本数据类型之一，以u1、u2、u4、u8分别代表一个字节、两个字节、四个字节、八个字节的无符号数，用来描述数字、索引引用、数量值和UTF-8编码构成的字符串值

* 表由多个无符号数和其他表构成的复合数据结构类型，所有表的命名都习惯性以_info结尾

![](C:\Users\Steven\Desktop\复盘\jvm\Class文件结构.png)

#### 魔数

Class文件头4个字节被称为魔数，用来标识这个文件为Class文件，一个Class文件的魔数值为0XCAFABABE

#### 文件版本号

第5、6个字节为次版本号，第7、8个字节为主版本号



#### 常量池

常量池是Class文件的基石，它是Class文件的资源库，存放着与其他文件结构相关联的数据，主要存放两大类常量：字面量和符号引用。

常量池中常量数量不固定，因此需要常量池计数器，第0项常量需要空出来，若引用第0项常量，则表示“不引用任何常量池项目”。

字面量：文本字符串、声明为final的常量

符号引用

* 类和接口的全限定名

* 字段和方法的名称和描述符
* 方法句柄和方法类型
* 被模块导出或者开放的包

全类名：java.lang.String

全限定名：java/lang/String

简单名称：没有任何类型和参数修饰的方法或者字段名称

描述符：描述字段的数据类型、方法的参数列表（数量类型和顺序）和返回值

例

```java
void inc();
简单名称：inc
描述符：()V
int indexOf(char[]source, int sourceOffset, int sourceCount, char []target, int targetOffset, int targetCount, int fromIndex);
简单名称：indexOf
描述符：([CII[CIII)I
```



#### 访问标志

用于标识一些类或者接口层次的访问信息，包括Class是类还是接口，是否定义为public类型，是否定义为abstract类型，如果为类，是否被声明为final。



#### 类索引、父类索引、接口索引集合

类索引、夫类索引：确定这个类的全限定名和父类的全限定名

由于可以实现多接口，因此接口索引的前面是接口索引计数器，表示这个类的接口的数量，接口索引集合描述这个类实现的接口，这些被实现的接口将按接口的顺序从左到右排列在接口索引集合当中。





#### 字段表集合

字段表集合用来描述这个类或者接口的字段信息，包括字段的作用域，是实例变量还是类变量，是否可变、字段的数据类型、字段名称等。

```java
field_info {
    u2 access_flags;			// 字段访问标识位
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info attributes[attributes_count];
}
```

注

字段表不会列出从父类或者父接口中继承而来的字段

java语言中字段无法重载，不管修饰符相同与否，名称必须不同。而对于Class文件来说，只要两个字段的描述符不相同，那么字段重名为合法的。



#### 方法表集合

与字段表类似，仅在访问标志和属性表集合的可选项中有所区别。

```java
method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info attributes[attributes_count];
}
```

注

Java语言中，重载一个方法时，除了要与原方法具有相同的简单名称外，还要求必须拥有一个与原方法不同的特征签名，正因为方法返回类型不在特征签名中，因此无法靠方法的返回值进行重载。

java代码层面特征签名：指一个方法中各个参数在常量池的符号引用的集合

字节码层面特征签名：还包括了方法的返回值以及受查异常表。





#### 属性表集合

在Class文件中，字段表、方法表都可以携带自己的属性表，用来描述某些场景的专有信息，比如Code属性表存放方法中java经过编译后的字节码。

```java
attribute_info {
    u2 attribute_name_index;   //属性名索引
    u4 attribute_length;       //属性长度
    u1 info[attribute_length]; //属性的具体内容
}
```







