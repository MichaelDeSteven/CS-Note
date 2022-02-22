# Redis概述



## NOSQL与MySQL

### 关系型数据库

关系型数据库的特点是使用了表，每张表代表现实世界中的关系，表中的每个记录代表一个实例，格式一致，因此关系型数据库维护方便，支持SQL语言，可以用于较复杂的查询



### 为什么需要NOSQL

传统的关系型数据库面对云计算、大数据的时代具有性能的瓶颈，对于高并发下的性能读取，关系型数据库的性能瓶颈来源于IO，尽管通过分布式、集群、主从复制、读写分离等优化方式能使得MySQL有较大的性能提升，但是对于海量数据来说，关系型数据库仍然是力不从心，同时为了解决关系型数据库中表结构的僵化，缺乏灵活度，关系型数据库对于特定场景下的需求实现起来异常复杂的情况（比如做交集运算），因此出现了NOSQL





### NOSQL

NOSQL有两个含义在里面

* NO SQL，即非传统意义上关系型数据库
* No Only SQL，指不只是SQL语言



优点

* 灵活。
* 读写性能高。
* 某些查询方便。

NOSQL与关系型数据库首先最大的不同是，NOSQL并由于固定的表结构，而是使用键值对的方式来存储数据，且结构和数据类型可以不固定，具有灵活性，同时NOSQL的数据都是存储在内存当中，与关系型数据库相比，读写的性能更加高效，查询数据不使用SQL语言，在做交集运算会比SQL语言方便



## Redis介绍

REmote DIctionary Server(Redis) 全程为远程字典服务，是一种基于内存存储的高性能键值对数据库，据统计，Redis每秒可读11w次，写8w次，相比于关系型数据库的性能来说具有巨大的提升，它可以用于数据库、缓存、消息中间件等。它支持了多种数据结构、string、list、hash、set、zset，Resis还内置了复制、LUA脚本、LRU事件驱动、不同级别的持久化（RDB、AOF）、事务，并且通过了哨兵、自动分区提供了高可用性





[redis官方文档](https://redis.io/)



## Redis应用场景

### 计数器

可以对String进行自增和自减，适用于存储读写频繁的计数量	



### 缓存

将热点数据放在内存当中，使用特定的淘汰算法，来提高读写的性能



### 查找表



### 消息队列

利用List数据结构还有lpush和lpop可以实现发送和读取消息



### 分布式锁

可以使用setnx来实现一个分布式锁









## 配置及其常用操作



```shell
# 端口
port 6379

# 绑定主机地址
bind 127.0.0.1

# 设置数据库数量，默认16
databases 16

# 客户端连接
redis-cli

# 选择数据库
select

# 清空所有数据库的数据
flushall

# 清空该数据库的数据
flushdb
```







# 数据结构与对象



## String



``` shell
# 设置
set <key> <value>

# 获取
get <key>

# 获取子字符串，索引是从0开始的
getrange <key> <start> <end>
getrange name 0 -1等价于get name
getrange name 0 1获取name的子字符串[0,1]

# 获取字符串长度
strlen <key>

# 移除
del <key>

# 批量创建
mset [key value ...]

# 批量获取
mget [key ...]

# 追加
append <key> <string>

# 设置过期时间
expire <key> <seconds>

# 查看过期时间
ttl <key>

# 自增+自减
incr <key>
decr <key>
incrby <key> <increment>
decrby <key> <decrement>

# 将value关联到key，并给定过期时间
setex <key> <seconds> <value>

# key不存在时设置
setnx <key> <value>

# 原子操作的批量创建，仅当所有的key都不存在时才创建成功
msetnx [key value ...]

# 设置新值并返回旧值
getset <key> <value>
```



## List



```shell
# 向头部插入
lpush <key> <value>
# 向尾部插入
rpush <key> <value>

# 查看长度
llen <key>

# 查看list
lrange <key> <start> <stop>

# 移除头部元素
lpop <key>

# 移除尾部元素
lpop <key>
```







## Set



```shell
# 增
sadd <key> <member>

# 查
smembers <key> <member>
sismember <key> <member>

# 删
srem <key> <member>
```







## Hash



```shell
# 增
hset key field value

# 查
hget key field
hexists key field
hgeall key

# 删
hdel key field
```











## ZSet



```shell
# 增
zadd <key> <score> <member>

# 查
zrange <key> <start> <stop> [withscores]

# 删
zrem <key> <member>
```







## 数据结构

### SDS



#### **数据结构**

```c++
struct sdshdr {
    // 记录buf数组的长度是多少
    // 包括了已用长度+free
    int len;
    // 记录了buf数组未使用的字节数
    int free;
    char buf[];
}
```







#### SDS与C字符串

| SDS                                      | C字符串                                    |
| ---------------------------------------- | ------------------------------------------ |
| 可以在O(1)时间内获得字符串长度           | 获取字符串长度的复杂度为O（N）             |
| API是安全的，不会出现缓冲区溢出问题      | API是不安全的，可能会出现缓冲区溢出问题    |
| 可以存放二进制或者是文本数据             | 只能存放文本数据                           |
| 修改字符串长度N次，最多执行N次内存重分配 | 修改字符串长度N次，必然要执行N次内存重分配 |
| 可以使用部分<string.h>API                | 可以使用<sring.h>的全部API                 |



#### 常数复杂度获取字符串长度

数据结构中的len属性记录了SDS本身的长度，使用SLEN只需要常数时间的复杂度就能获取到字符串长度



#### 杜绝缓冲区溢出问题

len属性和free有效的避免了缓冲区溢出问题，当使用sdcat会先检查SDS的空间是否足够，如果不够则会先拓展SDS的大小，然后再执行sdcat操作



#### SDS内存分配策略

Redis作为数据库，在速度要求较高、数据被频繁读写的场合下，如果每次修改字符串长度都执行一次内存重分配，那么就会对性能产生影响，为了避免C字符串的这种缺陷，SDS通过了未使用空间来解除字符串长度和数组长度的关联，然后由free属性来管理未使用空间的方式来实现内存分配的优化策略，通过未使用空间，SDS实现了空间预分配和惰性空间释放两种优化策略



**空间预分配**

* 如果对SDS进行修改后，SDS的长度小于1m，那么会free和len会分配相同的长度，比如13字节的长度，buf数组实际上会分配13+13+1的字节
* 如果对SDS进行修改后，SDS长度大于1m，那么free会分配1m的大小，比如len的长度为30m，那么buf数组实际上会分配30m+1m+1b大小



**惰性空间释放**

当执行字符串缩短操作时，并不立即使用内存分配来回收缩短的空间，而是使用free属性来记录未使用空间，供将来使用。



#### 二进制安全

C字符串要求字符必须符合某种编码，且‘以\0’作为字符串的结尾，而SDS的使用的是字节数组，因此存放的是二进制数据，而且是以len属性来判断字符串结束，通过使用二进制安全SDS而不是C字符串，使得Redis不仅可以保存文本数据，还可以保存二进制



### 链表

#### 数据结构

```c++
typedef struct listNode {
    struct listNode *prev;
    
    struct listNode *next;
    
    void *value;
}

typedef struct list {
    listNode *head;
    listNode *tail;
    unsigned long len;
    // 节点值复制函数
    void *(*dup) (void *ptr);
    // 节点值释放函数
    void *(*free) (void *ptr);
    // 节点值对比函数
    void *(*match) (void *ptr, void *key);
}list
```



#### 特点

Redis的List底层数据结构使用了链表，Redis链表的特性可以总结如下

* 双端。每个节点可以获取到直接前驱节点和直接后继节点
* 无环。表头结点的prev和表尾节点的next都指向NULL
* 保存了头节点和尾节点。获取链表的头和尾只需通过head和tail指针
* 记录了链表长度。list结构的len属性记录了链表的长度
* 多态。链表结点使用了void*指针来存放节点值，并且可以通过list结构中的dup、free、match三个属性来设定特定类型的函数，因此链表可以存放不同类型的值





### 字典

字典在Redis的应用非常广泛，Redis的数据库就是使用字典作为底层实现的，对数据库的操作就是建立在对字典的操作上的。除了用来表示数据库之外，字典还是Hash的底层实现之一，当一个Hash包含的键值对比较多时，又或者键值对中的元素都是比较长的字符串时，Redis就会使用字典作为Hash的数据结构



#### **数据结构**

```c++
// Redis的字典结构
typedef struct dict {
    // 类型特定函数
    dictType *type;
    
    // 私有数据
    void *privdata;
    
    // 哈希表
    dictht ht[2];
    
    // rehash索引
    // rehash不进行时值为-1
    int trehashidx;
}
```



```c++
// 哈希表数据结构
typedef struct dictht {
    // 哈希表数组
    dictEntry **table;
    
    // 哈希表大小
    unsigned long size;
    
    // 哈希表大小掩码，用于计算索引值
    unsigned long sizemask;
    
    // 哈希表已有节点的数量
    unsigned long used;
}dictht;
```



```cpp
typedef struct dictEntry {
    void *key;
    
    union {
        void* val;
        uint64_tu64;
        int64_ts64;
    }
    struct dictEntry *next;
}dictEntry;
```



#### **哈希算法**

Redis使用的是MurmurHash2算法来计算键的哈希值，该算法的优点在于，即使输入的键是有规律的，算法仍然能给出一个很好地随机分布性，并且计算速度快。



#### **冲突解决**

Redis的哈希表采用的是链地址法来解决冲突，每一个相同的键的哈希节点都会组织成一个单链表，同时处于速度的考虑，单链表插入节点采用了头插法提高插入速度



#### **rehash**

为了让哈希表的负载因子维持在一个合理的范围之内，当哈希表保存的键值对数量太多或者太少时，程序需要对哈希表的大小进行相应的拓展或者收缩，拓展和收缩的操作通过rehash来完成，rehash的步骤如下

* 为字典的ht[1]哈希表分配空间，这个哈希表的空间取决于要执行的操作，以及ht[0]当前键值对的数量
  * 如果为拓展操作，那么ht[1]大小为第一个大于等于ht[0].size << 1的2^n
  * 如果为收缩操作，那么ht[1]大小为第一个大于等于ht[0].size的2^n
* 将保存在ht[0]的所有键值对rehash到ht[1]上面，rehash操作时，需要重新计算键的哈希值和索引值，然后将相应的键值对放在ht[1]哈希表的指定位置上
* 将ht[0]的键值对都迁移到了ht[1]以后，释放ht[0]，并将ht[1]和ht[0]进行交换





#### **渐进式rehash**

为了防止键值对过多，迁移时导致服务器的性能受影响，rehash操作是采用分多次、渐进式地将键值对进行迁移，渐进式rehash操作如下

* 字典中维持一个索引计数器变量rehashidx，并将其初始化为0，表示rehash正在进行
* rehash过程中，每次对字典执行操作外，还会顺带将ht[0]哈希表键值对迁移到ht[1]中
* 随着字典操作的不断执行，最终迁移完成，这时将rehashidx设置为-1，表示rehash操作完成
* rehash期间，字典的键值对一律会被添加到ht[1]，保证了ht[0]键值对数量只减不增
* rehash期间，查找键值对会首先到ht[0]查找，如果找不到会再到ht[1]查找



[美团针对Redis Rehash机制的探索和实践](https://tech.meituan.com/2018/07/27/redis-rehash-practice-optimization.html)



### 整数集合

整数集合是集合的底层实现之一，当一个集合只包含整数，且集合的元素数量不多时，那么Redis就会使用整数集合作为集合键的底层实现。



#### **数据结构**

```cpp
typedef struct intset {
    // 编码方式
    uint32_t encoding;
    // 长度
    uint32_t length;
    // 保存元素的数组
    int8_t contents[];
}
```



* eocoding决定了contents数组中元素的数据类型，它有int16_t，int32_t或者int64_t
* contents数组是一个有序的数组，不包含重复的元素



#### **升级**

当一个新元素插入整数集合中，并且这个新元素的长度比整数集合现有的所有元素类型都要长的时候，整数集合会先进行升级操作，然后才将新元素添加到整数集合当中。

升级并添加新元素共分三步进行

* 根据新元素的类型，拓展整数集合数组的大小，并为新元素分配空间
* 将底层数组所有的元素转化成与新元素相同的类型，并将类型转化后的元素放在正确的位置上，同时还要维护数组元素的有序性
* 将新的元素添加到底层数组当中



**好处**

* 提高灵活性：整数集合通过自动升级底层数组来适应新元素，因此可以随意将不同长度的数组添加到整数集合而不必担心出现类型错误。
* 节约内存：整数集合一个最简单的做法就是第一次就将底层数组的类型设置为int64_t，但是这样可能会出现浪费内存，采用升级的机制能够有效的节约内存





### 压缩列表

压缩列表是List和Hash的底层实现之一，它是Redis为了节约内存而开发出来的，它是由一系列特殊编码的连续内存块组成的顺序型数据结构，一个压缩列表可以包含任意多个entry，每个entry可以保存一个字节数组或者整数值



* 对于List，当一个List只包含少量列表项，并且这些列表项要么是长度短的字符串，要么是小整数值，那么Redis就会使用压缩列表来作为List的底层实现
* 对于Hash，当一个Hash只包含少量键值对，并且每个键值对的键和值要么是长度较短的字符串，要么就是小整数值，Redis也会使用压缩列表来作为哈希键的底层实现



#### **数据结构**

![](C:\Users\Steven\Desktop\CS-Note\redis\pic\zlist.png)



* zlbytes：记录zl占用的内存字节数，在对压缩列表进行内存重分配或者是计算zlend位置时使用
* zltail：记录压缩列表尾节点距离压缩列表起始地址有多少字节，通过该偏移量可以直接确定尾节点的地址
* zllen：计算zl包含的节点数量
* entry：节点长度由节点保存的内容决定，用于保存字节数组或者整数值
* zlend：值为0XFF，表示压缩列表的结尾



**zlentry**

![](C:\Users\Steven\Desktop\CS-Note\redis\pic\zlentry.png)

* previous_entry_length：保存这当前节点的直接前驱节点的长度，有两种类型
  * 1个字节。如果前驱节点的长度小于254，那么就是用1个字节来记录该长度
  * 5个字节。如果前驱节点的长度大于等于254，那么就会使用5个字节来记录，其中第一个字节会被设置为0xFE，而后面4个字节用来保存前一节点的长度
* encoding：记录节点content属性所保存的类型以及长度
  * 值的最高位不为11表示content为字节数组编码，数组长度为除去高两位后其它位的记录
  * 值的最高位为11表示content保存着整数值，整数值的类型和长度为除去高两位后其它位的记录
* content：负责保存节点的值，节点值可以是一个字节数组或者整数



**连锁更新**

当压缩列表中，有多个连续的长度介于250字节-253字节之间的节点e1-eN，当在表头插入一个大于等于254字节的节点，那么e1的previous_entry_length将会由原来的1字节变为5字节，而之后的节点也是如此，这样可能会引发N次内存重分配，而每次空间分配的最坏复杂度为O（N），也就是最坏的复杂度为O（N^2）

尽管连锁更新的复杂度高，但是它造成性能问题的概率低

* 首先，压缩列表要恰好有多个连续的、长度介于250-253字节的节点
* 其次，即使出现了连锁更新，只要被更新的节点数量不多，那么就不会影响性能



### 跳跃表

跳表是一种有序的数据结构，它通过在每个节点维持多个指向其他节点的指针，从而达到快速访问节点的目的。跳表节点查找的平均时间复杂度为O（logN），大部分情况下，跳表效率和平衡树相媲美，同时实现也比平衡树简单，因此使用跳表来替代平衡树。Redis使用跳表来作为有序集合的底层实现之一。如果有序集合的元素数量过多或者是元素成员是比较长的字符串时，Redis就会使用跳表作为有序集合的底层实现。



#### **数据结构**

```cpp
// 跳跃表节点
typedef struct zskiplistNode {
    // 层
    struct zskiplistLevel {
        // 前进指针
        struct zskiplistNode *forward;
        // 跨度
        unsigned int span;
    } level[];
    // 后退指针
    struct zskiplistNode* backward;
    // 分值
    double score;
    // 成员对象
    robj *obj;
}zskiplistNode;

// 跳跃表
typedef struct zskiplist {
    // 表头节点和表尾节点
    struct skiplistNode *header, *tail;
    // 表中节点的数量
    unsigned long length;
    // 表中层数最大的节点的层数
    int level;
}zskiplist;
```



跳跃表节点

* 层：Redis会随机为每个节点生成1-32的值来作为level数组的大小，层数越高，节点越少，访问的速度越快

* 前进指针：每一层都是一个有序的链表，前进指针就是用来指向同一层的下一个节点
* 后退指针：用于从表尾向表头访问节点
* 分值：double类型的浮点数，跳跃表的节点按分值进行排序
* 成员对象：指向一个字符串对象，如果分值相同的节点，则会按照成员对象在字典序的大小进行排序



跳跃表

* header：指向表头节点的指针
* tail：指向表尾节点的指针
* length：节点的数量
* level：节点中层数的最大值





## 对象

前面介绍了Redis的底层数据结构：SDS、链表、字典、压缩列表、跳跃表、整数集合

Redis并没有直接使用这些数据结构来实现键值对数据库，而是基于这些数据结构创建了一个对象系统，这个系统包含了字符串对象、列表对象、哈希对象、集合对象和有序集合对象这五种类型的对象，每个对象都用到了至少一种数据结构。使用对象的好处就是可以针对不同的使用场景来设置多种不同的数据结构来实现，从而优化对象在不同场景下的使用效率

Redis对象系统还实现了基于引用计数的内存回收机制，当某个对象不再被引用时，那么这个对象所占用的内存将会被自动释放。同时，利用引用计数还实现了对象共享机制，通过该机制，可以使得多个数据库键共享同一对象类节约内存



### 对象的类型和编码

Redis使用对象来表示数据库的键值对，每次创建一个新的键值对时，至少会创建两个对象，一个对象是用作key，另一个对象用作value



```cpp
struct redisObject {
    // 类型
    unsigned type:4;
    
    //编码
    unsigned encoding:4;
    
    // 底层数据结构的指针
    void *ptr;
    
    // 引用计数
    int refcount;
}
```





#### 类型



```shell
# 查询某个关键字的类型
type key
```



![](C:\Users\Steven\Desktop\CS-Note\redis\pic\redisObjType.png)



#### 编码

对象的底层数据结构实现是由encoding属性决定的

![](C:\Users\Steven\Desktop\CS-Note\redis\pic\redisObjEnc.png)



可以发现每个数据类型至少使用了两种不同的编码

```shell
# 查看对象使用的编码
object encoding key
```





### 字符串对象

String类型使用了三种编码，int、raw、embstr



* 如果字符串对象保存的是一个整数且该整数可以被long类型表示，那么编码类型就为int
* 如果字符串对象保存的是一个字符串且长度超过44字节，那么使用SDS来保存字符串的值，编码类型为raw
* 如果字符串长度小于44字节，那么就使用embstr编码来保存这个字符串



**embstr**

embstr是一种专门用来保存短字符串的一种优化编码方式，使用embstr编码由以下好处

* 由于embstr编码创建的内存块是一块连续的空间，因此减少了内存分配和释放的次数
* embstr编码的字符串对象所有数据都保存在了一块连续的内存中，因此可以更好利用缓存带来的优势



### 列表对象

列表对象使用了两种编码，压缩列表和链表



当同时满足下面两个条件时，会使用压缩列表作为底层数据结构实现，否则就使用链表

* 所有字符串的长度都小于64字节
* 字符串的数量不超过512个



### 集合对象

集合对象使用了两种编码，整数集合和字典

当同时满足下面两个条件时，会使用整数集合作为底层数据结构实现，否则就使用字典

* 所有元素为整数
* 元素的数量不超过512个







### 哈希对象

哈希对象使用了两种编码，压缩列表和字典

当同时满足下面两个条件时，会使用压缩列表作为底层数据结构实现，否则就使用字典

* 哈希对象保存的键值对的键和值长度都小于64字节
* 键值对数量小于512个



### 有序集合对象

有序集合的编码可以使用压缩列表或者跳表

当同时满足下面两个条件时，会使用压缩列表作为底层数据结构实现，否则就使用跳表

* 哈希对象保存的元素成员长度都小于64字节
* 元素数量小于128个



**跳表结合字典使用原因**

* 原因是为了综合这两个数据结构的优点

* 如果单独使用跳表，那么在进行根据成员查找分值的操作，复杂度就会从O（1）变成O（N）
* 如果单独使用字典，那么执行ZRANK、ZRANGE等命令，都需要将字典查找的元素进行排序，复杂度为O(NlogN)
* 为了让有序集合的查找和访问操作尽可能快，因此Redis同时使用这两种数据结构来实现有序集合



### 回收机制



C语言并不具备自动内存回收功能，所以Redis在对象系统中采用引用计数来实现内存回收机制





### 对象共享







# 单机数据库实现



## 数据库



### 数据结构

Redis服务器会将所有数据库都保存在redisServer数据结构当中



```cpp
struct redisServer {
    // 一个数组，保存服务器中所有数据库
    redisDb *db;
    // 数据库的个数，默认16
    int dnum;
}
```





### 数据库的键空间

Redis是一个键值对数据库，每个数据库都有一个字典，用来保存数据库的所有键值对，这个字典也被成为了键空间

```cpp
typedef struct redisDb {
    dict *dict;
}redis;
```





**常用操作**

```shell
get key
set key value
del key
dbsize
flushdb
randomkey
```





### 键的生存和过期时间



Redis提供键过期机制的原因就是因为内存是有限的，缓存中的所有键值对如果一直保存在内存当中，那么很可能就会OOM，因此将指定的键过期然后处理能够有效的腾出内存空间给其它有用的键所使用。



#### 设置过期时间

Redis有四种方式来设置键过期

```shell
expire <key> <ttl> 时间单位为秒
pexpire <key> <ttl> 时间单位为毫秒
expireat <key> <timestamp>
pexpireat <key> <timestamp>
```

Redis最终会将前面三种指令转化为pexpireat命令来执行



#### 保存过期时间

Redis数据库还会将所有键的过期时间保存在字典当中，过期字典的值是一个longlong类型的整数，是一个毫秒进度的时间戳，该字典也叫做过期字典

```cpp
typedef struct redisDb {
    dict *expires;
}redis;
```



执行pexpireat时，判断该键是否在键空间当中，如果存在那么会将该键关联到过期字典



#### 移除过期时间

```shell
persist <key>
```

用来解除键的过期时间，同时在过期字典将该键删除



#### 计算并返回键生存时间

```cpp
ttl <key>
```

* 检查指定键是否在键空间当中，如果存在再判断是否存在过期时间
* 如果存在过期时间则与当前的时间相减得到时间差
* 该时间差即为键的剩余生存时间



#### 过期键判定

* 检查指定键是否在过期字典当中，如果存在，那么取得键的过期时间
* 与当前时间戳比较，如果大于键过期时间说明过期，否则未过期



#### 过期键删除策略



* **定时删除**：在为每个键设置过期时间的同时设置一个定时器，若键过期后，就对该键执行立即删除
  * 这种方式能极大的节约内存空间，但是存在两个问题
  * 影响服务器的响应时间和吞吐量。如果过期键较多时，删除过期键可能会占用一部分CPU时间
  * 无法高效处理时间事件。设置定时器需要使用Redis的时间事件。而处理时间事件的方式是使用了无序链表，这样查找指定事件的复杂度将会是O(N)

* **惰性删除**：当过期键再次被访问时，才执行删除策略
  * 容易造成内存泄漏。过期键较多时，但是这些过期键又恰好没被访问时，会就造成大量过期键驻留在内存，导致内存浪费

* **定期删除**：每隔一段时间，就对数据库进行检查，删除过期键
  * 是定时和惰性删除的一种折衷方案
  * 缺点是需要有一个合理的执行删除操作的时长和频率，如果删除太频繁，那么就会退化成定时删除，对CPU造成负担，如果删除执行过少，就会退化成惰性删除，造成内存浪费



Redis删除过期键采用了惰性删除和定期删除策略：通过两种策略的搭配使用，能够在合理使用CPU和避免内存空间浪费之间取得平衡



**惰性删除策略实现**

Redis会对命令执行前调用expireIfNeeded函数对输入键进行检查

* 如果输入键过期，那么该函数就将输入键从数据库中删除
* 未过期则不采取操作



**定期删除策略实现**

Redis过期键的定期删除策略由activeExpireCycle函数实现。Redis会周期性调用该函数，会在规定时间内，分多次遍历数据库，随机选择一部分键检查过期时间，如果过期则删除，如果达到时间上限则停止处理



## RDB



```shell
# 阻塞Redis服务器进程，直到RDB文件创建完毕为止，阻塞期间不能处理任何命令请求
save
# 创建一个子进程，然后由子进程负责创建RDB文件，服务器进程可以继续处理命令请求
bgsave
```



* 如果服务器开启了AOF持久化功能，那么服务器会优先使用AOF文件来还原数据库状态
* 只有在AOF持久化功能处于关闭状态时，服务器才会使用RDB文件来还原数据库状态





## AOF



### 原理

除了RDB持久化功能外，Redis还提供了AOF持久化功能，与RDB持久化通过**保存数据库键值对**来记录数据库状态不同，AOF持久化是通过**保存Redis服务器所执行的写命令**来记录数据库的状态。



### 步骤



#### 追加

服务器在执行完一个写命令后，会以协议格式将被执行的写命令追加到服务器状态的aof_buf缓冲区的末尾



#### 写入与同步



Redis服务器进程是一个事件循环，文件事件负责接收命令请求以及发送命令回复，在处理文件事件时可能会执行写命令，这些命令会追加到aof_buf缓冲区中，每次都会调用相应的函数（flushAppedOnlyFile）然后根据不同的行为来处理AOF文件，该行为通过服务器配置的appendfsync决定



* always：每次事件循环都将缓冲区的所有命令写入并同步到AOF文件
* everysec：每次事件循环都将缓冲区所有命令写入AOF文件，并且每隔一秒子线程要对AOF文件进行一次文件同步
* no：每次事件循环都将缓冲区所有命令写入AOF文件，同步时机则由OS来决定



#### 载入与还原



Redis读取AOF文件并且还原数据库状态步骤如下

* 创建一个伪客户端
* 伪客户端从AOF中读取写命令并执行
* 当AOF文件的所有命令都被执行完毕则载入完毕



#### 重写

由于AOF是通过保存服务器执行的写命令来保证数据库状态，当时随着时间流逝，AOF文件可能体积会越来越大，因此提供了AOF文件重写功能，允许使用一个新的AOF文件来重写旧的AOF文件，新的AOF文件能够保证数据库当前状态的一致，且不包含了任何冗余命令





#### 后台重写

为了避免重写时，服务器进程被阻塞导致处理不了客户请求，因此Redis还提供了后台重写功能，但是为了保证数据一致性（子进程AOF重写期间，服务器处理的新的命令可能会对数据库状态进行修改），Redis服务器设置了AOF重写缓冲区，子进程在AOF重写期间，服务器做了以下步骤

* 执行客户端发来的命令
* 将执行后的命令写入缓冲区
* 将执行后的命令写入重写缓冲区
* 子进程完成重写工作后，会向父进程发送一个信号
* 父进程执行信号处理函数
  * 将重写缓冲区写入一个新的AOF文件
  * 将新的AOF文件原子覆盖现有的AOF文件，完成新旧AOF文件的替换

在子进程AOF重写期间，父进程不会被阻塞，只有当执行信号处理函数时，才会进入阻塞，因此后台重写将服务器性能的影响降到了最低





## 事件

Redis事件主要分两类，时间事件和文件事件



## 文件事件

![](C:\Users\Steven\Desktop\CS-Note\redis\pic\ae.png)

文件事件处理器的四个组成部分

* 套接字：文件事件是对套接字的抽象，每当一个套接字准备好执行连接、写入、读取、关闭等操作就会产生对应的文件事件
* IO多路复用程序：程序编译时会根据当前的系统选择性能最高的IO复用函数来作为底层的实现，该程序主要负责监听文件事件，并将相应的文件事件传送给文件事件分派器
* 文件事件分派器：根据文件事件不同的类型调用相应的事件处理器
* 事件处理器：主要有连接应答、命令请求、命令回复等



采用了IO复用+Reactor实现了单个线程并发处理多个事件的高性能网络通信程序





## 时间事件

Redis的时间事件主要分以下两类

* 定时事件
* 周期性时间



**实现**

事件的组织方式采用了无序链表，每当时间事件执行器运行时，就会遍历整个链表，查找已到达的事件，并调用相应的事件处理器



## 线程模型



### 单线程模型

Redis的文件事件使用的是单线程，因此Redis也被称为单线程模型，不使用多线程而使用单线程设计Redis的原因主要有以下几点

* 单线程编程方便、易维护，而并发编程需要有一定的并发编程基础，而且使用多线程需要涉及互斥锁，在某些情况下，锁可能会导致Redis性能损耗
* 单线程也具有并发处理多个事件的功能，Redis使用了IO多路复用模型，通过该模型使得单线程也具有并发监听多个事件的功能
* Redis的性能瓶颈不在CPU上，使用多线程编程是为了更加充分利用CPU资源，而Redis的性能瓶颈在于内存和网络而不是CPU，因此就没有必要使用多线程技术





### 多线程模型

严格来讲，Redis4.0之后实际上采用了多线程，这些后台线程主要用于处理一些较缓慢的操作，比如清理脏数据、删除较大的键。



Redis6.0以后真正引入了多线程

```shell
# 开启多线程
io-threads-do-reads yes
# 多线程数
io-threads 4 #官网建议4核的机器建议设置为2或3个线程，8核的建议设置为6个线程
```



引入原因

* 为了充分利用CPU资源
* 多线程可以分担服务进程处理某些缓慢操作的压力







# 多机数据库实现



## 复制



### 配置

主服务器配置文件

```shell
daemonize yes
port 6379
bind 0.0.0.0
timeout 300
databases 16
dbfilename dump-16379.db
dir ./redis-workdir
```

启动后的信息

```shell
# Replication
role:master
connected_slaves:0
master_replid:070eb97822a4172ae691a8fb933562d741edf9c8
master_replid2:0000000000000000000000000000000000000000
master_repl_offset:0
second_repl_offset:-1
repl_backlog_active:0
repl_backlog_size:1048576
repl_backlog_first_byte_offset:0
repl_backlog_histlen:0
```

从服务器配置文件

```shell
# 从服务器1
daemonize yes
port 16379
bind 0.0.0.0
timeout 300
databases 16
dbfilename dump-16379.db
dir ./redis-workdir
slaveof 127.0.0.1 6379

# 从服务器2
daemonize yes
port 26379
bind 0.0.0.0
timeout 300
databases 16
dbfilename dump-26379.db
dir ./redis-workdir
slaveof 127.0.0.1 6379
```

从服务器启动后的信息

```shell
# Replication
role:slave
master_host:127.0.0.1
master_port:6379
master_link_status:up
master_last_io_seconds_ago:4
master_sync_in_progress:0
slave_repl_offset:406
slave_priority:100
slave_read_only:1
connected_slaves:0
master_replid:ba3377b5f4295f29f42f18873b336ff45029a662
master_replid2:0000000000000000000000000000000000000000
master_repl_offset:406
second_repl_offset:-1
repl_backlog_active:1
repl_backlog_size:1048576
repl_backlog_first_byte_offset:1
repl_backlog_histlen:406
# Replication
role:slave
master_host:127.0.0.1
master_port:6379
master_link_status:up
master_last_io_seconds_ago:3
master_sync_in_progress:0
slave_repl_offset:490
slave_priority:100
slave_read_only:1
connected_slaves:0
master_replid:ba3377b5f4295f29f42f18873b336ff45029a662
master_replid2:0000000000000000000000000000000000000000
master_repl_offset:490
second_repl_offset:-1
repl_backlog_active:1
repl_backlog_size:1048576
repl_backlog_first_byte_offset:323
repl_backlog_histlen:168
```









## Sentinel





## 集群



### 方案

### 原理

### 总结





# 缓存



## 缓存穿透

概念：是指用户请求缓存中没有的数据，导致请求都直接到了数据库，如果请求量过大可能会压垮数据库



## 缓存击穿

概念：缓存中的某些热点Key一直扛着高并发的请求量，一旦缓存失效，那么这些请求就会击穿缓存，直接落在数据库上



## 缓存雪崩

概念：缓存在同一时间大面积失效，导致请求都直接落在数据库上



# 事务



# 发布和订阅









# 问题



五种基本数据类型的应用场景？

* String
  * 缓存
  * 计数器
  * 共享用户Session
* Hash
  * 键值对存储
* List
  * 消息队列
  * 文章列表或者数据分页展示
* Set
  * 可以用于集合的运算
  * 相比于HashMap来说，多台机器部署Set可以进行全局的去重
* ZSet
  * 排行榜



五种基本数据结构类型的底层实现





