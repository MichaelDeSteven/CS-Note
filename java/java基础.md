# Java基础



## Java语言特点

* 简单易学
* 是一门面向对象语言（封装继承多态）
* 平台无关性（通过JVM实现）
* 可靠性
* 安全性
* 支持多线程编程
  * 支持网络编程
* 动态性，解释与运行并存







## 面向对象

面向对象的三大特性：封装、继承、多态



### 封装

利用抽象数据类型将数据和操作数据的方法封装在一起，使其成为一个独立的实体。数据被保护在抽象数据类型的内部，尽可能地隐藏内部细节，只保留一些接口使其与外部发生联系。用户无需对象内部细节

目的：减少耦合，提高了代码重用性



#### 访问修饰符

public：对所有类可见

protected：对同一包内所有类以及所有子类都可见

default：对同一包内所有类和子类可见

private：仅当前类

| 修饰符    | 当前类 | 同一包内 | 同一包内的继承类 | 不同包的继承类 | 其他包 |
| --------- | ------ | -------- | ---------------- | -------------- | ------ |
| public    | Y      | Y        | Y                | Y              | Y      |
| protected | Y      | Y        | Y                | Y              | N      |
| default   | Y      | Y        | Y                | N              | N      |
| private   | Y      | N        | N                | N              | N      |





#### 非访问修饰符

**static**

* 修饰方法
* 修饰字段
* 修饰内部类：静态内部类与非静态内部类的区别在于非静态内部类在编译完后会隐含地保存一个引用，这个引用用来指向外围类，因此静态内部类创建不依赖于外围类，同时静态内部类不能使用任何非static的方法或者字段
* 静态代码块：加载顺序为静态代码块—非静态代码块—构造方法

**final**

* 意思为不可改变的，不可改变的原因主要是设计和效率问题
* final可以用来修饰类、方法、字段，修饰的类不能被继承，修饰的方法不能被继承类重写，修饰的变量不能被修改
* 用来修饰对象引用时，对象引用恒定不变，都是对象自身是可被修改的
* 修饰类表示该类无法被继承
* 修饰方法可以把方法锁住，以防止任何继承类修改它的含义



**abstract**：用来创建抽象类和抽象方法



### 继承

面向对象中有父类以及子类的概念，即子类可以继承父类的一些属性和方法。继承实现了IS-A关系，例如Cat IS-A Animal，Cat类可以继承父类Animal的非private方法



### 多态

顾名思义：一个类的多种不同形态。

多态又分为编译时多态和运行时多态

* 编译时多态：通常指的是重载（Overload）
* 运行时多态：通常指的是重写（Overwrite），只有在程序运行期间，才确定对象引用的具体类型，从而调用相应的方法

运行时多态的三个条件

* 子类继承（extends）或者接口实现（implements）
* 重写
* 向上转型：父类引用子类的方法

方法重载发生在同一个类中，方法名相同，参数的个数、类型不同

方法重写发生在子类对父类允许访问的方法实现过程进行重新编写，返回值和形参都不能变（也可以发生在实现接口重写方法的时候）

目的：易于拓展新的子类或者功能，增加程序的灵活性



原理详见JVM#方法调用







### 接口类和抽象类

#### 抽象类

抽象类和抽象方法用abstract关键字进行声明，如果一个类中包含抽象方法，那么这个类必须声明为抽象类。

抽象类和普通类的最大区别是，抽象类不能被实例化，需要继承抽象类才能实例化其子类



#### 接口

接口是抽象类的延伸，它可以看作是一个完全的抽象类，也即不能有任何方法的实现



**JDK8**

* 支持声明default和静态方法





比较抽象类和接口

* 共同点：**均不能被实例化**，只有实现接口的所有方法或者实现了抽象方法的类才能被实例化
* 定义：abstract class定义抽象类、interface定义接口
* 继承：抽象类和接口都可用于实现面向对象中的运行时多态，增加程序的灵活性，接口是对Java多重继承的折中方案，Java中只存在一个父类，但是却可以实现多个接口
* 构造器：抽象类可以有构造器，接口不能有构造器
* 从语法上：Java 8之前接口内的方法不能有任何的实现，从Java 8开始使用关键字default能够拥有默认方法的实现，而抽象类内可以有普通方法和字段，
* 修饰符：接口成员的访问修饰默认且只有public，而抽象类无限制
* 设计层面：抽象类提供了一种IS-A的关系**是一种概念上的抽象，而接口则是对行为的抽象**



例如：对于Door的抽象概念，该 Door 具有执行两个动作 open 和 close，使用抽象类或者接口定义如下

```java
abstract class Door {
        abstract void open();
        abstract void close()；
}
interface Door {
    void open();
    void close();
}
```

无论使用抽象类或者接口，这样一点问题都没有

如果现在要求 Door 还要具有报警的功能，有以下简单的解决方案

```java
abstract class Door {
   abstract void open();
   abstract void close()；
   abstract void alarm();
}
interface Door {
    void open();
    void close();
    void alarm();
}
// 继承或实现
class AlarmDoor extends Door {
    void open() {... }
    void close() {... }
    void alarm() {... }
}

class AlarmDoor implements Door ｛
    void open() {... }
    void close() {... }
    void alarm() {... }
｝
```

违反了面向对象设计的核心原则ISP（接口分离原则：不应该强迫客户依赖于它们不用的方法）这样定义混淆了门的概念和报警器的概念，解决方案是将门固有的行为方法和警报器的行为方法分离出来。如果我们对于问题领域的理解是：AlarmDoor 在概念本质上是 Door，同时它有具有报警的功能。那么我们可以通过抽象类的方式来定义概念（AlarmDoor IS A Door），另外，通过接口的方式来定义行为

```java
abstract class Door {
    abstract void open();
    abstract void close()；
}
interface Alarm {
    void alarm();
}
class AlarmDoor extends Door implements Alarm {
    void open() {... }
    void close() {... }
    void alarm() {... }
}
```



## 基本数据类型

Java拥有两大类数据类型：基本数据类型和引用数据类型

### 介绍

大致分为整型、字符型、浮点型、布尔型

整型

1. byte，8位（-128-127）默认值为0
2. short，16位，默认值为0
3. int，32位，默认值为0
4. long，64位，默认值为0L

字符型

5. char，16位无符号整数，默认值为'\u0000'

浮点型

6. float，默认值为+0f
7. double，默认值为+0d

布尔型

8. boolean，尽管JVM定义了布尔型，但是只对它提供了有限的支持，JVM编译时，会将它转化为int（1表示true，0表示false），若boolean为数组，则会被JVM编译为byte数组，boolean只含两个值true、false，默认值为false，但是在《Java虚拟机规范》并没有给出明确的大小定义，所以boolean的大小要看虚拟机具体实现



### 缓存池

new Integer(123) 与 Integer.valueOf(123) 的区别在于：

*  new Integer(123) 每次都会新建一个对象； 
* Integer.valueOf(123) 会使用缓存池中的对象，多次调用会取得同一个对象的引用。

```java
public static Integer valueOf(int i) {
if (i >= IntegerCache.low && i <= IntegerCache.high)
return IntegerCache.cache[i + (-IntegerCache.low)];
return new Integer(i);
}
```



### 包装类

每个内置数据类型都有相应的包装类，基本数据类型转换为包装类称为自动装箱，反之为自动拆箱



## 引用数据类型

### Object

```java
public native int hashCode()
public boolean equals(Object obj)
protected native Object clone() throws CloneNotSupportedException
public String toString()
public final native Class<?> getClass()
protected void finalize() throws Throwable {}
public final native void notify()
public final native void notifyAll()
public final native void wait(long timeout) throws InterruptedException
public final void wait(long timeout, int nanos) throws InterruptedException
public final void wait() throws InterruptedException
```

**equals**

* 用来判断两个对象是否相等，默认实现是判断两个对象的内存地址是否相等，如果要判断内容则需要重写该方法
* Java语言规范要求equals方法具有下面的特点
* 自反性，即x.equals(x) == true
* 对称性，即x.equals(y) == true 那么就有y.equals(x) = true
* 传递性，即x.equals(y) == true，y.equals(z) == true 那么就有x.equals(z) == true
* 一致性，如果对象要比较的内容没有被修改，那么每次使用equals方法都应该返回相同的值



**hashCode**

* 返回对象的哈希值（内存中的地址）
* 一般要与equals一起重写



**toString**

* 默认打印实例的类名+无符号的十六进制的hashcode，子类都应该重写toString，方便查看对象的信息和调试

**clone**

* 创建并返回一个对象的拷贝，clone默认浅拷贝



**getClass**

* 获取Class对象



**finalize**

* 当决定回收该对象时，就会调用该方法，由于finalize并不保证对象的回收，可能导致性能、死锁、挂起问题，所以JDK9被废弃



**wait**

* 使当前线程等待，直到被唤醒，需要获取对象锁，否则会抛出illegalMonitorStateException异常



**notify**

* 唤醒一个在对象锁等待的线程，唤醒的策略有具体的虚拟机实现



**notifyAll**

* 唤醒所有在对象锁等待的线程







### String

JDK8中，String类由final修饰，字符串内容由final char数组维护 同时String类维护了一个字符串常量池

String、StringBuffer、StringBuilder位于java.lang包下



#### **常用方法**

```java
indexOf():返回指定字符的索引
charAt():返回指定索引处的字符
trim():去除字符串两端的空白
split():分割字符串，返回一个分割后的字符串数组
getBytes():返回一个byte类型的数组
length():返回字符串的长度
toLowerCase():将字符串转化为小写
toUpperCase():将字符串转化为大写
substring():截取字符串
equals():字符串比较
contains():检测字符串是否包含了指定字符串
intern()
```



#### 不可变性

```java
// String类被final修饰，则该类不可被继承
public final class String
    implements java.io.Serializable, Comparable<String>, CharSequence {
    /** The value is used for character storage. */
    // 值被final修饰，则该值不可被修改
    private final char value[];
    ...
}
```



1. 适合作为HashMap和HashSet的key。String的hash值经常被使用。不可变性特征可以使得hash值不可变，由于HashMap和HashSet的key一般都要求不可变，因此String可以适合当作key
2. 缓存。String Pool存储着字符串，字面量相同的字符串都会指向同一内存地址，在大量使用字符串情况下，可以节省内存，提高效率
3. 线程安全。String可以被多个线程所使用而不产生线程安全问题
4. 安全。账户密码一般用字符串表示，不可变使得内容不可修改，保证了安全



#### String、StringBuilder、StringBuffer

1. 可变性
   * String不可变
   * StringBuffer和StringBuilder可变
2. 线程安全
   * String和StringBuffer线程安全
   * StringBuilder不是线程安全



#### intern方法

JDK8中intern方法解释为：字符串常量池存储着字符串，当调用该方法时，会从常量池查找是否含有该字符串，若存在则直接返回该字符串的地址，否则会在字符串常量池添加一个字符串，并返回该字符串的引用地址。

详见：JVM



#### equals

```java
public boolean equals(Object anObject) {
    if (this == anObject) {
        //内存地址一致的话，为true
        return true;
    }
    //判断是不是String类
    if (anObject instanceof String) {
        String anotherString = (String)anObject;
        int n = value.length;
        //判断字符串长度是否相等，不等直接返回不等
        if (n == anotherString.value.length) {
            char v1[] = value;
            char v2[] = anotherString.value;
            int i = 0;
            //依次比较每个字符
            while (n-- != 0) {
                if (v1[i] != v2[i])
                    return false;
                i++;
            }
            return true;
        }
    }
    return false;
}
```



细节：比较字符串内容并不是一上来就进行了比较，而是先进行几个简单的判断，提升了效率

1. 比较内存地址是否相等
2. 比较传入的对象类型是否一致
3. 字符串长度是否相等
4. 一个个比较字符值



#### concat

```java
public String concat(String str) {
    int otherLen = str.length();
    if (otherLen == 0) {
        return this;
    }
    int len = value.length;
    char buf[] = Arrays.copyOf(value, len + otherLen);
    str.getChars(buf, len);
    return new String(buf, true);
}
```



创建一个新的字符数组，长度为已有字符串+待拼接字符串长度之和，再将两个字符串的值复制到新的字符数组中，最后返回一个新对象String



#### append



```java
public final class StringBuilder
    extends AbstractStringBuilder
    implements java.io.Serializable, CharSequence
{}


abstract class AbstractStringBuilder implements Appendable, CharSequence {
    // char数组
    char[] value;
    public AbstractStringBuilder append(String str) {
        if (str == null)
            return appendNull();
        int len = str.length();
        ensureCapacityInternal(count + len);
        str.getChars(0, len, value, count);
        count += len;
        return this;
    }
}
```



#### 字符串拼接

1. 使用+拼接字符串：原理是创建了一个StringBuilder对象之后使用append方法进行处理的
2. String使用concat方法
3. StringBuilder和StringBuffer的append方法





#### 新特性JDK9

char数组改为了byte数组，好处是节约内存空间和减少GC次数



## 内部类

### 介绍

将一个类的放到另一类的内部，就是内部类

### 原因



* 和接口配合解决了Java语言多重继承的问题
* 能与外围类通信，包括了访问private字段
* 对同一包内的类隐藏
* 内部类提供了闭包的功能（可调用对象），方便回调







## 泛型

泛型本质就是类型参数化，使用泛型能对类型进行泛化，泛型的好处是提高程序健壮性、增加代码可读性、提高效率



与C++的模板不同的是Java在使用泛化时，擦除类型的信息，在泛型的内部代码无法获得任何有关泛型参数类型的信息，例如List<String>在运行时仅用一个List来表示，这样做的原因是为了泛型实现的一种**折中**，为了确保能和Java 5之前的版本开发二进制类库进行兼容。即迁移兼容性，Java泛型不仅必须要支持向后兼容，还要保持之间的含义。



### 限定通配符

* ? extends T：继承某个类
* ？super T：自身或者父类



[10 道 Java 泛型面试题](https://cloud.tencent.com/developer/article/1033693)

https://mp.weixin.qq.com/s/XNYfLrnd7tYnTmuf1oyKQg



## 反射

### 概念

反射体现了Java语言的动态性，这也是和C++不同的地方，它为运行时的Java程序提供了获取自身的信息，从而能够访问或者操作类或者对象的内部属性或者方法，反射可以说是Java框架的灵魂，是因为它赋予了运行时能够分析类以及类中方法的能力。反射的优点是提高了代码的灵活性，为各个框架开箱即用提供了便利。缺点首先是反射可能会带来一定的性能损耗，同时反射具有一定的安全问题。比如它可以无视泛型参数的安全检查，它也可以访问私有的方法或者字段，破坏了面向对象的设计原则，增加了安全隐患。



### 使用方法

**获取Class对象的方式**

（1）使用Class的静态方法forName

```java
Class cClass = Class.forName("Reflection.Person");
```



（2）直接获取某个对象的Class

```java
Class cClass = Person.class;
System.out.println(cClass);
```



（3）调用某个对象的getClass方法

```java
Person person = new Person();
cClass = person.getClass();
```



（4）通过类加载器获取

```java
Class clazz = ClassLoader.getSystemClassLoader().loadClass("Reflection.Person");
```





**判断是否为类的实例**

一般地，判断某个实例是否属于某个类我们可以使用instanceof关键字来判断，也可以使用反射中Class对象的isInstance()来判断某个类的实例，它是一个native方法

```java
public native boolean isInstance(Object obj);
```



**创建实例**

```java
Class cClass = Person.class;
Constructor c = cClass.getConstructor(int.class, String.class); // 区分包装类
Object obj = c.newInstance(1, "zst");
```



**获取类的信息**

```java
// 获取所有构造器方法
Constructor[] constructor = cClass.getConstructors();
// 获取所有公有方法，包括了接口以及父类
Method[] methods = cClass.getMethods();
// 获取本类当中的公有方法
methods = cClass.getDeclaredMethods();
// 获取所有公有字段，包括了接口以及父类
Field[] fields = cClass.getFields();
// 获取当前类的公有字段
fields = cClass.getDeclaredFields();
// 如果想要获取或者修改私有方法或者字段可以使用setAccessible方法
```



**调用方法**

```java
Class clazz = Student.class;
Method method = clazz.getMethod("sayHi");
method.invoke(clazz.newInstance());
```





[Java Reflection: Why is it so slow?](https://stackoverflow.com/questions/1392351/java-reflection-why-is-it-so-slow)





### 应用场景



* JDBC：加载驱动
* Spring：xml配置文件读取
* 动态代理



## 动态代理

详见设计模式中的代理模式





## 异常

异常机制就是为了使得程序具备健壮性。能在调试，运行阶段都能提供有效的手段进行异常捕获，然后实施补救手段。





### 体系

Java异常的父类为Throwable，它主要有两个子类Error和Exception，两者之间的区别如下

* Error为Java处理不了错误，常见的Error有OOM，SOF
* Exception是Java可以处理的异常，Exception又分受检查异常和不受检查异常，Exption
  * 受检查异常时指如果没有catch`/`throw处理，就通过不了编译，比如运行时异常
  * 不受检查异常是指没有catch`/`throw，也能通过编译，该类常见的异常有类型转换错误、空指针、数组越界、算术错误



### try-with-resources

面对需要关闭的资源，try-with-resources优先于try-catch-finally，这样编写的代码更简单，更清晰

适用范围

* 任何实现 java.lang.AutoCloseable或者 java.io.Closeable 的对象



**例**

```java
//读取文本文件的内容
Scanner scanner = null;
try {
    scanner = new Scanner(new File("D://read.txt"));
    while (scanner.hasNext()) {
        System.out.println(scanner.nextLine());
    }
} catch (FileNotFoundException e) {
    e.printStackTrace();
} finally {
    if (scanner != null) {
        scanner.close();
    }
}

try (Scanner scanner = new Scanner(new File("test.txt"))) {
    while (scanner.hasNext()) {
        System.out.println(scanner.nextLine());
    }
} catch (FileNotFoundException fnfe) {
    fnfe.printStackTrace();
}
```





### throw&throws

* throw：用于捕获异常，需要配合try-catch语句
* throws：用于方法抛出异常，可以单独使用



## 注解

### 概念

* 注解是附加在Java代码的一些元信息，用于一些工具在编译或运行时进行解析和使用，起到了说明和配置的功能。注解不会影响代码的实际逻辑
* 比如@Override起到了标注重写方法的作用，同时如果父类不存在该方法，编译时会报错
* 注解还可以用来生成文档
* 实现了配置文件功能





### 元注解

表示注解的注解

![](C:\Users\Steven\Desktop\CS-Note\java\pic\annotation.jpg)



* @Override：检查是否为重写方法，如果发现其父类或者接口没有该方法，则编译报错
* @Deprecated：表示过时的方法
* @SuppressWarning：表示忽略注解中声明的警告
* @Retention：Retention有保留的意思，表示这个注释怎么保存，是只在代码中，还是编入的class文件中，或者是在运行时可以通过反射访问
* @Documented：标记这些注解是否包含在用户文档中
* @Target：表示目标的意思，使用枚举类ElementType表示注解的范围，可以是类、方法、参数
* @Inherited：标记这个注解是继承哪个注解类



```java
package java.lang.annotation;
public interface Annotation {

    boolean equals(Object obj);

    int hashCode();

    String toString();

    Class<? extends Annotation> annotationType();
}
```



```java
package java.lang.annotation;

public enum ElementType {
    TYPE,               /* 类、接口（包括注释类型）或枚举声明  */

    FIELD,              /* 字段声明（包括枚举常量）  */

    METHOD,             /* 方法声明  */

    PARAMETER,          /* 参数声明  */

    CONSTRUCTOR,        /* 构造方法声明  */

    LOCAL_VARIABLE,     /* 局部变量声明  */

    ANNOTATION_TYPE,    /* 注释类型声明  */

    PACKAGE             /* 包声明  */
}
```



```java
package java.lang.annotation;
public enum RetentionPolicy {
    SOURCE,            /* Annotation信息仅存在于编译器处理期间，编译器处理完之后就没有该Annotation信息了  */

    CLASS,             /* 编译器将Annotation存储于类对应的.class文件中。默认行为  */

    RUNTIME            /* 编译器将Annotation存储于class文件中，并且可由JVM读入 */
}
```





### 原理

* 本质是一个继承了Annotation的特殊接口，其具体实现类是Java运行时生成的动态代理类，通过反射获取注解时，返回的是Java运行时生成的动态代理对象$Proxy1。通过代理对象调用自定义注解的方法，最终调用AnnotationInvocationHandler的invoke方法，该方法会从memberValues这个Map中索引出对应的值。memberValues的来源是Java常量池







[Java 注解（Annotation）](https://www.runoob.com/w3cnote/java-annotation.html)

[Java注解全解析](https://www.jianshu.com/p/9471d6bcf4cf)





## SPI

### 概念

SPI全称Service Provider Interface服务提供接口，它允许开发者不用修改Java代码而去实现自己提供的服务，



### 源码分析

```java
public final class ServiceLoader<S>
    implements Iterable<S>
{

    private static final String PREFIX = "META-INF/services/";

    // The class or interface representing the service being loaded
    private final Class<S> service;

    // The class loader used to locate, load, and instantiate providers
    private final ClassLoader loader;

    // The access control context taken when the ServiceLoader is created
    private final AccessControlContext acc;

    // Cached providers, in instantiation order
    private LinkedHashMap<String,S> providers = new LinkedHashMap<>();

    // The current lazy-lookup iterator
    private LazyIterator lookupIterator;
    
    public void reload() {
        providers.clear();
        // 使用了懒加载+迭代器，服务会放入迭代器当中
        lookupIterator = new LazyIterator(service, loader);
    }
    
    // 该类使用了工厂方法设计模式，必须用load来创建对象
    private ServiceLoader(Class<S> svc, ClassLoader cl) {
        service = Objects.requireNonNull(svc, "Service interface cannot be null");
        loader = (cl == null) ? ClassLoader.getSystemClassLoader() : cl;
        acc = (System.getSecurityManager() != null) ? AccessController.getContext() : null;
        reload();
    }
    
    public static <S> ServiceLoader<S> load(Class<S> service,
                                            ClassLoader loader)
    {
        return new ServiceLoader<>(service, loader);
    }
    
    // 第一次加载会调用load方法，该方法默认使用线程的上下文类加载器
    public static <S> ServiceLoader<S> load(Class<S> service) {
        ClassLoader cl = Thread.currentThread().getContextClassLoader();
        return ServiceLoader.load(service, cl);
    }
    
    // 服务的真正加载
    public Iterator<S> iterator() {
        return new Iterator<S>() {

            Iterator<Map.Entry<String,S>> knownProviders
                = providers.entrySet().iterator();

            public boolean hasNext() {
                if (knownProviders.hasNext())
                    return true;
                return lookupIterator.hasNext();
            }

            public S next() {
                if (knownProviders.hasNext())
                    return knownProviders.next().getValue();
                return lookupIterator.next();
            }

            public void remove() {
                throw new UnsupportedOperationException();
            }

        };
    }
    
    // Private inner class implementing fully-lazy provider lookup
    private class LazyIterator implements Iterator<S>
    {

        Class<S> service;
        ClassLoader loader;
        Enumeration<URL> configs = null;
        // 当前service配置文件的内容迭代器
        // 即对services进行遍历，取出一个services配置文件，再对该文件按行解析，每行代表一个具体的service实现类，pending是某个services配置文件中service实现类的迭代器
        Iterator<String> pending = null;
        String nextName = null;

        private LazyIterator(Class<S> service, ClassLoader loader) {
            this.service = service;
            this.loader = loader;
        }

        private boolean hasNextService() {
            if (nextName != null) {
                return true;
            }
            // 首次迭代时，configs为空，尝试通过classloader获取名为：
            // "META-INF/services/[服务全限定名]"的所有配置文件
            if (configs == null) {
                try {
                    // 注意fullName的定义:"META-INF/services/[服务全限定名]"
                    String fullName = PREFIX + service.getName();
                    // 通过ClassLoader.getResources()获得资源URL集合
                    if (loader == null)
                        configs = ClassLoader.getSystemResources(fullName);
                    else
                        configs = loader.getResources(fullName);
                } catch (IOException x) {
                    fail(service, "Error locating configuration files", x);
                }
            }
            // 如果pending为空，或者pending已经迭代到迭代器末尾，则尝试解析下一个services配置文件
            while ((pending == null) || !pending.hasNext()) {
                if (!configs.hasMoreElements()) {
                    return false;
                }
                pending = parse(service, configs.nextElement());
            }
            // 对当前pending内容进行遍历，每一项代表services的一个实现类
            nextName = pending.next();
            return true;
        }
    }

}
```







### 应用

JDBC4.0以后不再需要显示实例化DB驱动实现类











[SPI官方文档](https://docs.oracle.com/javase/6/docs/api/java/util/ServiceLoader.html)

[SPI源码分析部分](https://www.jianshu.com/p/27c837293aeb)



## Java集合

### ArrayList

**ArrayList类主要信息**

```java
public class ArrayList<E> extends AbstractList<E>
        implements List<E>, RandomAccess, Cloneable, java.io.Serializable
{
    private static final long serialVersionUID = 8683452581122892189L;

    // 数组默认大小为10
    private static final int DEFAULT_CAPACITY = 10;
    
    // 构造函数指定参数为0时的空数组
    private static final Object[] EMPTY_ELEMENTDATA = {};
    
	// 无参构造指定的空数组与EMPTY_ELEMENTDATA的区别是
    // 若数组为空时第一次添加元素，将会被扩容大小为DEFAULT_CAPACITY的数组
    private static final Object[] DEFAULTCAPACITY_EMPTY_ELEMENTDATA = {};

    // 用于存储ArrayList元素的数组
    transient Object[] elementData; // non-private to simplify nested class access

    // ArrayList当前大小
    private int size;

    // ArrayList最大大小
    private static final int MAX_ARRAY_SIZE = Integer.MAX_VALUE - 8;
}
```



**初始化**

```cpp
public ArrayList(int initialCapacity) {
    // 指定大小大于0，则创建指定大小的数组
    if (initialCapacity > 0) {
        this.elementData = new Object[initialCapacity];
        // 指定大小为0，则创建一个空的数组
    } else if (initialCapacity == 0) {
        this.elementData = EMPTY_ELEMENTDATA;
        // 负数则抛出非法参数异常
    } else {
        throw new IllegalArgumentException("Illegal Capacity: "+
                                           initialCapacity);
    }
}
public ArrayList() {
    // 无参构造则创建一个空数组
    this.elementData = DEFAULTCAPACITY_EMPTY_ELEMENTDATA;
}
```

1. 无参构造，会给定一个空数组
2. 有参构造，若大小为0也会给定一个空数组，否则会创建一个指定大小的数组
3. 设置两个空数组的理由是考虑了扩容大小与速度。无参构造第一次add操作会直接扩容为默认大小为10的数组，好处是减少了扩容的次数，无参构造的空数组扩容如10、15，有参构造空数组则按照大小为0、1、2、3、4、6的方式来扩容，好处是节约了内存
4. 大小为0，赋值一个空数组，只有元素被添加进来才会真正开辟空间，体现了懒加载的思想



**add(E e)方法**

```java
// 本地方法
public static native void arraycopy(Object src,  int  srcPos,
                                    Object dest, int destPos,
                                    int length);
public static <T,U> T[] copyOf(U[] original, int newLength, Class<? extends T[]> newType) {
    @SuppressWarnings("unchecked")
    T[] copy = ((Object)newType == (Object)Object[].class)
        ? (T[]) new Object[newLength]
        : (T[]) Array.newInstance(newType.getComponentType(), newLength);
    // 数组赋值
    System.arraycopy(original, 0, copy, 0,
                     Math.min(original.length, newLength));
    return copy;
}
public static <T> T[] copyOf(T[] original, int newLength) {
    return (T[]) copyOf(original, newLength, original.getClass());
}
// 扩容
private void grow(int minCapacity) {
    // overflow-conscious code
    int oldCapacity = elementData.length;
    // 扩容1.5倍
    int newCapacity = oldCapacity + (oldCapacity >> 1);
    // 如果扩容容量小于minCapacity，则扩容为我们需要的大小minCapacity
    if (newCapacity - minCapacity < 0)
        newCapacity = minCapacity;
    if (newCapacity - MAX_ARRAY_SIZE > 0)	// 大于最大大小2^31 - 1
        newCapacity = hugeCapacity(minCapacity);
    elementData = Arrays.copyOf(elementData, newCapacity);
}
private void ensureExplicitCapacity(int minCapacity) {
    modCount++;
    // 最小容量比数组的长度大则扩容
    if (minCapacity - elementData.length > 0)
        grow(minCapacity);
}
private void ensureCapacityInternal(int minCapacity) {
    // 无参构造，第一次添加的值时，最小容量为10
    if (elementData == DEFAULTCAPACITY_EMPTY_ELEMENTDATA) {
        minCapacity = Math.max(DEFAULT_CAPACITY, minCapacity);
    }
    ensureExplicitCapacity(minCapacity);
}
public boolean add(E e) {
    ensureCapacityInternal(size + 1);  // Increments modCount!!
    elementData[size++] = e;
    return true;
}

```

1. 先判断添加后的大小有没有超过当前数组的大小
2. 如果超过了就进行扩容处理
3. 获取当前elementData数组的大小并扩容
4. 判断扩容为原来1.5倍的大小是否大于当前容量
5. 如果小于当前容量，则采用当前容量作为新的数组大小
6. 调用Arrays的copyOf方法
7. copyOf则是调用了本地方法arraycopy，进行了数组的拷贝和扩容
8. 扩容完成后，再进行添加元素操作



**add(int index, E element)方法**

```java
// 越界判断
private void rangeCheckForAdd(int index) {
    if (index > size || index < 0)
        throw new IndexOutOfBoundsException(outOfBoundsMsg(index));
}
public void add(int index, E element) {
    rangeCheckForAdd(index);

    ensureCapacityInternal(size + 1);  // Increments modCount!!
    // 将index后面的数组向后移动一位
    System.arraycopy(elementData, index, elementData, index + 1,
                     size - index);
    elementData[index] = element;
    size++;
}
```

1. 在指定元素插入操作，先判断是否越界
2. 不越界则调用arraycopy方法将指定索引后的所有元素向后移动一位
3. 在指定索引添加元素



**get方法**

```java
public E get(int index) {
    rangeCheck(index);

    return elementData(index);
}
```





**set方法**

```java
public E set(int index, E element) {
    rangeCheck(index);

    E oldValue = elementData(index);
    elementData[index] = element;
    return oldValue;
}
```



**remove方法**

```java
public E remove(int index) {
    rangeCheck(index);

    modCount++;
    E oldValue = elementData(index);

    int numMoved = size - index - 1;
    if (numMoved > 0)
        System.arraycopy(elementData, index+1, elementData, index,
                         numMoved);
    elementData[--size] = null; // 去掉对象的引用

    return oldValue;
}
```





**问题**

ArrayList与LinkedList

* ArrayList底层为动态数组，LinkedList为双向链表
* ArrayList的随机访问比LinkedList快
* ArrayList的顺序访问不一定比LinkedList快
* ArrayList实现了RandomAccess标识接口







### Vector

**add方法**

```java
public synchronized boolean add(E e) {
    modCount++;
    ensureCapacityHelper(elementCount + 1);
    elementData[elementCount++] = e;
    return true;
}
```

实现与ArrayList类似，只不过操作方法有synchroized关键词修饰



### LinkedList

**LinkedList类主要信息**

可以分析出LinkedList是双向链表

```java
public class LinkedList<E>
    extends AbstractSequentialList<E>
    implements List<E>, Deque<E>, Cloneable, java.io.Serializable
{
    transient int size = 0;

    transient Node<E> first;

    transient Node<E> last;
}
```



**Deque接口**

操作LinkedList可以像操作队列和栈一样使用poll，peek，push方法



**Node信息**

静态内部类

```java
private static class Node<E> {
    E item;
    Node<E> next;
    Node<E> prev;

    Node(Node<E> prev, E element, Node<E> next) {
        this.item = element;
        this.next = next;
        this.prev = prev;
    }
}
```





**add方法**

```java
public boolean add(E e) {
    linkLast(e);
    return true;
}
void linkLast(E e) {
    final Node<E> l = last;
    final Node<E> newNode = new Node<>(l, e, null);
    last = newNode;
    if (l == null)
        first = newNode;
    else
        l.next = newNode;
    size++;
    modCount++;
}
```

1. 调用linkLast方法
2. 获取当前链表最后一个节点并使用Node节点的构造函数
3. 判断最后一个节点是否为空
4. 如果空则添加的元素作为链表的首元节点
5. 否则将添加到链表的末尾



**get方法**

```java
Node<E> node(int index) {
    // assert isElementIndex(index);

    // 小优化
    if (index < (size >> 1)) {
        Node<E> x = first;
        for (int i = 0; i < index; i++)
            x = x.next;
        return x;
    } else {
        Node<E> x = last;
        for (int i = size - 1; i > index; i--)
            x = x.prev;
        return x;
    }
}
public E get(int index) {
    checkElementIndex(index);
    return node(index).item;
}
```

1. 判断是否越界
2. 如果没有越界则调用node方法继续查找
3. 判断索引是否小于长度的一半
4. 如果小于则从头开始找，否则从结尾开始找
5. 找到后，返回当前索引的元素



**remove方法**

```java
E unlink(Node<E> x) {
    // assert x != null;
    final E element = x.item;
    final Node<E> next = x.next;
    final Node<E> prev = x.prev;

    if (prev == null) {
        first = next;
    } else {
        prev.next = next;
        x.prev = null;
    }

    if (next == null) {
        last = prev;
    } else {
        next.prev = prev;
        x.next = null;
    }

    x.item = null;
    size--;
    modCount++;
    return element;
}
private void checkElementIndex(int index) {
    if (!isElementIndex(index))
        throw new IndexOutOfBoundsException(outOfBoundsMsg(index));
}
public E remove(int index) {
    checkElementIndex(index);
    return unlink(node(index));
}
```

1. 先判断索引是否越界
2. 没有越界则进行查找工作
3. 调用unlink方法对查找到的元素进行删除
4. 保存待删除元素的直接前驱prev和后驱节点next
5. 判断前驱节点prev是否为空
6. 若为空则将链表头节点设置为后驱节点next
7. 否则设置前驱节点的后继节点为后驱节点next
8. 判断后驱节点next是否为空
9. 若为空则将链表的尾节点设置为前驱节点prev
10. 否则设置后驱节点next的前继节点为前驱节点prev



**set方法**

```java
public E set(int index, E element) {
    checkElementIndex(index);
    Node<E> x = node(index);
    E oldVal = x.item;
    x.item = element;
    return oldVal;
}
```

set方法与get方法差不多



**push方法**

```java
public void push(E e) {
    addFirst(e);
}
```

添加链表首元节点



**poll方法**

```java
// 弹出链表首元节点
public E pollFirst() {
    final Node<E> f = first;
    return (f == null) ? null : unlinkFirst(f);
}
// 弹出链表尾元节点
public E pollLast() {
    final Node<E> l = last;
    return (l == null) ? null : unlinkLast(l);
}
```



**pop方法**

```java
// 弹出链表首元节点
public E pop() {
    return removeFirst();
}
```



**peek方法**

```java
// 返回首元节点
public E peek() {
    final Node<E> f = first;
    return (f == null) ? null : f.item;
}
```





### CopyOnWriteArrayList

由可重入锁和volatile修饰的数组组成的线程安全的ArrayList，适用于读多写少，对内存资源和实时性要求不高的场景。

**基本信息**

```java
public class CopyOnWriteArrayList<E>
    implements List<E>, RandomAccess, Cloneable, java.io.Serializable {
    
    // 可重入锁
    final transient ReentrantLock lock = new ReentrantLock();

    // volatile修饰的数组
    private transient volatile Object[] array;

}
```



**add**

```java
public boolean add(E e) {
    final ReentrantLock lock = this.lock;
    // 使用锁
    lock.lock();
    try {
        Object[] elements = getArray();
        int len = elements.length;
        // 创建一个新的数组
        Object[] newElements = Arrays.copyOf(elements, len + 1);
        newElements[len] = e;
        // array更新为新的数组
        setArray(newElements);
        // 修改成功
        return true;
    } finally {
        lock.unlock();
    }
}

public void add(int index, E element) {
    final ReentrantLock lock = this.lock;
    lock.lock();
    try {
        Object[] elements = getArray();
        int len = elements.length;
        // 越界判断
        if (index > len || index < 0)
            throw new IndexOutOfBoundsException("Index: "+index+
                                                ", Size: "+len);
        Object[] newElements;
        int numMoved = len - index;
        // 插入结尾，同第一个add方法逻辑一样
        if (numMoved == 0)
            newElements = Arrays.copyOf(elements, len + 1);
        // 插入中间
        else {
            newElements = new Object[len + 1];
            System.arraycopy(elements, 0, newElements, 0, index);
            System.arraycopy(elements, index, newElements, index + 1,
                             numMoved);
        }
        newElements[index] = element;
        setArray(newElements);
    } finally {
        lock.unlock();
    }
}
```



**set**

```java
public E set(int index, E element) {
    final ReentrantLock lock = this.lock;
    lock.lock();
    try {
        Object[] elements = getArray();
        E oldValue = get(elements, index);

        if (oldValue != element) {
            int len = elements.length;
            Object[] newElements = Arrays.copyOf(elements, len);
            newElements[index] = element;
            setArray(newElements);
        } else {
            // Not quite a no-op; ensures volatile write semantics
            setArray(elements);
        }
        return oldValue;
    } finally {
        lock.unlock();
    }
}
```



**get**

```java
// 读时不加锁
private E get(Object[] a, int index) {
    return (E) a[index];
}
public E get(int index) {
    return get(getArray(), index);
}
```

* 遍历时不加锁
* 原因是遍历时读取的是原数组



- 已经加锁了，为什么还需要拷贝新数组？
  因为在原数组上进行修改，没有办法触发volatile的可见性，需要修改内存地址，即将新拷贝的数组赋值给原引用





**评价**

* 相比于Vector类来说，COWArrayList在写时同时允许读操作，大大提高了读操作的效率，适合写少读多的场景
* 内存占用：写操作时需要创建新的数组，使得内存占用大
* 数据不一致：COWArrayList只能保证数据的最终一致性，不能保证数据的实时一致性
* 因此COWArrayList不适合内存敏感或者实时性要求高的场景





### Map接口

```java
添加功能
V put(K key, V value);
删除功能
V remove(Object key);
// 清空集合
void clear();
判断功能
// 判断集合是否有指定键
boolean containsKey(Object key);
// 判断集合是否有指定值
boolean containsValue(Object value);
// 判断是否为空
boolean isEmpty();
获取功能
// 根据K获取V
V get(Object key);
// 返回键值对对象集合
Set<Map.Entry<K, V>> entrySet();
// 返回关键字集合
Set<K> keySet();
// 返回值的集合
Collection<V> values();
```







### HashMap



#### 介绍

HashMap实现了Map接口，提供了常数时间复杂度的get/set方法的哈希表，JDK8以前底层数据结构采用了数组链表的方式，JDK8采用了数组链表加红黑树的方式。它是一个线程不安全的集合类，构造哈希表时，主要由容量和平衡因子所决定。



#### 基本信息

```java
public class HashMap<K,V> extends AbstractMap<K,V>
    implements Map<K,V>, Cloneable, Serializable {
    /**
     * 默认初始化大小—必须是2的幂次
     */
    static final int DEFAULT_INITIAL_CAPACITY = 1 << 4; // aka 16

    /**
     * 最大容量为2^30次方
     */
    static final int MAXIMUM_CAPACITY = 1 << 30;

    /**
     * 默认负载因子为0.75
     */
    static final float DEFAULT_LOAD_FACTOR = 0.75f;

    /**
     * 哈希表树化的条件之一，某个桶的链表长度大于等于8
     */
    static final int TREEIFY_THRESHOLD = 8;

    /**
     * 数量小于等于UNTREEIFY_THRESHOLD则会变成链表
     */
    static final int UNTREEIFY_THRESHOLD = 6;

    /**
     * 树化的第一个条件，table的容量必须大于64
     */
    static final int MIN_TREEIFY_CAPACITY = 64;
    
    
    /**
     * Node数组存放放键值对
     */
    transient Node<K,V>[] table;

    /**
     * Holds cached entrySet(). Note that AbstractMap fields are used
     * for keySet() and values().
     */
    transient Set<Map.Entry<K,V>> entrySet;

    /**
     * 键值对个数
     */
    transient int size;


    /**
     * The next size value at which to resize (capacity * load factor).
     *
     * @serial
     */
    // (The javadoc description is true upon serialization.
    // Additionally, if the table array has not been allocated, this
    // field holds the initial array capacity, or zero signifying
    // DEFAULT_INITIAL_CAPACITY.)
    int threshold;

    /**
     * 哈希表的负载因子
     */
    final float loadFactor;
}
// HashMap作为链表的数据结构结点
static class Node<K,V> implements Map.Entry<K,V> {
    final int hash;
    final K key;
    V value;
    Node<K,V> next;

    Node(int hash, K key, V value, Node<K,V> next) {
        this.hash = hash;
        this.key = key;
        this.value = value;
        this.next = next;
    }

    public final K getKey()        { return key; }
    public final V getValue()      { return value; }
    public final String toString() { return key + "=" + value; }

    // 重写了hashCode方法，返回的是key和value的异或值
    public final int hashCode() {
        return Objects.hashCode(key) ^ Objects.hashCode(value);
    }

    public final V setValue(V newValue) {
        V oldValue = value;
        value = newValue;
        return oldValue;
    }

    // 重写equals方法
    public final boolean equals(Object o) {
        if (o == this)
            return true;
        if (o instanceof Map.Entry) {
            Map.Entry<?,?> e = (Map.Entry<?,?>)o;
            if (Objects.equals(key, e.getKey()) &&
                Objects.equals(value, e.getValue()))
                return true;
        }
        return false;
    }
}
static final int hash(Object key) {
    int h;
    return (key == null) ? 0 : (h = key.hashCode()) ^ (h >>> 16);
}
```

#### 构造方法

```java
// 无参构造的负载因子为默认
public HashMap() {
    this.loadFactor = DEFAULT_LOAD_FACTOR; // all other fields defaulted
}
// 指定桶的大小
public HashMap(int initialCapacity) {
    this(initialCapacity, DEFAULT_LOAD_FACTOR);
}
// 指定桶和负载因子
public HashMap(int initialCapacity, float loadFactor) {
    if (initialCapacity < 0)
        throw new IllegalArgumentException("Illegal initial capacity: " +
                                           initialCapacity);
    if (initialCapacity > MAXIMUM_CAPACITY)
        initialCapacity = MAXIMUM_CAPACITY;
    if (loadFactor <= 0 || Float.isNaN(loadFactor))
        throw new IllegalArgumentException("Illegal load factor: " +
                                           loadFactor);
    this.loadFactor = loadFactor;
    this.threshold = tableSizeFor(initialCapacity);
}

// 分配table的大小
// 如果为2的幂次则返回原来的
// 本函数也就是求最接近cap的某个2的幂次的值
static final int tableSizeFor(int cap) {
    int n = cap - 1;
    n |= n >>> 1;
    n |= n >>> 2;
    n |= n >>> 4;
    n |= n >>> 8;
    n |= n >>> 16;
    // 执行完上式，左起的1后共有16个1，再加上后面的1就为2的幂次
    return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
}

```



#### 获取

```java
// 给定桶的位置以及关键字查找
final Node<K,V> getNode(int hash, Object key) {
    Node<K,V>[] tab; Node<K,V> first, e; int n; K k;
    // first指向哈希桶的首个结点
    if ((tab = table) != null && (n = tab.length) > 0 &&
        (first = tab[(n - 1) & hash]) != null) {
        if (first.hash == hash && // always check first node
            ((k = first.key) == key || (key != null && key.equals(k))))
            return first;
        // 遍历桶，寻找指定值
        if ((e = first.next) != null) {
            // 红黑树形式查找
            if (first instanceof TreeNode)
                return ((TreeNode<K,V>)first).getTreeNode(hash, key);
            // 链表形式查找
            do {
                if (e.hash == hash &&
                    ((k = e.key) == key || (key != null && key.equals(k))))
                    return e;
            } while ((e = e.next) != null);
        }
    }
    return null;
}
// 通过关键字获取值
public V get(Object key) {
    Node<K,V> e;
    return (e = getNode(hash(key), key)) == null ? null : e.value;
}

// 判断是否存在关键字
public boolean containsKey(Object key) {
    return getNode(hash(key), key) != null;
}
// 判断是否存在值
public boolean containsValue(Object value) {
    Node<K,V>[] tab; V v;
    // 如果表不为空才开始遍历
    if ((tab = table) != null && size > 0) {
        // 遍历哈希桶
        for (int i = 0; i < tab.length; ++i) {
            // 遍历哈希桶的每一个值
            for (Node<K,V> e = tab[i]; e != null; e = e.next) {
                if ((v = e.value) == value ||
                    (value != null && value.equals(v)))
                    return true;
            }
        }
    }
    return false;
}
```



#### 插入操作

```java
final V putVal(int hash, K key, V value, boolean onlyIfAbsent,
               boolean evict) {
    Node<K,V>[] tab; Node<K,V> p; int n, i;
    // table为空则resize，同时获取表的长度
    if ((tab = table) == null || (n = tab.length) == 0)
        n = (tab = resize()).length;
    // 桶为空则直接插入
    if ((p = tab[i = (n - 1) & hash]) == null)
        tab[i] = newNode(hash, key, value, null);
    else {
        Node<K,V> e; K k;
        // 哈希桶首节点的值与要插入的值相同
        if (p.hash == hash &&
            ((k = p.key) == key || (key != null && key.equals(k))))
            e = p;
        // 使用红黑树方式来插入
        else if (p instanceof TreeNode)
            e = ((TreeNode<K,V>)p).putTreeVal(this, tab, hash, key, value);
        else {
            // 从链表的第二个结点开始遍历
            for (int binCount = 0; ; ++binCount) {
                // 到了链表尾部，直接插入
                if ((e = p.next) == null) {
                    p.next = newNode(hash, key, value, null);
                    // 如果链表大小超过了最小树化大小，默认为8则树化
                    if (binCount >= TREEIFY_THRESHOLD - 1) // -1 for 1st
                        treeifyBin(tab, hash);
                    break;
                }
                // 存在同一个关键字
                if (e.hash == hash &&
                    ((k = e.key) == key || (key != null && key.equals(k))))
                    break;
                p = e;
            }
        }
        // 已存在该关键字
        if (e != null) { // existing mapping for key
            V oldValue = e.value;
            // 如果onlyIfAbsent=false或者oldValue=null则替换
            if (!onlyIfAbsent || oldValue == null)
                e.value = value;
            afterNodeAccess(e);
            // 将旧的value返回
            return oldValue;
        }
    }
    ++modCount;
    // map大小超过阈值则再哈希
    if (++size > threshold)
        resize();
    afterNodeInsertion(evict);
    return null;
}
// 调用putVal方法
public V put(K key, V value) {
    return putVal(hash(key), key, value, false, true);
}
```





#### 删除操作

```java
// 和putVal函数类似
final Node<K,V> removeNode(int hash, Object key, Object value,
                           boolean matchValue, boolean movable) {
    Node<K,V>[] tab; Node<K,V> p; int n, index;
    // 哈希表表和哈希桶不为空
    if ((tab = table) != null && (n = tab.length) > 0 &&
        (p = tab[index = (n - 1) & hash]) != null) {
        Node<K,V> node = null, e; K k; V v;
        // 先判断哈希桶的首结点是否为目标结点
        if (p.hash == hash &&
            ((k = p.key) == key || (key != null && key.equals(k))))
            node = p;
        // 遍历
        else if ((e = p.next) != null) {
            // 如果属于TreeNode结点则调用getTreeNode函数进行查找
            if (p instanceof TreeNode)
                node = ((TreeNode<K,V>)p).getTreeNode(hash, key);
            // 否则按链表形式从第二个位置遍历
            else {
                do {
                    if (e.hash == hash &&
                        ((k = e.key) == key ||
                         (key != null && key.equals(k)))) {
                        node = e;
                        break;
                    }
                    p = e;
                } while ((e = e.next) != null);
            }
        }
        // 找到了需要删除的结点node，执行删除操作
        if (node != null && (!matchValue || (v = node.value) == value ||
                             (value != null && value.equals(v)))) {
            // 结点属于TreeNode则使用红黑树版的删除结点操作
            if (node instanceof TreeNode)
                ((TreeNode<K,V>)node).removeTreeNode(this, tab, movable);
            // 否则执行链表的删除结点操作
            // 1. 如果为哈希桶的首结点则将后面结点置为首结点
            // 否则用待删除结点前驱结点连接待删除结点的后驱结点
            else if (node == p)
                tab[index] = node.next;
            else
                p.next = node.next;
            ++modCount;
            --size;
            afterNodeRemoval(node);
            // 返回删除结点
            return node;
        }
    }
    return null;
}
// 调用removeNode删除
public V remove(Object key) {
    Node<K,V> e;
    return (e = removeNode(hash(key), key, null, false, true)) == null ?
        null : e.value;
}
```



#### 再哈希

```java
// resize函数主要做两件事，计算newCap新容量和newThr阈值
final Node<K,V>[] resize() {
    Node<K,V>[] oldTab = table;
    // 获取旧容量和旧阈值
    int oldCap = (oldTab == null) ? 0 : oldTab.length;
    int oldThr = threshold;
    int newCap, newThr = 0;
    // 旧容量大于0时
    if (oldCap > 0) {
        // 旧容量已经大于或等于最大容量时旧不resize，直接返回
        if (oldCap >= MAXIMUM_CAPACITY) {
            threshold = Integer.MAX_VALUE;
            return oldTab;
        }
        // 否则将新容量设置为旧容量的两倍，并判断新容量是否小于最大容量且旧容量是否大于等于默认默认初始化容量
        // 成立则新的阈值扩大为原来的两倍
        else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY &&
                 oldCap >= DEFAULT_INITIAL_CAPACITY)
            newThr = oldThr << 1; // double threshold
    }
    // 使用过有参构造函数且没有table为null，将新容量设置为旧的阈值
    else if (oldThr > 0) // initial capacity was placed in threshold
        newCap = oldThr;
    // 使用的是无参构造
    // 新容量为默认初始化容量，新阈值为默认负载因子*默认初始化容量=0.75*20=12
    else {               // zero initial threshold signifies using defaults
        newCap = DEFAULT_INITIAL_CAPACITY;
        newThr = (int)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
    }
    // 当旧阈值为0时，对其进行赋值newCap * loadFactor
    if (newThr == 0) {
        float ft = (float)newCap * loadFactor;
        newThr = (newCap < MAXIMUM_CAPACITY && ft < (float)MAXIMUM_CAPACITY ?
                  (int)ft : Integer.MAX_VALUE);
    }
    threshold = newThr;
    @SuppressWarnings({"rawtypes","unchecked"})
    // resize操作
    Node<K,V>[] newTab = (Node<K,V>[])new Node[newCap];
    table = newTab;
    if (oldTab != null) {
        // 遍历每一个哈希桶
        for (int j = 0; j < oldCap; ++j) {
            Node<K,V> e;
            // 哈希桶不为空时则需要处理
            if ((e = oldTab[j]) != null) {
                oldTab[j] = null;
                // 如果哈希桶之有一个元素，则直接放在下标为e.hash & (newCap - 1)下
                if (e.next == null)
                    newTab[e.hash & (newCap - 1)] = e;
                // 如果哈希桶有多个元素则，且e为TreeNode交给split函数
                else if (e instanceof TreeNode)
                    ((TreeNode<K,V>)e).split(this, newTab, j, oldCap);
                // 否则由链表的内层循环完成再哈希
                else { // preserve order
                    Node<K,V> loHead = null, loTail = null;
                    Node<K,V> hiHead = null, hiTail = null;
                    Node<K,V> next;
                    // 将原来的链表分成两份低链表和高链表
                    do {
                        next = e.next;
                        // oldCap为2的幂次，如果等于0说明新的哈希表桶与旧的哈希表桶的下标位置没变，则插入低链表
                        if ((e.hash & oldCap) == 0) {
                            if (loTail == null)
                                loHead = e;
                            else
                                loTail.next = e;
                            loTail = e;
                        }
                        // 新的哈希表桶与旧的哈希表桶的下标位置变化了，插入高链表
                        else {
                            if (hiTail == null)
                                hiHead = e;
                            else
                                hiTail.next = e;
                            hiTail = e;
                        }
                    } while ((e = next) != null);
                    // 旧的哈希表桶插入原来的下标
                    if (loTail != null) {
                        loTail.next = null;
                        newTab[j] = loHead;
                    }
                    // 位置变化的下标的高链表插入下标为原来的位置+桶的容量
                    if (hiTail != null) {
                        hiTail.next = null;
                        newTab[j + oldCap] = hiHead;
                    }
                }
            }
        }
    }
    return newTab;
}
```



#### 红黑树操作



**左旋操作**

```java
// root为红黑树的根结点，p为旋转支点
    pp                             pp    
   /  \                           /  \
  ppl  ppr(p)                   ppl  pr(r)
       / \                           /  \ 
      pl pr(r)                    ppr(p) rr
        /  \                      /  \
       rl  rr                    pl  rl
static <K,V> TreeNode<K,V> rotateLeft(TreeNode<K,V> root,
                                      TreeNode<K,V> p) {
    TreeNode<K,V> r, pp, rl;
     // 判断旋转支点p和p的右孩子是否为空
    if (p != null && (r = p.right) != null) {
        // 将rl接到p的右孩子上
        if ((rl = p.right = r.left) != null)
            rl.parent = p;
        // 将r父结点设置为p的父结点，如果父结点为空则将r设置为红黑树的根结点
        if ((pp = r.parent = p.parent) == null)
            (root = r).red = false;
        // 如果p为pp的左孩子，则设置pp的左孩子为r
        else if (pp.left == p)
            pp.left = r;
        // 否则设置pp的右孩子为r
        else
            pp.right = r;
        // 将p及其子树接到r的左孩子上
        r.left = p;
        p.parent = r;
    }
    return root;
}
```



**右旋操作**

```java
// root为红黑树的根结点，p为旋转支点
      pp                       pp
    /   \                    /   \
   ppl  ppr(p)              ppl   pl(l)
       /   \                     /   \
      pl(l) pr                  ll   ppr(p)
     /  \                            /  \ 
    ll  lr                          lr   pr
static <K,V> TreeNode<K,V> rotateRight(TreeNode<K,V> root,
                                       TreeNode<K,V> p) {
    TreeNode<K,V> l, pp, lr;
    // 判断旋转支点以及旋转支点的左孩子是否为空
    if (p != null && (l = p.left) != null) {
        // 将lr接到p的左孩子结点
        if ((lr = p.left = l.right) != null)
            lr.parent = p;
        // 将l的父节点设置为p的父结点，如果父结点为空则将l作为根结点
        if ((pp = l.parent = p.parent) == null)
            (root = l).red = false;
        // 如果p为pp的左孩子，则设置pp的左孩子为l
        else if (pp.right == p)
            pp.right = l;
        // 否则设置pp的右孩子为l
        else
            pp.left = l;
        l.right = p;
        p.parent = l;
    }
    return root;
}
```



**红黑树版的resize**

```java
final void split(HashMap<K,V> map, Node<K,V>[] tab, int index, int bit) {
    TreeNode<K,V> b = this;
    // Relink into lo and hi lists, preserving order
    TreeNode<K,V> loHead = null, loTail = null;
    TreeNode<K,V> hiHead = null, hiTail = null;
    int lc = 0, hc = 0;
    // 以链表方式遍历，获取高位低位链表
    for (TreeNode<K,V> e = b, next; e != null; e = next) {
        next = (TreeNode<K,V>)e.next;
        e.next = null;
        if ((e.hash & bit) == 0) {
            if ((e.prev = loTail) == null)
                loHead = e;
            else
                loTail.next = e;
            loTail = e;
            ++lc;
        }
        else {
            if ((e.prev = hiTail) == null)
                hiHead = e;
            else
                hiTail.next = e;
            hiTail = e;
            ++hc;
        }
    }
	// 判断链表大小是否小于等于链化容量6
    // 小于等于就进行链化，否则进行树化
    if (loHead != null) {
        if (lc <= UNTREEIFY_THRESHOLD)
            tab[index] = loHead.untreeify(map);
        else {
            tab[index] = loHead;
            if (hiHead != null) // (else is already treeified)
                loHead.treeify(tab);
        }
    }
    if (hiHead != null) {
        if (hc <= UNTREEIFY_THRESHOLD)
            tab[index + bit] = hiHead.untreeify(map);
        else {
            tab[index + bit] = hiHead;
            if (loHead != null)
                hiHead.treeify(tab);
        }
    }
}
```



**链化**

```java
final Node<K,V> untreeify(HashMap<K,V> map) {
    Node<K,V> hd = null, tl = null;
    for (Node<K,V> q = this; q != null; q = q.next) {
        Node<K,V> p = map.replacementNode(q, null);
        if (tl == null)
            hd = p;
        else
            tl.next = p;
        tl = p;
    }
    return hd;
}
```



**树化（双向链表转化为红黑树）**

```java
final void treeify(Node<K,V>[] tab) {
    TreeNode<K,V> root = null;
    // 遍历双向链表的所有元素并插入
    for (TreeNode<K,V> x = this, next; x != null; x = next) {
        next = (TreeNode<K,V>)x.next;
        x.left = x.right = null;
        // 根结点则为黑色
        if (root == null) {
            x.parent = null;
            x.red = false;
            root = x;
        }
        else {
            K k = x.key;
            int h = x.hash;
            Class<?> kc = null;
            // 查找插入位置并插入和自平衡
            for (TreeNode<K,V> p = root;;) {
                int dir, ph;
                K pk = p.key;
                // 比较大小
                if ((ph = p.hash) > h)
                    dir = -1;
                else if (ph < h)
                    dir = 1;
                else if ((kc == null &&
                          (kc = comparableClassFor(k)) == null) ||
                         (dir = compareComparables(kc, k, pk)) == 0)
                    dir = tieBreakOrder(k, pk);
                
                TreeNode<K,V> xp = p;
                // 根据非0值dir插入，dir大于0则往p的右子树插入，否则往左子树插入
                if ((p = (dir <= 0) ? p.left : p.right) == null) {
                    // p为空则找到了待插入结点的位置
                    // 比父节点小插入左边，否则插入右边
                    x.parent = xp;
                    if (dir <= 0)
                        xp.left = x;
                    else
                        xp.right = x;
                    // 进行自平衡操作
                    root = balanceInsertion(root, x);
                    break;
                }
            }
        }
    }
    // 将根结点插入哈希桶首结点
    moveRootToFront(tab, root);
}
```





**插入自平衡**

```java
static <K,V> TreeNode<K,V> balanceInsertion(TreeNode<K,V> root,
                                            TreeNode<K,V> x) {
    // 默认插入红色结点
    x.red = true;
    for (TreeNode<K,V> xp, xpp, xppl, xppr;;) {
        // 情况1：无根
        // 不用调整
        if ((xp = x.parent) == null) {
            x.red = false;
            return x;
        }
        // 情况2：父结点为黑色结点
        // 不用调整
        // 注：父结点为红，爷爷结点为空这种情况不可能会出现，只是为了给爷爷结点xpp赋值
        else if (!xp.red || (xpp = xp.parent) == null)
            return root;
        // 父结点为左结点
        if (xp == (xppl = xpp.left)) {
            // 情况3：叔叔结点为红色时，父节点一定为黑色(4结点)
            // 调整：变色，爷爷变成红色，父结点和叔叔结点变成黑色
            if ((xppr = xpp.right) != null && xppr.red) {
                xppr.red = false;
                xp.red = false;
                xpp.red = true;
                // 插入结点设置为爷爷结点，下次循环继续调整
                x = xpp;
            }
            // 情况4：叔叔结点为黑色结点，父结点一定为红色，爷爷结点为黑色
            else {
                // 插入结点为父结点的右孩子
                // 调整：以父结点为支点左旋，插入结点到了原来的父结点位置上
                if (x == xp.right) {
                    root = rotateLeft(root, x = xp);
                    // 注：这也是赋值行为，获取新的父结点，xp为原来的插入结点
                    xpp = (xp = x.parent) == null ? null : xp.parent;
                }
                // 不执行上面的if，说明插入结点为父结点的左孩子，否则就是右孩子
                // 父结点变成黑色，爷爷结点变成红色，对爷爷结点进行右旋操作
                if (xp != null) {
                    xp.red = false;
                    if (xpp != null) {
                        xpp.red = true;
                        root = rotateRight(root, xpp);
                    }
                }
            }
        }
        // 父结点为右结点，则进行对称操作
        else {
            // 叔叔结点为红色结点，爷爷结点为黑色结点
            // 调整：父结点和叔叔结点变黑，爷爷结点变红
            if (xppl != null && xppl.red) {
                xppl.red = false;
                xp.red = false;
                xpp.red = true;
                // 插入结点设置为爷爷结点，下次循环继续调整
                x = xpp;
            }
            // 叔叔结点为黑色结点
            else {
                // 插入结点为父结点的左孩子
                // 先进行右旋操作，插入结点到了原来父结点位置上
                if (x == xp.left) {
                    root = rotateRight(root, x = xp);
                    xpp = (xp = x.parent) == null ? null : xp.parent;
                }
                // 父结点变成黑色结点，爷爷结点变成红色，对爷爷结点进行左旋
                if (xp != null) {
                    xp.red = false;
                    if (xpp != null) {
                        xpp.red = true;
                        root = rotateLeft(root, xpp);
                    }
                }
            }
        }
    }
}
```



**删除结点**

```java
final void removeTreeNode(HashMap<K,V> map, Node<K,V>[] tab,
                          boolean movable) {
    int n;
    if (tab == null || (n = tab.length) == 0)
        return;
    int index = (n - 1) & hash;
    TreeNode<K,V> first = (TreeNode<K,V>)tab[index], root = first, rl;
    TreeNode<K,V> succ = (TreeNode<K,V>)next, pred = prev;
    if (pred == null)
        tab[index] = first = succ;
    else
        pred.next = succ;
    if (succ != null)
        succ.prev = pred;
    if (first == null)
        return;
    if (root.parent != null)
        root = root.root();
    if (root == null || root.right == null ||
        (rl = root.left) == null || rl.left == null) {
        tab[index] = first.untreeify(map);  // too small
        return;
    }
    // 红黑树寻找后驱结点以及删除指定值操作
    // p为待删除结点
    TreeNode<K,V> p = this, pl = left, pr = right, replacement;
    // 有两个子树
    if (pl != null && pr != null) {
        // s为后驱结点，一定没有左孩子
        TreeNode<K,V> s = pr, sl;
        while ((sl = s.left) != null) // find successor
            s = sl;
        // 交换后驱结点s和待删除结点的颜色p
        boolean c = s.red; s.red = p.red; p.red = c; // swap colors
        TreeNode<K,V> sr = s.right;
        TreeNode<K,V> pp = p.parent;
        // 如果待删除结点p的右孩子为后驱结点s
        // 以s结点为支点左旋
        if (s == pr) { // p was s's direct parent
            p.parent = s;
            s.right = p;
        }
        else {
            TreeNode<K,V> sp = s.parent;
            if ((p.parent = sp) != null) {
                if (s == sp.left)
                    sp.left = p;
                else
                    sp.right = p;
            }
            if ((s.right = pr) != null)
                pr.parent = s;
        }
        // 公共操作
        // p的左孩子为空
        p.left = null;
        // p的右孩子为后驱结点的右孩子
        if ((p.right = sr) != null)
            sr.parent = p;
        // s的左孩子为p的左孩子
        if ((s.left = pl) != null)
            pl.parent = s;
        // 设置s的父亲
        if ((s.parent = pp) == null)
            root = s;
        else if (p == pp.left)
            pp.left = s;
        else
            pp.right = s;
        // 替代结点replacement一定为叶子结点
        // sr不为空则用sr作为替代结点
        if (sr != null)
            replacement = sr;
        // 否则使用p来作为替代结点
        else
            replacement = p;
    }
    else if (pl != null)
        replacement = pl;
    else if (pr != null)
        replacement = pr;
    else
        replacement = p;
    // 替换结点不为待删除结点p时（此时p不为叶子结点）
    // 执行完后replacement成为了叶子结点，p被断开
    if (replacement != p) {
        TreeNode<K,V> pp = replacement.parent = p.parent;
        if (pp == null)
            root = replacement;
        else if (p == pp.left)
            pp.left = replacement;
        else
            pp.right = replacement;
        p.left = p.right = p.parent = null;
    }

    // 删除的结点p为红色则不用调整
    TreeNode<K,V> r = p.red ? root : balanceDeletion(root, replacement);

    // 替换结点为待删除结点p时（此时p为叶子结点）
    if (replacement == p) {  // detach
        TreeNode<K,V> pp = p.parent;
        p.parent = null;
        if (pp != null) {
            if (p == pp.left)
                pp.left = null;
            else if (p == pp.right)
                pp.right = null;
        }
    }
    if (movable)
        moveRootToFront(tab, r);
}
```



**删除自平衡**

```java
// root为红黑树根结点，x为替换的结点（一开始位于叶子结点）且一定为黑色结点，所以需要平衡操作
static <K,V> TreeNode<K,V> balanceDeletion(TreeNode<K,V> root,
                                           TreeNode<K,V> x) {
    // 循环是为了向上来寻找平衡点
    for (TreeNode<K,V> xp, xpl, xpr;;)  {
        // 基本情况，直接返回
        if (x == null || x == root)
            return root;
        // x为根结点
        else if ((xp = x.parent) == null) {
            x.red = false;
            return x;
        }
        // x为红色结点，找到了平衡点，将其改为黑色完成了平衡操作
        else if (x.red) {
            x.red = false;
            return root;
        }
        // 左倾的情况，x结点为黑色
        else if ((xpl = xp.left) == x) {
            // 兄弟结点xpr为红色，xprl和xprr一定为黑色，父结点一定为黑色
            // xpr变黑色，xp变红色，xp左旋，调整为x的兄弟结点为黑色结点
            if ((xpr = xp.right) != null && xpr.red) {
                xpr.red = false;
                xp.red = true;
                root = rotateLeft(root, xp);
                // 调整完后，xpr为原来的xprl
                xpr = (xp = x.parent) == null ? null : xp.right;
            }
            // 到这里，x的兄弟结点一定为黑色
            // xpr为空，递归向上寻找平衡点
            if (xpr == null)
                x = xp;
            // 兄弟结点黑色且不为空，即有孩子结点
            else {
                TreeNode<K,V> sl = xpr.left, sr = xpr.right;
                // 兄弟结点的两个子结点都为黑色
                // 则兄弟结点“自损”变红，向上递归寻找平衡点
                if ((sr == null || !sr.red) &&
                    (sl == null || !sl.red)) {
                    xpr.red = true;
                    x = xp;
                }
                // 兄弟结点的两个子结点不全为黑色
                // 落到这种情况，调整完之后一定是平衡了
                else {
                    // sr为黑色结点，sl为红色结点
                    // sl变黑色，兄弟结点变红，兄弟结点右旋，将兄弟结点设置为sl
                    if (sr == null || !sr.red) {
                        if (sl != null)
                            sl.red = false;
                        xpr.red = true;
                        root = rotateRight(root, xpr);
                        xpr = (xp = x.parent) == null ?
                            null : xp.right;
                    }
                    // 执行到这里，最终兄弟结点的右孩子一定为红色
                    
                    if (xpr != null) {
                        xpr.red = (xp == null) ? false : xp.red;
                        if ((sr = xpr.right) != null)
                            sr.red = false;
                    }
                    // 父结点为红色，兄弟结点为黑色
                    // 父结点变成黑色，以父结点为支点左旋就平衡了
                    if (xp != null) {
                        xp.red = false;
                        root = rotateLeft(root, xp);
                    }
                    x = root;
                }
            }
        }
        // x在右边
        else { // symmetric
            // 兄弟结点为红色
            // 父结点变红，兄弟结点变黑，以父结点为支点右旋
            if (xpl != null && xpl.red) {
                xpl.red = false;
                xp.red = true;
                root = rotateRight(root, xp);
                // 新的兄弟结点一定为黑色
                xpl = (xp = x.parent) == null ? null : xp.left;
            }
            // 兄弟结点为空，向上调整
            if (xpl == null)
                x = xp;
            // 兄弟结点不为空
            else {
                TreeNode<K,V> sl = xpl.left, sr = xpl.right;
                // 兄弟结点的两个孩子结点为黑色
                // 兄弟结点变红，向上调整
                if ((sl == null || !sl.red) &&
                    (sr == null || !sr.red)) {
                    xpl.red = true;
                    x = xp;
                }
                // 兄弟结点的孩子结点至少有一个为红色结点
                else {
                    // 左孩子sl为黑色，右孩子sr为红色
                    // 右孩子sr变黑，兄弟结点变红，以兄弟结点为支点左旋，兄弟结点变成原来的sr
                    if (sl == null || !sl.red) {
                        if (sr != null)
                            sr.red = false;
                        xpl.red = true;
                        root = rotateLeft(root, xpl);
                        xpl = (xp = x.parent) == null ?
                            null : xp.left;
                    }
                    // 兄弟结点不为空
                    if (xpl != null) {
                        xpl.red = (xp == null) ? false : xp.red;
                        if ((sl = xpl.left) != null)
                            sl.red = false;
                    }
                    // 兄弟结点为黑色，父结点变黑，以父结点为支点右旋
                    if (xp != null) {
                        xp.red = false;
                        root = rotateRight(root, xp);
                    }
                    x = root;
                }
            }
        }
    }
}
```



#### 小总结

**HashMap主要成员**

* Entry<K,V>[] table，这个Entry类型存储了HashMap的真正数据
* size大小代表HashMap存储的键值对个数
* capacity容量，table数组的大小，容量一定为2的次方
* threshold阈值和loadFactor装载因子。threshold是通过loadFactor*capacity得到的，当size超过threshold时，HashMap会再扩容
* DEFAULT_INITIAL_CAPICITY 表示默认大小为16
* TREEIFY_THRESHOLD 树化条件之一，链表长度大于8
* MIN_TREEIFY_CAPACITY 树化条件之一，树化时数组大小最少为64

**HashMap的底层原理**

* JDK8之前，采用的是数组链表的结构来存储关键字，JDK8则采用了数组链表+红黑树方式来存储，一个数组元素代表了一个哈希桶，一个哈希桶要么是链表，要么是红黑树结构
* 由于数组具有随机存取的特点，采用哈希映射我们可以快速地通过下标的方式找到哈希桶，然后从哈希桶中获取值

**构造函数**

* HashMap无参构造时，默认的负载因子为0.75，默认table数组大小为16，所以默认的阈值threshold为12
* 指定了table数组容量时，会调用tableSizeFor函数来分配数组的大小，这个函数会求一个最接近指定值的2的次方数，若指定值为2的次方则数组大小就为该值

**HashMap的get方法**

* 获取的工作大部分由getNode函数完成，get函数会传入关键字和以及哈希值
* 如果哈希桶头结点为空则返回null
* 如果哈希桶头结点与关键字对象相同或者哈希值相同的话返回头结点
* 如果头结点的关键字与待查找的不相同且还有后继则进行遍历
* 如果当前哈希桶采用了红黑树结构则调用getTreeNode（使用了BST树的查找方法）的方式来查找
* 如果是链表，则遍历所有结点，寻找到相同的key则返回
* 如果哈希表所有的值都不与要查找的不同则返回null

**HashMap的put方法**

* 插入的工作大部分由putVal方法，put函数会传入待插入值、哈希值等参数
* 如果table数组为空，则调用resize函数获取一个非空的table
* 根据传入的关键字来获取table数组的下标从而得到哈希桶
* 然后判断哈希桶的首结点是否为空，若为空则直接插入
* 如果哈希桶的首结点关键字与待插入的关键字相同且允许替换，那么首结点的值将被替换
* 如果哈希桶的首结点关键字不同则发生了哈希碰撞       
* 若哈希桶的结构为红黑树结构则调用putTreeVal函数来插入
* 否则哈希桶为链表结点，遍历到链表结尾后进行插入
* 如果键值对的大小超过了阈值，则会调用resize函数

**HashMap的resize**

* resize函数主要是重新确定了newCap、newThr，然后进行哈希扩容
* 如果table数组已经被初始化了且容量为最大（$2^{30}$）那么就不会resize了直接返回
* 如果table数组已经被初始化但是两倍后的旧容量仍小于最大容量，那么新容量就为旧容量的两倍且新阈值也会翻倍
* 如果table数组没有被初始化且旧容量大于0，则说明这是有参构造函数指定的旧容量，那么新容量就为原来的旧阈值
* 如果table数组没被初始化且旧容量为0，说明这是使用了无参构造，新容量为默认初始容量16，新阈值为默认阈值12
* 经过上面的判断后如果新阈值仍然为0，那么使用新容量乘以负载因子来计算新阈值
* 然后进行哈希扩容操作，首先会遍历table数组的每一个哈希桶
* 如果哈希桶只有一个元素则直接插入新的table数组
* 如果哈希桶的结构为红黑树就调用split方法
* 否则哈希桶为链表，JDK8避免了hash值重新计算，而是将链表分成高位链表和低位链表，分的依据是哈希值与旧容量进行与运算，结果为0在低位链表，否则为高位链表
* 链表分离使用了位运算的技巧，最终将节点的位置要么在原来的哈希桶，要么就是原来哈希桶下标+原来哈希桶的容量
  * 由于新容量为2的倍数且为旧容量的2倍，比如10000b即16为新容量，那么旧容量1000b，table下标为000b-111b，能影响下标的只有后3位bit，扩容两倍后，影响下标变成了后4bit，那么后3位bit不变，新的table数组下标取决于第4位bit，且只有两种可能，第一种是等于0，那么这一类一定还是在原来的下标，第二种是等于1，这一类下标就是原来的下标加上旧容量
* 遍历完哈希桶就将低位链表插入原来下标，高位链表插入原来下表+旧容量

**HashMap的remove**

* remove函数主要工作是在removeNode完成的
* 如果table数组为空则返回null，否则得到哈希桶
* 如果table数组不为空，则先判断哈希桶是否存在首结点
* 如果首结点为空，返回null
* 首结点不为空判断是否与待删除关键字相同则找到
* 首结点与待删除关键字不同判断先判断是否为红黑树结构
* 如果是则使用getTreeNode来查找，否则进行链表遍历
* 然后对找到的非空对象进行处理
* 如果为红黑树结构就是用removeTreeNode删除
* 否则执行链表的删除结点操作

**为什么TREEIFY_THRESHOLD = 8**

* 综合了时间和空间上的共同考量，结点的hashcode随机条件下服从泊松分布，那么在一般情况下哈希桶超过8个元素的概率千万分之一，避免了频繁树化导致哈希表内存占用过大，同时也保证了查找时间具有良好的性能

* 链表的查询时间复杂度为O(n)，红黑树的查询时间复杂度为O(logn)
* 在数据量不多的时候，使用链表比较快，只有当数据量比较大的时候，才会转化为红黑树，但是红黑树占用的空间大小是链表的2倍，考虑到时间和空间上的损耗，所以要设置边界值（其实链表长度为8的概率很低，在HashMap注释中写了，出现的概率不择千万分之一，红黑树只是为了在极端情况下来保证性能）

**为什么还要有UNTREEIFY_THRESHOLD = 6**

* 起到一个缓冲作用。避免频繁的进行树退化为链表的操作，因为退化也是有开销的，当我们移除一个红黑树上的值的时候，如果只有阈值8的话，那么它会直接退化，我们若再添加一个值，它有可能又需要变为红黑树了，添加阈值6相当于添加了一个缓冲



**HashMap容量为什么是2的n次方**

1. 首先2的幂次违背了算法导论中“不建议采用2的幂次作为除数”因为这样很容易导致哈希冲突的发生，但是hash函数的设计减少了这种冲突，这种做法的效果与算法导论上的方式几乎无差别

2. 同时计算table数组下标时，&运算比%的效率更高

   * 需要说明的第一点就是为什么%运算能转化成&运算

   * 第二点就是&运算为什么比%运算更高效

3. 扩容时后的逻辑更加简单（避免了重新计算节点hash值）

**HashMap的哈希函数**

* 通过hashCode()的高16位和低16位的异或值实现的
* 哈希函数这样设计是经过了综合考量的，符合了哈希函数的设计原则（简单、计算快、随机、哈希碰撞少），由于table大小采用的是2的幂次，模运算时候只有低位参与运算，采用这种哈希方式，不会因而高位没有参与下标运算而造成碰撞，使用异或运算好处就是当某一个bit发生变化时，hash函数返回值也会发生变化，从而减少碰撞
* 不直接使用hashCode()处理后的哈希值作为数组下标是因为值的范围很大，数组取不到这么大的空间



**HashMap的key设计**

* 两个对象相等，则hashcode一定也是相同的
* 两个对象相等，那么使用equals方法一定会返回true
* 两个对象hashcode都相等，那么这两个对象不一定相等

* 因此hashCode和equals方法都要同时重写
* 如果key只重写了hashCode，却没有重写equals方法，那么equals默认是判断对象是否为同一个对象，那么会造成不同对象虽然值相同，但是会被认为是哈希碰撞
* 如果重写了equals方法而没有重写hashCode方法，equals执行速度会相对较慢



**比较节点时为什么先比较key的hash然后才比较key**

* 处于性能方面的一个考虑，比较equals可能会需要一定的时间开销，如果先比较key，那么key不相同则节点一定不相同此时则可以跳过比较key这一个过程



#### HashMap1.7

1.7与1.8主要有3点区别



* 哈希函数设计

1.7使用了9次函数扰动（4次位运算和5次异或）

1.8使用了2次函数扰动（1次位运算和1次异或）



* 数据结构

1.7 采用了数组+链表解决哈希冲突

1.8采用了数组+链表+红黑树来解决哈希冲突



* 扩容

1.7resize需要重新计算所有哈希值

1.8resize则省略该过程



* 插入链表的方式

1.7链表采用了头插法，并发下容易导致环形链表

1.8链表采用了尾插法，避免了环形链表的产生，但是还是线程不安全





#### 线程安全问题

**为什么HashMap线程不安全**

* JDK7使用尾插法，容易导致扩容时发生死循环
* 并发put操作时，可能会导致元素丢失



**如何解决？**

使用线程安全的Map，比如ConcurrentMap、HashTable



[JDK8 HashMap源码行级解析](https://www.cnblogs.com/allmignt/p/12353727.html#ijS57sM7)

[JDK7 HashMap](https://blog.csdn.net/carson_ho/article/details/79373026)

[头插法导致的死循环图解](https://my.oschina.net/u/4163222/blog/4750816)





### HashTable



**基本信息**

```java
public class ConcurrentHashMap<K,V> extends AbstractMap<K,V>
    implements ConcurrentMap<K,V>, Serializable {
```





### LinkedHashMap

**基本信息**

```java
// 继承了HashMap
// 内部维护了双向链表，用来维护插入顺序或LRU顺序
public class LinkedHashMap<K,V>
    extends HashMap<K,V>
    implements Map<K,V>
{
    /**
     * The head (eldest) of the doubly linked list.
     */
    transient LinkedHashMap.Entry<K,V> head;

    /**
     * The tail (youngest) of the doubly linked list.
     */
    transient LinkedHashMap.Entry<K,V> tail;
    /**
     * false表示维护的是插入顺序
     * true表示维护的是LRU顺序
     */
    final boolean accessOrder;
    
    static class Entry<K,V> extends HashMap.Node<K,V> {
        Entry<K,V> before, after;
        Entry(int hash, K key, V value, Node<K,V> next) {
            super(hash, key, value, next);
        }
    }
}
```



**put操作**

```java
// 首先会调用HashMap中的putVal函数
// 插入完成后，会调用LinkedHashMap的afterNodeAccess函数
// 如果指定LRU顺序，那么每次访问完该结点，就会把结点放在链表的尾部，表示最近访问结点，首结点也就即最久未被访问的结点
void afterNodeAccess(Node<K,V> e) { // move node to last
    LinkedHashMap.Entry<K,V> last;
    if (accessOrder && (last = tail) != e) {
        LinkedHashMap.Entry<K,V> p =
            (LinkedHashMap.Entry<K,V>)e, b = p.before, a = p.after;
        p.after = null;
        if (b == null)
            head = a;
        else
            b.after = a;
        if (a != null)
            a.before = b;
        else
            last = b;
        if (last == null)
            head = p;
        else {
            p.before = last;
            last.after = p;
        }
        tail = p;
        ++modCount;
    }
}
```





```java
// 在put的最后进行afterNodeInsertion
// 当removeEldestEntry返回true时会移除最晚的结点，也就是链表头部
void afterNodeInsertion(boolean evict) { // possibly remove eldest
    LinkedHashMap.Entry<K,V> first;
    if (evict && (first = head) != null && removeEldestEntry(first)) {
        K key = first.key;
        removeNode(hash(key), key, null, false, true);
    }
}
// 默认返回false，需要继承LinkedHashMap来重写方法
// 可以用来实现LRU缓存
protected boolean removeEldestEntry(Map.Entry<K,V> eldest) {
	return false;
}
```



**LRU缓存**

```java
public class myLinkedHashMap {
    public static void main(String[] args) {
        // LRU算法
        Map<Integer, String> ma = new Cache(3);
        ma.put(1, "1");
        ma.put(2, "2");
        ma.put(3, "3");
        System.out.println(ma.size());
        ma.put(4, "4");
        System.out.println(ma.size());
        System.out.println(ma.get(1));
        System.out.println(ma.get(2));
        System.out.println("LRU的顺序");
        // 3 4 2
        for (Integer key : ma.keySet()) {
            System.out.println(key);
        }
    }

    static class Cache extends LinkedHashMap {
        private final int maxEntry;
        Cache(int maxEntry) {
            super(maxEntry, 0.75f, true);
            this.maxEntry = maxEntry;
        }

        @Override
        protected boolean removeEldestEntry(Map.Entry eldest) {
            return size() > maxEntry;
        }
    }
}
```





### TreeMap

* 基于红黑树实现
* 取出的键值对有序
* 线程不安全
* key不能为null





**put操作**

```java
public V put(K key, V value) {
    Entry<K,V> t = root;
    // 根节点为空
    if (t == null) {
        compare(key, key); // type (and possibly null) check

        root = new Entry<>(key, value, null);
        size = 1;
        modCount++;
        return null;
    }
    int cmp;
    Entry<K,V> parent;
    // split comparator and comparable paths
    Comparator<? super K> cpr = comparator;
    // 基于Comparator来比较并且进行查找
    if (cpr != null) {
        // 二叉树查找
        do {
            parent = t;
            cmp = cpr.compare(key, t.key);
            if (cmp < 0)
                t = t.left;
            else if (cmp > 0)
                t = t.right;
            else
                // key存在，直接将原来的value进行覆盖
                return t.setValue(value);
        } while (t != null);
    }
    // 基于key的大小来进行比较与插入
    else {
        if (key == null)
            throw new NullPointerException();
        @SuppressWarnings("unchecked")
        Comparable<? super K> k = (Comparable<? super K>) key;
        do {
            parent = t;
            cmp = k.compareTo(t.key);
            if (cmp < 0)
                t = t.left;
            else if (cmp > 0)
                t = t.right;
            else
                return t.setValue(value);
        } while (t != null);
    }
    // 找到插入位置的父节点，与父节点进行比较然后插入
    Entry<K,V> e = new Entry<>(key, value, parent);
    if (cmp < 0)
        parent.left = e;
    else
        parent.right = e;
    fixAfterInsertion(e);
    size++;
    modCount++;
    return null;
}
```









### WeakHashMap

WeakHashMap的Entry继承自WeakReference，被WeakReference关联的对象在下一次垃圾回收时会被回收，通常用于实现缓存

```java
// 引用队列
private final ReferenceQueue<Object> queue = new ReferenceQueue<>();
```







### ConcurrentHashMap



使用ConcurrentHashMap的原因

* HashMap不是线程安全，在多线程环境下，使用put操作会引起死循环
* HashTable使用synchronized来保证线程安全，但是在线程竞争激烈的情况下HashTable效率十分低下，当一个线程访问HashTable的同步方法，其它线程也访问时，会进入阻塞或轮询状态，比如，线程1使用put操作时，线程2不但不能使用put方法添加元素，也不能使用get方法获取元素，效率低







#### 数据结构

同HashMap类似，使用了Node和TreeNode来封装键值对，不同的是CHM的table使用了volatile关键字，保证了可见性，同时还有一个关键的属性sizeCnt

```java
    /**
     * Table initialization and resizing control.  When negative, the
     * table is being initialized or resized: -1 for initialization,
     * else -(1 + the number of active resizing threads).  Otherwise,
     * when table is null, holds the initial table size to use upon
     * creation, or 0 for default. After initialization, holds the
     * next element count value upon which to resize the table.
     */
    private transient volatile int sizeCtl;
大意就是sizeCtl是用来指示table数组的初始化状态或者扩容大小的
    当为负数时表示table数组正在被初始化或者扩容，
    -1表示初始化
    -（1 + 正在扩容的线程数）
    为0表示table数字为空，创建时会使用默认初始化大小16
    初始化后，sizeCtl持有下次扩容需要扩容的大小
```





#### 实现原理

* JDK7中，ConcurrentHashMap由Segment数组结构和HashEntry数据结构组成，Segment继承了ReentrantLock扮演锁的角色，ConcurrentHashMap采用了分段的方式，每一把锁用于锁容器其中的一部分数据，多线程访问容器不同数据段的数据时，线程间就不会存在锁竞争的问题，从而有效提高了并发访问效率

* JDK8中，ConcurrentHashMap在数据结构选用了与HashMap相同的数据结构：数组+链表+红黑树，在锁的实现上，抛弃了Segment分段锁，改用了CAS+synchronized的方式，实现了更低粒度的锁
  * synchronized引入了大量的优化。
  * 减少内存开销，每个节点都需要重入锁，那么需要继承AQS，然而不是所有节点都需要同步支持，一般链表头节点才需要同步，这样做会减少内存带来的开销



#### **put操作**



**JDK7**



**JDK8**



```java
final V putVal(K key, V value, boolean onlyIfAbsent) {
    if (key == null || value == null) throw new NullPointerException();
    int hash = spread(key.hashCode());
    int binCount = 0;
    // 死循环执行，保证最后可以插入成功
    for (Node<K,V>[] tab = table;;) {
        Node<K,V> f; int n, i, fh;
        if (tab == null || (n = tab.length) == 0)
            // table 需要初始化
            tab = initTable();
        // 获取对应下标节点，如果是空，直接插入
        else if ((f = tabAt(tab, i = (n - 1) & hash)) == null) {
            // CAS 进行插入
            if (casTabAt(tab, i, null,
                         new Node<K,V>(hash, key, value, null)))
                break;                   // no lock when adding to empty bin
        }
        // 如果 hash 冲突了，且 hash 值为 MOVED，说明是 ForwardingNode 对象（这是一个占位符对象，保存了扩容后的容器），table 正在扩容，当前线程参与帮助扩容
        else if ((fh = f.hash) == MOVED)
            tab = helpTransfer(tab, f);
        // 如果 hash 冲突了，且 hash 值不为 -1
        else {
            V oldVal = null;
            // 获取 f 节点（根结点）的锁，防止增加链表的时候导致链表成环
            synchronized (f) {
                // 如果对应的下标位置的节点没有改变
                if (tabAt(tab, i) == f) {
                    // 并且 f 节点的 hash 值大于等于 0
                    if (fh >= 0) {
                        // 链表初始长度
                        binCount = 1;
                        // 死循环，直到将值添加到链表尾部，并计算链表的长度
                        for (Node<K,V> e = f;; ++binCount) {
                            K ek;
                            if (e.hash == hash &&
                                ((ek = e.key) == key ||
                                 (ek != null && key.equals(ek)))) {
                                oldVal = e.val;
                                if (!onlyIfAbsent)
                                    e.val = value;
                                break;
                            }
                            Node<K,V> pred = e;
                            if ((e = e.next) == null) {
                                pred.next = new Node<K,V>(hash, key,
                                                          value, null);
                                break;
                            }
                        }
                    }
                    // 如果 f 节点的 hash 小于 0 并且 f 是树类型
                    else if (f instanceof TreeBin) {
                        Node<K,V> p;
                        binCount = 2;
                        if ((p = ((TreeBin<K,V>)f).putTreeVal(hash, key,
                                                              value)) != null) {
                            oldVal = p.val;
                            if (!onlyIfAbsent)
                                p.val = value;
                        }
                    }
                }
            }
            // 链表长度大于等于 8 时，将该节点改成红黑树
            if (binCount != 0) {
                if (binCount >= TREEIFY_THRESHOLD)
                    treeifyBin(tab, i);
                if (oldVal != null)
                    return oldVal;
                break;
            }
        }
    }
    // 判断是否需要扩容
    addCount(1L, binCount);
    return null;
}
public V put(K key, V value) {
    return putVal(key, value, false);
}
```

* 首先进入一个死循环，保证了最终一定能插入成功
* 如果table数组为空则初始化数组
* 如果table数组不为空，头结点为空那么采用CAS操作尝试插入，插入成功则直接退出循环
* 如果发生了hash冲突，那么对应的根节点hash值会被标记为MOVE（值为-1）状态，表示table正在扩容，当前线程会进入helpTransfer来帮助其它线程进行迁移操作
* 如果发生hash冲突，但是hash值不为MOVE状态，那么此时才使用synchronized加锁，锁对象为根节点，防止了链表插入结点时导致链表成环
* 如果根节点对应的下标没有变化，那么就可以插入该下标，下标变化了则重新进入循环
* 如果hash值大于等于0，那么采用死循环的方式直到结点插入链表尾部成功为止，同时统计链表结点个数
* 如果hash值小于0且跟根节点是树类型，那么采用红黑树方式插入结点
* 最后根据结点的个数，大于等于8且table数组大于等于64，则将该哈希桶变成红黑树
* 最后判断是否需要扩容





#### **initTable**



```java
private final Node<K,V>[] initTable() {
    Node<K,V>[] tab; int sc;
    while ((tab = table) == null || tab.length == 0) {
        if ((sc = sizeCtl) < 0)
            Thread.yield(); // lost initialization race; just spin
        else if (U.compareAndSwapInt(this, SIZECTL, sc, -1)) {，
            try {
                if ((tab = table) == null || tab.length == 0) {
                    int n = (sc > 0) ? sc : DEFAULT_CAPACITY;
                    @SuppressWarnings("unchecked")
                    Node<K,V>[] nt = (Node<K,V>[])new Node<?,?>[n];
                    table = tab = nt;
                    sc = n - (n >>> 2);
                }
            } finally {
                sizeCtl = sc;
            }
            break;
        }
    }
    return tab;
}
```



#### **helpTransfer**



```java
/**
* Helps transfer if a resize is in progress.
*/
final Node<K,V>[] helpTransfer(Node<K,V>[] tab, Node<K,V> f) {
    Node<K,V>[] nextTab; int sc;
    // 如果 table 不是空，且 node 节点是转移类型，数据检验
    // 且 node 节点的 nextTable（新 table） 不是空，同样也是数据校验
    // 尝试帮助扩容
    if (tab != null && (f instanceof ForwardingNode) &&
        (nextTab = ((ForwardingNode<K,V>)f).nextTable) != null) {
       // 根据 length 得到一个标识符号
        int rs = resizeStamp(tab.length);
       // 如果 nextTab 没有被并发修改 且 tab 也没有被并发修改
       // 且 sizeCtl < 0 （说明还在扩容）
        while (nextTab == nextTable && table == tab &&
               (sc = sizeCtl) < 0) {
           // 如果 sizeCtl 无符号右移 16 不等于 rs（sc 前 16 位如果不等于标识符，则标识符变化了）
           // 或者 sizeCtl == rs + 1 （扩容结束了，不再有线程进行扩容）
           // 或者 sizeCtl == rs + 65535（如果达到最大帮助线程的数量，即 65535）
           // 或者转移下标正在调整（扩容结束）
           // 结束循环，返回 table
            if ((sc >>> RESIZE_STAMP_SHIFT) != rs || sc == rs + 1 ||
                sc == rs + MAX_RESIZERS || transferIndex <= 0)
                break;
            // 如果以上都不是, 将 sizeCtl + 1（表示增加了一个线程帮助其扩容）
            if (U.compareAndSwapInt(this, SIZECTL, sc, sc + 1)) {
               // 进行转移
                transfer(tab, nextTab);
                // 结束循环
                break;
            }
        }
        return nextTab;
    }
    return table;
}
```





#### **transfer**



**大致流程**

```
1. 计算 CPU 核心数和桶个数得出每个线程要处理多少桶，小于 16 时该值为 16
2. 初始化 nextTable，长度为原来的两倍
3. 死循环转移过程，根据 finishing 变量来判断转移是否结束
    1. 进入一个 while 循环，并分配 table 数组中的一个桶给线程，初始值是 16，按从大到小的顺序进行分配，当拿到分配值后，进行 i -- 递减。这个 i 就是数组下标。循环中有一个 bound 变量，指的是当前线程此次循环可以处理的区间的最小下标，超过这个下标，就需要重新领取区间或者结束扩容。还有一个 advance 变量，指的是是否继续递减以转移下一个桶，如果为 false，说明当前桶还没有处理完
    2. 进入 if 判断，判断扩容是否结束，如果扩容结束，清空 nextTable，并更新 table，更新 sizeCtl。如果没完成，但已经无法领取区间，该线程退出该方法，并将 sizeCtl 减一，表示参与扩容的线程少一个。
    3. 如果没有完成任务，且 i 对应的桶为 null，尝试 CAS 插入占位符 ForwardingNode 对象，这样其他线程进行 put 时就可以感知到并参与到扩容中来
    4. 如果对应的桶不是空，有占位符，说明当前已经有线程正在对这个桶进行迁移，当前线程跳过这个桶
    5. 如果以上都不是，说明桶不空，且不是占位符，说明这个桶尚未被处理，当前线程就会开始处理这个桶
4. 在迁移桶的时候是对头节点上锁的，防止有其他线程插入数据，迁移过程与 HashMap 一致（resize 方法）
```



**源码**

```java
private final void transfer(Node<K,V>[] tab, Node<K,V>[] nextTab) {
    int n = tab.length, stride;
    // 将 length / 8 然后除以 CPU 核心数。如果得到的结果小于 16，那么就使用 16。
    // 这里的目的是让每个 CPU 处理的桶一样多，避免出现转移任务不均匀的现象，如果桶较少的话，默认一个 CPU（一个线程）处理 16 个桶
    if ((stride = (NCPU > 1) ? (n >>> 3) / NCPU : n) < MIN_TRANSFER_STRIDE)
        stride = MIN_TRANSFER_STRIDE; // subdivide range 细分范围 stridea：TODO
    // 新的 table 尚未初始化
    if (nextTab == null) {            // initiating
        try {
            // 扩容  2 倍
            Node<K,V>[] nt = (Node<K,V>[])new Node<?,?>[n << 1];
            // 更新
            nextTab = nt;
        } catch (Throwable ex) {      // try to cope with OOME
            // 扩容失败， sizeCtl 使用 int 最大值。
            sizeCtl = Integer.MAX_VALUE;
            return;// 结束
        }
        // 更新成员变量
        nextTable = nextTab;
        // 更新转移下标，就是 老的 tab 的 length
        transferIndex = n;
    }
    // 新 tab 的 length
    int nextn = nextTab.length;
    // 创建一个 fwd 节点，用于占位。当别的线程发现这个槽位中是 fwd 类型的节点，则跳过这个节点。
    ForwardingNode<K,V> fwd = new ForwardingNode<K,V>(nextTab);
    // 首次推进为 true，如果等于 true，说明需要再次推进一个下标（i--），反之，如果是 false，那么就不能推进下标，需要将当前的下标处理完毕才能继续推进
    boolean advance = true;
    // 完成状态，如果是 true，就结束此方法。
    boolean finishing = false; // to ensure sweep before committing nextTab
    // 死循环,i 表示下标，bound 表示当前线程可以处理的当前桶区间最小下标
    for (int i = 0, bound = 0;;) {
        Node<K,V> f; int fh;
        // 如果当前线程可以向后推进；这个循环就是控制 i 递减。同时，每个线程都会进入这里取得自己需要转移的桶的区间
        while (advance) {
            int nextIndex, nextBound;
            // 对 i 减一，判断是否大于等于 bound （正常情况下，如果大于 bound 不成立，说明该线程上次领取的任务已经完成了。那么，需要在下面继续领取任务）
            // 如果对 i 减一大于等于 bound（还需要继续做任务），或者完成了，修改推进状态为 false，不能推进了。任务成功后修改推进状态为 true。
            // 通常，第一次进入循环，i-- 这个判断会无法通过，从而走下面的 nextIndex 赋值操作（获取最新的转移下标）。其余情况都是：如果可以推进，将 i 减一，然后修改成不可推进。如果 i 对应的桶处理成功了，改成可以推进。
            if (--i >= bound || finishing)
                advance = false;// 这里设置 false，是为了防止在没有成功处理一个桶的情况下却进行了推进
            // 这里的目的是：1. 当一个线程进入时，会选取最新的转移下标。2. 当一个线程处理完自己的区间时，如果还有剩余区间的没有别的线程处理。再次获取区间。
            else if ((nextIndex = transferIndex) <= 0) {
                // 如果小于等于0，说明没有区间了 ，i 改成 -1，推进状态变成 false，不再推进，表示，扩容结束了，当前线程可以退出了
                // 这个 -1 会在下面的 if 块里判断，从而进入完成状态判断
                i = -1;
                advance = false;// 这里设置 false，是为了防止在没有成功处理一个桶的情况下却进行了推进
            }// CAS 修改 transferIndex，即 length - 区间值，留下剩余的区间值供后面的线程使用
            else if (U.compareAndSwapInt
                     (this, TRANSFERINDEX, nextIndex,
                      nextBound = (nextIndex > stride ?
                                   nextIndex - stride : 0))) {
                bound = nextBound;// 这个值就是当前线程可以处理的最小当前区间最小下标
                i = nextIndex - 1; // 初次对i 赋值，这个就是当前线程可以处理的当前区间的最大下标
                advance = false; // 这里设置 false，是为了防止在没有成功处理一个桶的情况下却进行了推进，这样对导致漏掉某个桶。下面的 if (tabAt(tab, i) == f) 判断会出现这样的情况。
            }
        }// 如果 i 小于0 （不在 tab 下标内，按照上面的判断，领取最后一段区间的线程扩容结束）
        //  如果 i >= tab.length(不知道为什么这么判断)
        //  如果 i + tab.length >= nextTable.length  （不知道为什么这么判断）
        if (i < 0 || i >= n || i + n >= nextn) {
            int sc;
            if (finishing) { // 如果完成了扩容
                nextTable = null;// 删除成员变量
                table = nextTab;// 更新 table
                sizeCtl = (n << 1) - (n >>> 1); // 更新阈值
                return;// 结束方法。
            }// 如果没完成
            if (U.compareAndSwapInt(this, SIZECTL, sc = sizeCtl, sc - 1)) {// 尝试将 sc -1. 表示这个线程结束帮助扩容了，将 sc 的低 16 位减一。
                if ((sc - 2) != resizeStamp(n) << RESIZE_STAMP_SHIFT)// 如果 sc - 2 不等于标识符左移 16 位。如果他们相等了，说明没有线程在帮助他们扩容了。也就是说，扩容结束了。
                    return;// 不相等，说明没结束，当前线程结束方法。
                finishing = advance = true;// 如果相等，扩容结束了，更新 finising 变量
                i = n; // 再次循环检查一下整张表
            }
        }
        else if ((f = tabAt(tab, i)) == null) // 获取老 tab i 下标位置的变量，如果是 null，就使用 fwd 占位。
            advance = casTabAt(tab, i, null, fwd);// 如果成功写入 fwd 占位，再次推进一个下标
        else if ((fh = f.hash) == MOVED)// 如果不是 null 且 hash 值是 MOVED。
            advance = true; // already processed // 说明别的线程已经处理过了，再次推进一个下标
        else {// 到这里，说明这个位置有实际值了，且不是占位符。对这个节点上锁。为什么上锁，防止 putVal 的时候向链表插入数据
            synchronized (f) {
                // 判断 i 下标处的桶节点是否和 f 相同
                if (tabAt(tab, i) == f) {
                    Node<K,V> ln, hn;// low, height 高位桶，低位桶
                    // 如果 f 的 hash 值大于 0 。TreeBin 的 hash 是 -2
                    if (fh >= 0) {
                        // 对老长度进行与运算（第一个操作数的的第n位于第二个操作数的第n位如果都是1，那么结果的第n为也为1，否则为0）
                        // 由于 Map 的长度都是 2 的次方（000001000 这类的数字），那么取于 length 只有 2 种结果，一种是 0，一种是1
                        //  如果是结果是0 ，Doug Lea 将其放在低位，反之放在高位，目的是将链表重新 hash，放到对应的位置上，让新的取于算法能够击中他。
                        int runBit = fh & n;
                        Node<K,V> lastRun = f; // 尾节点，且和头节点的 hash 值取于不相等
                        // 遍历这个桶
                        for (Node<K,V> p = f.next; p != null; p = p.next) {
                            // 取于桶中每个节点的 hash 值
                            int b = p.hash & n;
                            // 如果节点的 hash 值和首节点的 hash 值取于结果不同
                            if (b != runBit) {
                                runBit = b; // 更新 runBit，用于下面判断 lastRun 该赋值给 ln 还是 hn。
                                lastRun = p; // 这个 lastRun 保证后面的节点与自己的取于值相同，避免后面没有必要的循环
                            }
                        }
                        if (runBit == 0) {// 如果最后更新的 runBit 是 0 ，设置低位节点
                            ln = lastRun;
                            hn = null;
                        }
                        else {
                            hn = lastRun; // 如果最后更新的 runBit 是 1， 设置高位节点
                            ln = null;
                        }// 再次循环，生成两个链表，lastRun 作为停止条件，这样就是避免无谓的循环（lastRun 后面都是相同的取于结果）
                        for (Node<K,V> p = f; p != lastRun; p = p.next) {
                            int ph = p.hash; K pk = p.key; V pv = p.val;
                            // 如果与运算结果是 0，那么就还在低位
                            if ((ph & n) == 0) // 如果是0 ，那么创建低位节点
                                ln = new Node<K,V>(ph, pk, pv, ln);
                            else // 1 则创建高位
                                hn = new Node<K,V>(ph, pk, pv, hn);
                        }
                        // 其实这里类似 hashMap 
                        // 设置低位链表放在新链表的 i
                        setTabAt(nextTab, i, ln);
                        // 设置高位链表，在原有长度上加 n
                        setTabAt(nextTab, i + n, hn);
                        // 将旧的链表设置成占位符
                        setTabAt(tab, i, fwd);
                        // 继续向后推进
                        advance = true;
                    }// 如果是红黑树
                    else if (f instanceof TreeBin) {
                        TreeBin<K,V> t = (TreeBin<K,V>)f;
                        TreeNode<K,V> lo = null, loTail = null;
                        TreeNode<K,V> hi = null, hiTail = null;
                        int lc = 0, hc = 0;
                        // 遍历
                        for (Node<K,V> e = t.first; e != null; e = e.next) {
                            int h = e.hash;
                            TreeNode<K,V> p = new TreeNode<K,V>
                                (h, e.key, e.val, null, null);
                            // 和链表相同的判断，与运算 == 0 的放在低位
                            if ((h & n) == 0) {
                                if ((p.prev = loTail) == null)
                                    lo = p;
                                else
                                    loTail.next = p;
                                loTail = p;
                                ++lc;
                            } // 不是 0 的放在高位
                            else {
                                if ((p.prev = hiTail) == null)
                                    hi = p;
                                else
                                    hiTail.next = p;
                                hiTail = p;
                                ++hc;
                            }
                        }
                        // 如果树的节点数小于等于 6，那么转成链表，反之，创建一个新的树
                        ln = (lc <= UNTREEIFY_THRESHOLD) ? untreeify(lo) :
                            (hc != 0) ? new TreeBin<K,V>(lo) : t;
                        hn = (hc <= UNTREEIFY_THRESHOLD) ? untreeify(hi) :
                            (lc != 0) ? new TreeBin<K,V>(hi) : t;
                        // 低位树
                        setTabAt(nextTab, i, ln);
                        // 高位数
                        setTabAt(nextTab, i + n, hn);
                        // 旧的设置成占位符
                        setTabAt(tab, i, fwd);
                        // 继续向后推进
                        advance = true;
                    }
                }
            }
        }
    }
}
```







### Set接口

```java
public interface Set<E> extends Collection<E> {
    int size();
    boolean isEmpty();
    boolean contains(Object o);
    Iterator<E> iterator();
    Object[] toArray();
    <T> T[] toArray(T[] a);
    // set添加元素不是put是add方法
    boolean add(E e);
    boolean remove(Object o);
    boolean containsAll(Collection<?> c);
    boolean addAll(Collection<? extends E> c);
    boolean retainAll(Collection<?> c);
    boolean removeAll(Collection<?> c);
    void clear();
    boolean equals(Object o);
    int hashCode();
}
```





### HashSet

总结

* HashSet实现了Set接口
* 不保证迭代的顺序
* 允许元素为null
* 非同步
* 底层实际上是一个HashMap，value使用的都是一个相同的Object对象





### LinkedHashSet

总结

* 不保证迭代的顺序
* 允许元素为null
* 非同步
* 底层为LinkedHashMap



### TreeSet

总结

* 迭代是按顺序的
* 不允许元素为null
* 非同步
* 底层是TreeMap





### 快速失败和安全失败

快速失败（fail-fast）

* 在用迭代器遍历一个集合对象时，如果遍历过程中对集合对象内容进行了修改，则会抛出异常
* 原理：集合内部维护modCount字段，每当集合被修改时，modCount会发生改变，而迭代器在遍历时会与预期的modCount进行比较，如果不一致则会快速失败
* 场景：java.util包下的集合都是快速失败

安全失败（fail-safe）

* 与迭代器遍历的对象不同，采用安全失败机制的集合容器，会在复制原先的集合内容，再进行遍历
* 原理：迭代时是在集合的拷贝下完成的
* 缺点：不能保证遍历实时的一致性
* 场景：java.util.concurrent包下的容器都是安全失败的





### 总结

**ArrayList、LinkedList、Vector比较**

* LinkedList使用的是链表，ArrayList和Vector使用的是动态数组
* ArrayList扩容增长原来的0.5，Vector扩容增长原来的一倍
* Vector是线程安全的，ArrayList和LinkedList是线程不安全的



**HashMap、HashTable、TreeMap、LinkedHashMap大比较**

* 都实现了Map接口
* HashTable是线程安全的，其它是线程不安全的
* TreeMap和HashTable的key不允许为null
* JDK8的HashMap底层为数组链表+红黑树，而LinkedHashMap是继承了HashMap并且内部维护了一个双向链表
* TreeMap保证了迭代的顺序，其它都不保证



**选取Java集合框架方法**

* 根据存储的集合类型，如果为单列元素且允许重复就选择List，单列元素且不允许重复则选择Set，如果是映射则选择Map
* 根据是否需要线程同步，迭代是否有序、是否需要排序、增删改查的性能要求选择合适的集合
* 使用泛型，避免在运行时出现ClassCastException









## Java IO



### 文件操作

```java
public class File
    implements Serializable, Comparable<File>
{
    // 给出相对路径
    public String getPath() {
        return path;
    }
    
    // 给出项目目录+文件名的路径
    public String getAbsolutePath() {
        return fs.resolve(this);
    }
    
    // 列举所有文件
    public File[] listFiles() {}
    
    // 给出文件名
    public String getName() {}
    
    // 判断是否为文件
    public boolean isFile() {}
}
```









### 字节操作

![](C:\Users\Steven\Desktop\CS-Note\java\pic\IO.png)

**字节和字符？**

* 一个字符由多个字节组成（一个byte为1个字节，一个char为两个字节）

* 字节主要用于处理二进制，字符是用来处理文本和字符串（编码是将字符变成字节，常见的编码方式有UTF-8、GBK）

* 由于UTF-8中，中文字符占3位，英文字符占1位，为了能够让一个char保存一个中文或一个英文，因此char采用了UTF-16BE编码（Big Endian大端模式，也称为网络序，将低字节放在高地址）

* 处理字节的IO类有InputStream、OutputStream，处理字符的IO类有Reader、Writer



**装饰者模式**

Java IO采用了大量的装饰者模式来实现各个类，装饰者模式的目的是为了增强IO流的功能

* InputStream为抽象组件
* FileInputStream是InputStream的子类，是具体组件
* FilterInputStream是InputStream的抽象装饰者
* BufferedInputStream是FilterInputStream的子类，是具体装饰者，它为FileInputStream提供了缓存的功能



### 字符操作

* InputStreamReader实现从字节流解码为字符流
* OutputStreamWriter实现从字符流编码为字节流







### 对象操作

**概念**

* 序列化：将一个对象转化为字节流（ObjectOutputStream.writeObject()）
* 反序列化：将一个字节流转化为一个对象（ObjectInputStrea.readObject()）



**Serializable**

序列化的类需要实现Serializable接口，该接口为标识接口，没有任何方法，不实现该接口，序列化时会出现SerializationException异常



**transient**

使用了该关键字的属性序列化对象后，该属性不会被序列化，用于保证某些对象的属性是临时保存在内存，而不能被序列化，ArrayList中的elementDate数组也是被transient所修饰，因为该数组是动态拓展的，并不是所有空间都会被使用



### 网络操作

Java常用的网络操作有

* InetAddress：表明网络地址
* Socket：套接字连接
* Datagram：数据报通信
* URL：统一资源定位符





**Socket**

![](C:\Users\Steven\Desktop\CS-Note\java\pic\socket.png)

**服务端使用Socket**

```java
// 开启ServerSocket
ServerSocket ss = new ServerSocket(port)
// 进入监听，该步骤会进入阻塞
Socket s = ss.accept()

// 有客户端连接，使用输入流将信息写入，IO读写也会进入阻塞
s.getInputStream()
```



**客户端使用Socket**

```java
// 表明服务器地址和端口，并尝试连接
Socket s = new Socket(host, port)

// 连接成功后，向服务器发送数据
s.getOutStream()
```







### NIO

同步和异步？阻塞和非阻塞？

* 同步和异步是指进程与内核之间的交互，如果数据没有准备好，则进程需要等待直到数据准备好为止，这个过程就叫做同步，而异步进程并不需要去等待，如果数据准备好了之后那么就由内核去通知进程
* 阻塞和非阻塞是指进程就已就绪的数据进行的IO操作采取的不同措施，阻塞是指读写时进程会一直等待，而非阻塞方式下，函数会返回一个值，程序就可以继续运行



Java在JDK1.4引入了NIO（New IO），它的IO模型是非阻塞IO模型，弥补了传统IO的不足，提供了高速、面向块的IO



**流和块的概念**

* IO和NIO最大的区别就是数据传输和打包的方式，传统IO是以流形式来处理数据，而NIO是以块的形式来处理数据
* 面向流的IO一次处理一个字节的数据，因此面向流的IO速度慢
* 面向块的IO一次处理一个数据块，按块的方式处理数据显然比按流的方式处理数据要快，但是编程实现却没有传统IO的优雅和简单





**通道与缓冲区**

通道可以用来读取或者写入数据，通道与流不同的是，流只能在一个方向移动，而通道可以同时读写，常见的通道类

* FileChannel：从文件读取数据
* SocketChannel：通过TCP读取网络数据
* ServerSocketChannel：可以监听新进来的TCP连接，并为每一个连接建立一个SocketChannel



通道读写的数据都保存在了缓冲区，不能直接对通道读写数据，而是对缓冲区进行读写，缓冲区实质是一个数组，包括了以下类型

* IntBuffer
* ByteBuffer
* FloatBuffer
* DoubleBuffer
* CharBuffer
* LongBuffer
* ShortBuffer



使用步骤

* 从IO流中获取Channel
* 创建Buffer
* 将数据从Channel读取到ByteBuffer



缓冲区状态变量

* capacity：最大容量，始终不变
* position：当前已经读写的字节数
* limit：当前还可以读写的字节数

```java
// 初始化，此时position = 0， limit = capacity
ByteBuffer bb = ByteBuffer.allocate(capacity);

// 读写操作，position = n，limit没变
// limit = position， position = 0
bb.flip();

// position = 0， limit = capacity
bb.clear();
```







**选择器**

什么是选择器？

* Java的NIO是属于同步非阻塞模型，这种方式下，用户发起IO操作后会返回做别的事情，这就是非阻塞，同时还需要去不断询问IO操作是否完成，NIO实现了IO多路复用的Reator模型

* 所谓Reator模型是事件处理的一种模式，它要求了主线程只负责监听文件描述符上是否有事件发生，有的话就立即将该事件通知给工作线程，主线程并不做实质性的工作，读写数据、接收连接、处理客户请求都是在工作线程中完成的

* 而选择器Selector充当了询问的角色，Selector通过轮询的方式去监听多个通道Channel，通过配置监听通道Channel为非阻塞，当Channel事件未到达时，就会不进入阻塞状态而是继续轮询其它Channel，找到IO事件已经到达的Channel，从而实现一个线程监听多个事件

  



为什么使用选择器？应用场景

* 相比于传统IO来说，NIO最大的优点就是一个线程能处理多个事件，而不是一个线程处理一个事件
* 适用于IO密集型的应用，当有用户有多个IO请求时，NIO的非阻塞特性能够发挥优势



怎么使用？

* 创建选择器
* 将通道注册到选择器上，同时注册事件
* 监听事件
* 判断事件以及处理对应的事件





[JavaNIO](https://tech.meituan.com/2016/11/04/nio.html)





## JDK8版本特性



### Lambda表达式



### 接口增强



### Stream流





### CompletableFuture

