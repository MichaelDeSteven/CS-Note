# Netty从入门到实战



## 介绍



### 什么是Netty

Netty是一个基于NIO的网络通信框架，它隐藏了网络通信背后的复杂性，可以用来快速构建高性能的通信应用



下面是Netty技术和方法的特点

* 设计
  * 提供了阻塞和非阻塞多种接口
  * 简单强大的线程模型
  * 自带编码和解码器，解决TCP粘包/拆包问题
* 性能
  * 比核心Java API更好的吞吐量、低延时
  * 资源消耗少
  * 减少内存拷贝
* 安全
  * 完整的SSL/TLS支持







## 入门



### 服务端

使用ServerBootstrap来引导我们创建一个服务端，为此需要准备3个属性

* 线程组group：一般需要两个线程组，一个负责处理客户端的请求，另一个负责处理IO请求
* IO模型（BioServerSocketChannel/OioServerSocketChannel）
* ChannelHandler：自定义一个处理客户端的数据并返回给客户端



#### 创建服务端

```java
public final class HelloServer {

    private  final int port;

    public HelloServer(int port) {
        this.port = port;
    }

    private  void start() throws InterruptedException {
        // 1.bossGroup 用于接收连接，workerGroup 用于具体的处理
        EventLoopGroup bossGroup = new NioEventLoopGroup(1);
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        try {
            // 2.创建服务端启动引导/辅助类：ServerBootstrap
            ServerBootstrap b = new ServerBootstrap();
            // 3.给引导类配置两大线程组,确定了线程模型
            b.group(bossGroup, workerGroup)
                    // (非必备)打印日志
                    .handler(new LoggingHandler(LogLevel.INFO))
                    // 4.指定 IO 模型
                    .channel(NioServerSocketChannel.class)
                    .childHandler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        public void initChannel(SocketChannel ch) {
                            ChannelPipeline p = ch.pipeline();
                            //5.可以自定义客户端消息的业务处理逻辑
                            p.addLast(new HelloServerHandler());
                        }
                    });
            // 6.绑定端口,调用 sync 方法阻塞知道绑定完成
            ChannelFuture f = b.bind(port).sync();
            // 7.阻塞等待直到服务器Channel关闭(closeFuture()方法获取Channel 的CloseFuture对象,然后调用sync()方法)
            f.channel().closeFuture().sync();
        } finally {
            // 8.优雅关闭相关线程组资源
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }
    }
    public static void main(String[] args) throws InterruptedException {
        new HelloServer(8080).start();
    }

}
```



步骤

* 创建两个线程组
* 使用ServerBootstrap引导服务端的启动
* 配置线程组
* 指定IO模型
* 指定业务处理逻辑
* 绑定端口并调用sync方法阻塞
* 阻塞等待，直到服务器channel关闭
* 优雅地关闭线程组资源



#### 服务端ChannelHandler

```java
public class HelloServerHandler extends ChannelInboundHandlerAdapter {

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) {
        try {
            ByteBuf in = (ByteBuf) msg;
            System.out.println("message from client:" + in.toString(CharsetUtil.UTF_8));
            // 发送消息给客户端
            ctx.writeAndFlush(Unpooled.copiedBuffer("你也好！", CharsetUtil.UTF_8));
        } finally {
            ReferenceCountUtil.release(msg);
        }
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        // Close the connection when an exception is raised.
        cause.printStackTrace();
        ctx.close();
    }
}
```



* channelRead：用来处理客户端发送来的数据
* exceptionCaugh：处理客户端消息发生异常





### 客户端

使用Bootstrap来引导客户端

#### 创建客户端

```java
public final class HelloClient {

    private final String host;
    private final int port;
    private final String message;

    public HelloClient(String host, int port, String message) {
        this.host = host;
        this.port = port;
        this.message = message;
    }

    private void start() throws InterruptedException {
        //1.创建一个 NioEventLoopGroup 对象实例
        EventLoopGroup group = new NioEventLoopGroup();
        try {
            //2.创建客户端启动引导/辅助类：Bootstrap
            Bootstrap b = new Bootstrap();
            //3.指定线程组
            b.group(group)
                    //4.指定 IO 模型
                    .channel(NioSocketChannel.class)
                    .handler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        public void initChannel(SocketChannel ch) throws Exception {
                            ChannelPipeline p = ch.pipeline();
                            // 5.这里可以自定义消息的业务处理逻辑
                            p.addLast(new HelloClientHandler(message));
                        }
                    });
            // 6.尝试建立连接
            ChannelFuture f = b.connect(host, port).sync();
            // 7.等待连接关闭（阻塞，直到Channel关闭）
            f.channel().closeFuture().sync();
        } finally {
            group.shutdownGracefully();
        }
    }
    public static void main(String[] args) throws Exception {
        new HelloClient("127.0.0.1",8080, "你好,你真帅啊！哥哥！").start();
    }
}
```



步骤

* 创建一个线程组
* 使用Bootstrap来引导客户端
* 配置线程组(group)
* 确定IO模型(channel)
* 指定业务处理逻辑(childHandler)
* 调用connect方法连接服务器
* 等待连接关闭（阻塞，直到channel关闭）
* 优雅地关闭线程组



#### 客户端ChannelHandler

```java
public class HelloClientHandler extends ChannelInboundHandlerAdapter {

    private final String message;

    public HelloClientHandler(String message) {
        this.message = message;
    }

    @Override
    public void channelActive(ChannelHandlerContext ctx) {
        System.out.println("client sen msg to server " + message);
        ctx.writeAndFlush(Unpooled.copiedBuffer(message, CharsetUtil.UTF_8));
    }

    @Override
    public void channelRead(ChannelHandlerContext ctx, Object msg) {
        ByteBuf in = (ByteBuf) msg;
        try {
            System.out.println("client receive msg from server: " + in.toString(CharsetUtil.UTF_8));
        } finally {
            ReferenceCountUtil.release(msg);
        }
    }

    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) {
        cause.printStackTrace();
        ctx.close();
    }
}
```

重写的方法主要有

* channelActive：服务端与客户端建立后被调用的方法
* channelRead：用来处理服务端发送来的数据
* exceptionCaught：处理服务端消息发生异常





## Codec框架

codec的作用就是将字节数据与目标数据进行相互转换，因为网络中的信息是以字节流的形式传输的，Netty的codec由两部分组成：decoder（解码器）和encoder（编码器），解码器是将字节流转化为目标数据也就是处理入站数据，而编码器讲目标数据转化为字节流，即处理出站数据



### Decoder

主要分为两类

* 从字节流转化为消息（ByteToMessageDecoder和ReplayingDecoder）
* 从一种消息转化为另一种消息（MessageToMessageDecoder）





#### ByteToMessageDecoder

该类会缓存入站的数据直到准备好了用于处理，处理后的数据被添加到了List中，然后传递到下一个ChannelInboundHandler

​	

```java
public class ToIntegerDecoder extends ByteToMessageDecoder {  //1

    @Override
    public void decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out)
            throws Exception {
        if (in.readableBytes() >= 4) {  //2
            out.add(in.readInt());  //3
        }
    }
}
```





#### ReplayingDecoder

与ByteToMessageDecoder不同的是，该类会读取缓冲区的数据是否有足够的字节，如果足够则解码，不够则会停止解码



```java
public class ToIntegerDecoder2 extends ReplayingDecoder<Void> {   //1

    @Override
    public void decode(ChannelHandlerContext ctx, ByteBuf in, List<Object> out)
            throws Exception {
        out.add(in.readInt());  //2
    }
}
```





#### MessageToMessage

该类为参数化的类，参数类型决定了被解析的类型



```java
// 类签名
public class IntegerToStringDecoder extends MessageToMessageDecoder<Integer>
    
// 方法签名
protected void decode( ChannelHandlerContext ctx,
Integer msg, List<Object> out ) throws Exception
```



```java
public class IntegerToStringDecoder extends
        MessageToMessageDecoder<Integer> { //1

    @Override
    public void decode(ChannelHandlerContext ctx, Integer msg, List<Object> out)
            throws Exception {
        // intToString
        out.add(String.valueOf(msg)); //2
    }
}
```



#### 处理过大的帧

Netty针对处理过大的帧提供了TooLongFrameException，为了避免解码器缓存过多的数据而耗尽内存，可以在解码器设置一个最大字节阈值，如果超过则抛出TooLongFrameException异常，然后由译码器用户决定如何处理它



```java
public class SafeByteToMessageDecoder extends ByteToMessageDecoder {  //1
    private static final int MAX_FRAME_SIZE = 1024;

    @Override
    public void decode(ChannelHandlerContext ctx, ByteBuf in,
                       List<Object> out) throws Exception {
        int readable = in.readableBytes();
        if (readable > MAX_FRAME_SIZE) { //2
            in.skipBytes(readable);        //3
            throw new TooLongFrameException("Frame too big!");
        }
        // do something
    }
}
```





### Encoder

编码器是将出站的数据从一种格式转化为另一种格式，netty编码器有两种

* MessageToByteEncoder
* MessageToMessageEncoder



#### MessageToByteEncoder



```java
public class ShortToByteEncoder extends
        MessageToByteEncoder<Short> {  //1
    @Override
    public void encode(ChannelHandlerContext ctx, Short msg, ByteBuf out)
            throws Exception {
        out.writeShort(msg);  //2
    }
}
```

* 实现从Short转化为ByteBuf







#### MessageToMessageEndoer



```java
public class IntegerToStringEncoder extends
        MessageToMessageEncoder<Integer> { //1

    @Override
    public void encode(ChannelHandlerContext ctx, Integer msg, List<Object> out)
            throws Exception {
        out.add(String.valueOf(msg));  //2
    }
}
```



* 将Integer转化为String，并添加到MessageBuf









## ChannelHandler





### ChannelHandlerContext











### 空闲连接以及超时

检测空闲连接和超时是为了及时释放资源，常用的方法是通过发送消息来测试该连接，这种方式成为心跳机制，Netty提供了几个ChannelHandler实现此目的



| 名称                | 描述                                                         |
| ------------------- | ------------------------------------------------------------ |
| IdleStateHandler    | 如果连接时间闲置过长，则会触发IdleState事件，在ChannelInboundHandler中可以覆盖userEventTriggered方法来处理该事件 |
| ReadTimeoutHandler  | 在指定时间间隔内没有收到入站数据则会抛出ReadTimeoutException并关闭Channel。ReadTimeoutException可以通过覆盖ChannelHandler的exceptionCaught方法检测到 |
| WriteTimeoutHandler | 在指定时间间隔内没有收到出站数据则会抛出WriteTimeoutException并关闭Channel。ReadTimeoutException可以通过覆盖ChannelHandler的exceptionCaught方法检测到 |



* 下面心跳机制的实现

```java
public class IdleStateHandlerInitializer extends ChannelInitializer<Channel> {

    @Override
    protected void initChannel(Channel ch) throws Exception {
        ChannelPipeline pipeline = ch.pipeline();
        pipeline.addLast(new IdleStateHandler(0, 0, 60, TimeUnit.SECONDS));  //1
        pipeline.addLast(new HeartbeatHandler());
    }

    public static final class HeartbeatHandler extends ChannelInboundHandlerAdapter {
        private static final ByteBuf HEARTBEAT_SEQUENCE = Unpooled.unreleasableBuffer(
                Unpooled.copiedBuffer("HEARTBEAT", CharsetUtil.ISO_8859_1));  //2

        @Override
        public void userEventTriggered(ChannelHandlerContext ctx, Object evt) throws Exception {
            if (evt instanceof IdleStateEvent) {
                 ctx.writeAndFlush(HEARTBEAT_SEQUENCE.duplicate())
                         .addListener(ChannelFutureListener.CLOSE_ON_FAILURE);  //3
            } else {
                super.userEventTriggered(ctx, evt);  //4
            }
        }
    }
}
```







### 协议



#### 分隔符协议



| 名称                       | 描述                                             |
| -------------------------- | ------------------------------------------------ |
| DelimiterBasedFrameDecoder | 接收ByteBuf由一个或多个分隔符拆分，如NUL或换行符 |
| LineBasedFrameDecoder      | 接收ByteBuf以分割线结束，如"\n"和"\r\n"          |



#### 基于长度的协议



| 名称                         | 描述                       |
| ---------------------------- | -------------------------- |
| FixedLengthFrameDecoder      | 提取固定长度               |
| LengthFieldBasedFrameDecoder | 读取头部长度并提取帧的长度 |





### 序列化数据







### 编写大型数据



