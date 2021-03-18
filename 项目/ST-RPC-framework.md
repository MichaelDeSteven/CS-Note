# 项目介绍





# 架构及其设计思路









# 详细实现







## 传输协议

**默认实现**

```
+---------------+---------------+-----------------+-------------+--------------+
|                                ST-RPC Package                                |
+---------------+---------------+-----------------+-------------+--------------+
|  Magic Number |  Package Type | Serializer Type | Data Length |    Options   |
|    4 bytes    |    1 bytes    |     1 bytes     |   1 bytes   |    1 bytes   |
+---------------+---------------+-----------------+-------------+--------------+
|                                    Data Bytes                                |
|                               Length: ${Data Length}                         |
+------------------------------------------------------------------------------+
```



* Magic Number：数据包表示字段，表示该数据包为协议头部类型，其固定值为0xBABE
* Package Type：数据包的类型字段，目前只定义了两种类型
  * 0表示请求包
  * 1表示响应包
* Serializer Type：数据部分使用的序列化算法字段
  * 0表示ProBuf算法
* Data Length：数据部分的大小字段，最大值为2^8-1（255）字节
* Options：选项字段，最多8个选项，每一个位域代表一个选项类型
  * 1 << 0表示无选项字段
  * 位域1 << 1表示数据扩充（Data Scaling），如果该位置为1，首部固定部分后面的3个字节（DS）与数据部分大小字段（D）共同组成数据部分的大小，大小为DS << 8 + D
  * 剩下7个字段待补充







## 序列化算法

为什么需要使用序列化，rpc是以二进制形式来传输数据，因此需要将Java对象变成二进制的形式，这个过程就叫做序列化，接收方接收到二进制数据需要将其转化为Java对象然后取得文本信息，这个过程就叫做反序列化





### ProtoBuf



[ProtoBuf官方文档](https://developers.google.com/protocol-buffers)









### Json





## 注册中心

采用了基于Nacos作为本项目的注册中心







## 网络传输



### Socket









### Netty







## 负载均衡



### 随机轮询算法



### 加权轮询算法









# 项目遇到的问题

## Socket

### 问题

客户端向服务端传输数据，结束后服务端出现java.net.SocketException: Connection reset异常



### 分析

出现该异常主要有以下几个原因

* 客户端重设了连接
* 更常见的原因是服务端在写入数据的时候，客户端就提前关闭了连接
* 当接收缓冲区还有未读的数据时，socket关闭





* 针对原因1可以先排除，客户端始终只连接一次，而不会发生重设

* 针对原因3，服务端读取数据时就已经把缓冲区的数据都读完了，所以原因3排除
* 原因2，我首先尝试让客户端写入完数据之后，睡眠不让其连接关闭，然后然服务端输出客户端发送的数据
* 结果为服务端将客户端数据完整输出，待客户端关闭连接后，服务端报异常
* 原因分析可能是客户端没有将输出流关闭，服务端阻塞等待数据，之后连接关闭，导致异常发生







### 解决方法

1. 一个简单的解决方案就是客户端发送完数据后就关闭输出流
2. 本质的原因就是TCP是面向流的，因此服务端并不清楚接收数据的大小，服务端因此会阻塞等待客户端的数据到来，如果客户端没有将输出流关闭，直接关闭连接，那么客户端就会抛出异常，因此服务端可以读取一个指定大小的数据流，然后服务端就不用阻塞等待，因此可以给传输数据规定一个协议头，协议头中记录该数据的大小以及信息，服务端就可以先读取大小固定的协议头，然后获取数据流的大小，通过这个协议头还可以顺带解决TCP粘包问题





[java.net.SocketException: Connection reset](https://stackoverflow.com/questions/62929/java-net-socketexception-connection-reset)





## Netty

[nioEventLoopGroup-2-1] WARN io.netty.util.ReferenceCountUtil - Failed to release a message: PooledUnsafeDirectByteBuf(freed)









```java
java.lang.OutOfMemoryError: Requested array size exceeds VM limit
	at io.netty.util.internal.PlatformDependent.allocateUninitializedArray(PlatformDependent.java:281)
	at io.netty.buffer.ByteBufUtil.getBytes(ByteBufUtil.java:898)
	at io.netty.buffer.ByteBufUtil.getBytes(ByteBufUtil.java:873)
	at io.netty.buffer.ByteBufUtil.getBytes(ByteBufUtil.java:865)
	at dgut.rpc.coder.socket.RpcDecoderImpl.decode(RpcDecoderImpl.java:66)
	at io.netty.handler.codec.ByteToMessageDecoder.decodeRemovalReentryProtection(ByteToMessageDecoder.java:501)
	at io.netty.handler.codec.ReplayingDecoder.callDecode(ReplayingDecoder.java:366)
	at io.netty.handler.codec.ByteToMessageDecoder.channelRead(ByteToMessageDecoder.java:276)
	at io.netty.channel.AbstractChannelHandlerContext.invokeChannelRead(AbstractChannelHandlerContext.java:379)
	at io.netty.channel.AbstractChannelHandlerContext.invokeChannelRead(AbstractChannelHandlerContext.java:365)
	at io.netty.channel.AbstractChannelHandlerContext.fireChannelRead(AbstractChannelHandlerContext.java:357)
	at io.netty.channel.DefaultChannelPipeline$HeadContext.channelRead(DefaultChannelPipeline.java:1410)
	at io.netty.channel.AbstractChannelHandlerContext.invokeChannelRead(AbstractChannelHandlerContext.java:379)
	at io.netty.channel.AbstractChannelHandlerContext.invokeChannelRead(AbstractChannelHandlerContext.java:365)
	at io.netty.channel.DefaultChannelPipeline.fireChannelRead(DefaultChannelPipeline.java:919)
	at io.netty.channel.nio.AbstractNioByteChannel$NioByteUnsafe.read(AbstractNioByteChannel.java:163)
	at io.netty.channel.nio.NioEventLoop.processSelectedKey(NioEventLoop.java:714)
	at io.netty.channel.nio.NioEventLoop.processSelectedKeysOptimized(NioEventLoop.java:650)
	at io.netty.channel.nio.NioEventLoop.processSelectedKeys(NioEventLoop.java:576)
	at io.netty.channel.nio.NioEventLoop.run(NioEventLoop.java:493)
	at io.netty.util.concurrent.SingleThreadEventExecutor$4.run(SingleThreadEventExecutor.java:989)
	at io.netty.util.internal.ThreadExecutorMap$2.run(ThreadExecutorMap.java:74)
	at io.netty.util.concurrent.FastThreadLocalRunnable.run(FastThreadLocalRunnable.java:30)
	at java.lang.Thread.run(Thread.java:748)
```





## Nacos

### 问题

Nacos开启一段时间后，占用了大量磁盘空间



### 分析

Nacos可能往磁盘写满了无效文件



### 解决方法











# 项目亮点





# 项目难点

