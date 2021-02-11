

# JAVA基础



## 面向对象

面向对象的三大特性：封装、继承、多态



### 封装

利用抽象数据类型将数据和操作数据的方法封装在一起，使其成为一个独立的实体。数据被保护在抽象数据类型的内部，尽可能地隐藏内部细节，只保留一些接口使其与外部发生联系。用户无需对象内部细节

目的：减少耦合，提高了代码重用性



#### 访问修饰符

public：对所有类可见

protected：对同一包内所有类和子类都可见

default：对同一包内所有内可见

private：仅当前类

| 修饰符    | 当前类 | 同一包内 | 同一包内的继承类 | 不同包的继承类 | 其他包 |
| --------- | ------ | -------- | ---------------- | -------------- | ------ |
| public    | Y      | Y        | Y                | Y              | Y      |
| protected | Y      | Y        | Y                | Y              | N      |
| default   | Y      | Y        | Y                | N              | N      |
| private   | Y      | N        | N                | N              | N      |





#### 非访问修饰符

**static**：用来修饰方法和字段，表示类方法和类字段

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

#### // TODO 多态的实现原理



### 接口类和抽象类

#### 抽象类

抽象类和抽象方法用abstract关键字进行声明，如果一个类中包含抽象方法，那么这个类必须声明为抽象类。

抽象类和普通类的最大区别是，抽象类不能被实例化，需要继承抽象类才能实例化其子类



#### 接口

接口是抽象类的延伸，它可以看作是一个完全的抽象类，也即不能有任何方法的实现



比较抽象类和接口：

* 抽象类和接口都可用于实现面向对象中的运行时多态，增加程序的灵活性，接口是对Java多重继承的折中方案，Java中只存在一个父类，但是却可以实现多个接口

* 从语法上，Java 8之前接口内的方法不能有任何的实现，从Java 8开始使用关键字default能够拥有默认方法的实现，而抽象类内可以有普通方法和字段

* 接口成员的访问修饰默认且只有public，而抽象类的成员可以有多种访问权限

* 接口字段默认为static和final，而抽象类的字段没有限制

* 从设计层面上看，抽象类提供了一种IS-A的关系**是一种概念上的抽象，而接口则是对行为的抽象**



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

### 内置数据类型

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



#### 缓存池

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

#### 包装类

每个内置数据类型都有相应的包装类，基本数据类型转换为包装类称为自动装箱，反之为自动拆箱





### 引用数据类型

#### Object

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

**hashCode**

**toString**

**clone**





#### String

String、StringBuffer、StringBuilder位于java.lang包下

String的常用方法

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

**intern方法**

JDK8中intern方法解释为：字符串常量池存储着字符串，当调用该方法时，会从常量池查找是否含有该字符串，若存在则直接返回该字符串的地址，否则会在字符串常量池添加一个字符串，并返回该字符串的引用地址。

详见：JVM

**String的不可变性**

1. 方便缓存hash值。String的hash值经常被使用。不可变性特征可以使得hash值不可变，hash值只需计算一次
2. String Pool存储着字符串，字面量相同的字符串都会指向同一内存地址，在大量使用字符串情况下，可以节省内存，提高效率
3. String的不可变性天生具备线程安全

String、StringBuilder、StringBuffer

1. 可变性
   * String不可变
   * StringBuffer和StringBuilder可变
2. 线程安全
   * String和StringBuffer线程安全
   * StringBuilder不是线程安全





## 内部类

### 介绍



### 原因



### 分类







## 泛型

泛型本质就是类型参数化，使用泛型能对类型进行泛化，进而写出更加通用灵活的代码

### 擦除

与C++的模板不同的是Java在使用泛化时，擦除类型的信息，在泛型的内部代码无法获得任何有关泛型参数类型的信息，例如List<String>在运行时仅用一个List来表示，这样做的原因是为了泛型实现的一种折中，为了使得泛化的客户端可以用非泛化的类库来使用，即迁移兼容性，Java泛型不仅必须要支持向后兼容，还要保持之间的含义。



### 限定通配符

* ? extends T：继承某个类
* ？super T：自身或者父类



[10 道 Java 泛型面试题](https://cloud.tencent.com/developer/article/1033693)



## 反射

### 概念

反射是Java的特性之一，它允许运行时的Java程序获取自身的信息，并且可以操作类或对象的内部属性，它的思想就是万事万物皆对象，JVM将class文件装入内存后，为之创建的一个Class对象。通过Class对象来动态获取类的信息以及动态调用对象的方法称为java语言的反射机制



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





### 应用场景

反射是框架设计的灵魂，在实际开发设计中，都与反射都有很大的关系，比如动态代理使用了反射机制，Spring的IOC控制反转创建对象以及AOP的面向切面编程大量的使用了反射机制

* 反射还有一些其他方面的应用比如动态地读取配置文件从而达到无需对源码操作而是对配置文件修改即可，越过泛型检查

* 反射的优点是增加了代码的灵活性，利用反射使得我们可以在运行时才进行判断从而实现动态的类的加载
* 缺点首先是性能方面的问题，反射相当于一系列解释操作，通知JVM要做的事情，性能比Java代码慢很多
* 还有一点是安全问题，通过反射我们甚至可以直接对私有的方法或者字段进行操作，违反了面向对象的设计原则，增加了类安全隐患



## 动态代理

详见设计模式中的代理模式





## 异常





## 注解





## 网络编程







## Java版本特性







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
3. 两个空数组的区别是无参构造第一次add操作会直接扩容为默认大小为10的数组



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
    // 如果扩容容量小于minCapacity，则扩容为minCapacity
    if (newCapacity - minCapacity < 0)
        newCapacity = minCapacity;
    if (newCapacity - MAX_ARRAY_SIZE > 0)
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
3. 判断扩容为原来1.5倍的大小是否大于当前的最小容量
4. 如果小于当前最小容量，则采用最小容量作为新的数组大小
5. 调用Arrays的copyOf方法
6. copyOf则是调用了本地方法arraycopy，进行了数组的拷贝和扩容
7. 扩容完成后，再进行添加元素操作



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

// TODO



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
            // 从链表的第二个接待你开始遍历
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
* 否则哈希桶为链表，将链表分成高位链表和低位链表，分的依据是哈希值与旧容量进行与运算，结果为0在低位链表，否则为高位链表
* 链表分离使用了位运算的技巧
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

**HashMap容量为什么是2的n次方**

1. 从统计角度上讲2的n次方的数据分布均匀

2. 同时计算table数组下标时，&运算比%的效率更高

   * 需要说明的第一点就是为什么%运算能转化成&运算

   * 第二点就是&运算为什么比%运算更高效

3. 扩容时后的逻辑更加简单

**HashMap的哈希函数**

* 通过hashCode()的高16位和低16位的异或值实现的
* 哈希函数这样设计是经过了综合考量的，符合了哈希函数的设计原则，不会因而高位没有参与下标运算而造成碰撞，使用异或运算好处就是当某一个bit发生变化时，hash函数返回值也会发生变化，从而减少碰撞
* 不直接使用hashCode()处理后的哈希值作为数组下标是因为值的范围很大，数组取不到这么大的空间

**HashMap的key设计**

* hashCode和equals方法都要同时重写
* 如果key只重写了hashCode，却没有重写equals方法，那么equals默认是判断对象是否为同一个对象，那么会造成不同对象虽然值相同，但是会被认为是哈希碰撞
* 如果重写了equals方法而没有重写hashCode方法，那么也会造成我们认为相同的键值对，但是map认为是哈希碰撞，原因是我们认为相同的对象相同但是它的hashCode却不相同

**HashMap的1.7和1.8比较**

1. JDK1.7底层数据结构是数据链表，JDK8是数组链表+红黑树
2. JDK1.7的哈希函数较为复杂，而JDK8的哈希函数简单



[JDK8 HashMap源码行级解析](https://www.cnblogs.com/allmignt/p/12353727.html#ijS57sM7)





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
* 非同步
* key不能为null





### WeakHashMap

WeakHashMap的Entry继承自WeakReference，被WeakReference关联的对象在下一次垃圾回收时会被回收，通常用于实现缓存

```java
// 引用队列
private final ReferenceQueue<Object> queue = new ReferenceQueue<>();
```







### ConcurrentHashMap







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
* 底层实际上是一个HashMap，value为Object对象即也叫做dummy value





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







