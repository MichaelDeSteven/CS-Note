

# 性能检测与优化

![image-20201127150909978](C:\Users\Steven\AppData\Roaming\Typora\typora-user-images\image-20201127150909978.png)

## 网络

### 网络配置

作用：查看网口配置和收发数据的统计信息



```shell
ifconfig
ip
```

查看的信息

* IP地址
* 子网掩码
* MAC地址
* 网关地址
* MTU大小
* 网口状态
* 收发数据包统计信息
  * TX（发送数据）
  * RX（接收数据）
  * errors错误包
  * dropped丢包
  * overruns超限包



### Socket

```shell
netstat
-l 表示只显示状态为listen的socket
-n 表示不显示名字
-t 表示只显示tcp连接
-p 表示显示对应的进程信息
ss

```



查看信息

* 状态
* 本地地址
* 远端地址
* 进程PID和进程名称

其中Send-Q、Recv-Q在不同的状态有不同的含义

当socket状态处于Established

* Recv-Q表示socket缓冲区中还没有被应用程序读取的字节数
* Send-Q表示socket缓冲区还没有被确认的字节数

当socket状态处于listen

* Recv-Q表示全连接队列长度
* Send-Q表示全连接队列最大长度



### 查看网络性能

网络性能主要由以下几个方面衡量

* 带宽
* 吞吐量
* 时延
* 时延带宽积





### 网络吞吐率



```shell
# 查看网口信息
sar -n DEV
```



* rxpck/s：每秒接收的数据包
* txpck/s：每秒发送的数据包
* rxkB/s：每秒接收的速率
* txkB/s：每秒发送的速率



### 连通性和延时



```shell
ping
```



### 抓包



```shell
tcpdump [-adeflnNOpqStvx][-c<数据包数目>][-dd][-ddd][-F<表达文件>][-i<网络界面>][-r<数据包文件>][-s<数据包大小>][-tt][-T<数据包类型>][-vv][-w<数据包文件>][输出数据栏位]
# tcpdump -c 10 -q //精简模式显示 10个包
```





## top

查看整机的情况

动态侦测进程的状态

```shell
[root@study ~]# top [-d 数字] | top [-bnp]
选项与参数：
-d ：后面可以接秒数，就是整个进程画面更新的秒数。预设是 5 秒；
-b ：以批次的方式执行 top ，还有更多的参数可以使用喔！
 通常会搭配数据流重导向来将批次的结果输出成为文件。
-n ：与 -b 搭配，意义是，需要进行几次 top 的输出结果。
-p ：指定某些个 PID 来进行观察监测而已。
在 top 执行过程当中可以使用的按键指令：
? ：显示在 top 当中可以输入的按键指令；
P ：以 CPU 的使用资源排序显示；
M ：以 Memory 的使用资源排序显示；
N ：以 PID 来排序喔！
T ：由该 Process 使用的 CPU 时间累积 (TIME+) 排序。
k ：给予某个 PID 一个讯号 (signal)
r ：给予某个 PID 重新制订一个 nice 值。
q ：离开 top 软件的按键。

将 top 的信息进行 2 次，然后将结果输出到 /tmp/top.txt
[root@study ~]# top -b -n 2 > /tmp/top.txt
```



![image-20201127151503654](C:\Users\Steven\AppData\Roaming\Typora\typora-user-images\image-20201127151503654.png)

第一行为运行时间：开机到目前为止的时间：使用人数，平均工作负载（1，5，15分钟）表示正在平均要运行的进程数

第二行：总进程：正在运行进程：睡眠的进程：终止的进程：僵尸进程

第三行：CPU的整体负载，wa代表I/Owait

第三行：物理内存使用情况

第四行：swap使用情况

top下半部分为每个进程使用资源情况

* USER：该进程所属使用者
* PR：Priority的简写，越小越早被执行
* NI：Nice的简写，与Priority有关，越小越早被执行
* %CPU：CPU使用率
* %MEM：内存使用率
* TIME+：CPU使用时间的累加



uptime为top精简版，用于查看平均负载情况



## CPU



### vmstat

侦测系统资源变化

```shell
[root@study ~]# vmstat [-a] [延迟 [总计侦测次数]] <==CPU/内存等信息
[root@study ~]# vmstat [-fs] <==内存相关
[root@study ~]# vmstat [-S 单位] <==设定显示数据的单位
[root@study ~]# vmstat [-d] <==与磁盘有关
[root@study ~]# vmstat [-p 分区槽] <==与磁盘有关
选项与参数：
-a ：使用 inactive/active(活跃与否) 取代 buffer/cache 的内存输出信息；
-f ：开机到目前为止，系统复制 (fork) 的进程数；
-s ：将一些事件 (开机至目前为止) 导致的内存变化情况列表说明；
-S ：后面可以接单位，让显示的数据有单位。例如 K/M 取代 bytes 的容量；
-d ：列出磁盘的读写总量统计表
-p ：后面列出分区槽，可显示该分区槽的读写总量统计表

统计目前主机 CPU 状态，每秒一次，共计三次！
vmstat 1 3
```



* procs
  * r：运行的任务
  * b：阻塞的任务
* cpu
  * us
  * sy
  * id
  * wa
  * st





### mpstat

显示CPU的运行状态，这些信息存放在/proc/stat文件，在多CPU系统中，不但能查看所有CPU的平均状况信息，而且能够查看特定的CPU信息

```shell
[root@study ~]# mpstat
选项与参数：
-A ：等效于# mpstat -l ALL -u -P ALL
-I {SUM | CPU | ALL} ： 报告中断统计信息。 使用SUM关键字，mpstat命令报告每个处理器的中断总数。使用CPU关键字，显示CPU或CPU每秒接收的每个中断的数量。ALL关键字等效于指定上面的所有关键字，因此显示所有中断统计信息。
-P {cpu [，...] | ON | ALL} ： 指示要报告统计信息的处理器编号。cpu是处理器号。注意，处理器0是第一个处理器。 ON关键字表示将为每个在线处理器报告统计信息，而ALL关键字指示要为所有处理器报告统计信息。
参数
间隔时间：每次报告的间隔时间（秒）； 
次数：显示报告的次数。 

统计所有CPU，每2秒报告一次，一共报告3次
mpstat -P ALL 2 3
```

![image-20201127153924685](C:\Users\Steven\AppData\Roaming\Typora\typora-user-images\image-20201127153924685.png)

user：在internal时间段内，用户态的CPU时间

nice：在internal时间段内，nice值为负进程的CPU时间

system：在internal时间段内，内核态的CPU时间

iowait：在internal时间段内，硬盘IO等待时间

irq：在internal时间段内，硬中断时间

soft：在internal时间段内，软中断时间

idle：在internal时间段内，CPU除去等待磁盘IO操作外的因为任何原因空闲的时间闲置时间



## 内存





### free

用来显示内存状态

```shell
[root@study ~]# free [-b|-k|-m|-g|-h] [-t] [-s N -c N]
选项与参数：
-b ：直接输入 free 时，显示的单位是 Kbytes，我们可以使用 b(bytes), m(Mbytes)
 k(Kbytes), 及 g(Gbytes) 来显示单位喔！也可以直接让系统自己指定单位 (-h)
-t ：在输出的最终结果，显示物理内存与 swap 的总量。
-s ：可以让系统每几秒钟输出一次，不间断的一直输出的意思！对于系统观察挺有效！
-c ：与 -s 同时处理～让 free 列出几次的意思～

以mb为显示单位，每2秒输出内存使用情况，一共3次
free -m -s 2 -c 3
```







## 磁盘





# 文件与目录管理

#### ls

```shell
[root@study ~]# ls [-aAdfFhilnrRSt] 文件名或目录名称.. 
[root@study ~]# ls [--color={never,auto,always}] 文件名或目录名称.. 
[root@study ~]# ls [--full-time] 文件名或目录名称.. 
```



作用：展示文件夹内内容

参数：

-a ：全部的档案，连同隐藏档( 开头为 . 的档案) 一起列出来～ 

-d ：仅列出目录本身，而不是列出目录内的档案数据 

-l ：列出所有文件的属性，包含文件的权限ll 为 ls -l的别名

-R ：连同子目录内容一起列出来； 

-A ：全部的档案，连同隐藏档，但不包括 . 与 .. 这两个目录，一起列出来～ 

-f ：直接列出结果，而不进行排序 (ls 预设会以档名排序！) 

-S ：以档案容量大小排序

-t ：依时间排序 

-r ：将排序结果反向输出，例如：原本档名由小到大，反向则为由大到小； 

--color=never/auto/always/



#### cp

```shell
[root@study ~]# cp [-adfilprsu] 来源文件(source) 目标文件(destination) 
[root@study ~]# cp [options] source1 source2 source3 .... directory
```

作用：复制文件，建立快捷方式，复制整个目录

参数

-i  ：若目标文件(destination)已经存在时，在覆盖时会先询问动作的进行

-p  ：连同文件的属性(权限、用户、时间)一起复制过去，而非使用默认属性

-r  ：递归持续复制，用于目录的复制行为；

-s  ：复制成为符号链接文件 (symbolic link)，亦即『快捷方式』文件

-l  ：进行硬式连结(hard link)的连结档建立，而非复制文件本身



软链接硬链接

硬链接：创建一个数据结构用来指向文件的inode结点，此时inode结点引用次数+1，不能对目录进行链接

软链接：相当于快捷方式，指向文件所在的绝对路径，当文件被删除时，软链接会失效，因为记录的是绝对路径，因此软链接也可以用来指向目录

[软连接与硬链接的区别](https://blog.csdn.net/stupid56862/article/details/90785420)



#### rm

作用：移除文件

```shell
[root@study ~]# rm [-fir] 文件或目录 
```

参数

-f  ：就是 force 的意思，忽略不存在的文件，不会出现警告讯息； 

-r  ：递归删除





#### mv

作用：移动目录和文件，还可以用来更名(rename)

```shell
[root@study ~]# mv [-fiu] source destination 
[root@study ~]# mv [options] source1 source2 source3 .... directory 
```

参数

-f  ：force 强制的意思，如果目标文件已经存在，不会询问而直接覆盖； 

-i  ：若目标文件 (destination) 已经存在时，就会询问是否覆盖！ 

-u  ：若目标文件已经存在，且 source 比较新，才会更新 (update) 

#### 文件内容查看

* **cat**

  concatenate：使连接

  查看前几行

* **tac**

  cat反过来，意思为查看后几行

* **nl**等同于cat -n

  显示行号版的cat

* **more**

  翻页

  空格键 (space)：代表向下翻一页； 

  Enter：代表向下翻『一行』； 

  /字符串：代表在这个显示的内容当中，向下搜寻『字符串』这个关键词； 

  :f：立刻显示出文件名以及目前显示的行数； 

  q：代表立刻离开 more ，不再显示该文件内容。 

  b 或 [ctrl]-b ：代表往回翻页，不过这动作只对文件有用，对管线无用

* **less**

  [pagedown]：向下翻动一页； 

  [pageup]：向上翻动一页

  /字符串：向下搜寻『字符串』的功能； 

  ?字符串：向上搜寻『字符串』的功能； 

  n：重复前一个搜寻 (与 / 或 ? 有关！) 

  N：反向的重复前一个搜寻 (与 / 或 ? 有关！) 

   g：前进到这个资料的第一行去； 

  G：前进到这个数据的最后一行去 (注意大小写)

* **head**

  显示文件前几行

  ```shell
  [root@study ~]# head [-n number] 文件
  ```

  

* **tail**

  显示文件后几行

  ```shell
  [root@study ~]# tail [-n number] 文件
  ```

  

* **od**

  显示二进制文件





* **touch**

  修改文件时间或者创建新的文件

```shell
[root@study ~]# touch [-acdmt] 文件 
```





#### 查找与排序

* find

```shell
[root@study ~]# find [PATH] [option] [action]
与文件权限及名称有关的参数：
 -name filename：搜寻文件名为 filename 的文件；
 -size [+-]SIZE：搜寻比 SIZE 还要大(+)或小(-)的文件。这个 SIZE 的规格有：
 c: 代表 byte， k: 代表 1024bytes。所以，要找比 50KB
 还要大的文件，就是『 -size +50k 』
 -type TYPE ：搜寻文件的类型为 TYPE 的，类型主要有：一般正规文件 (f), 装置文件 (b, c),
 目录 (d), 连结档 (l), socket (s), 及 FIFO (p) 等属性。
 -perm mode ：搜寻文件权限『刚好等于』 mode 的文件，这个 mode 为类似 chmod
 的属性值，举例来说， -rwsr-xr-x 的属性为 4755 ！
 -perm -mode ：搜寻文件权限『必须要全部囊括 mode 的权限』的文件，举例来说，
 我们要搜寻 -rwxr--r-- ，亦即 0744 的文件，使用 -perm -0744，
 当一个文件的权限为 -rwsr-xr-x ，亦即 4755 时，也会被列出来，
 因为 -rwsr-xr-x 的属性已经囊括了 -rwxr--r-- 的属性了。
 -perm /mode ：搜寻文件权限『包含任一 mode 的权限』的文件，举例来说，我们搜寻
 -rwxr-xr-x ，亦即 -perm /755 时，但一个文件属性为 -rw-------
 也会被列出来，因为他有 -rw.... 的属性存在！

选项与参数：
4. 额外可进行的动作：
 -exec command ：command 为其他指令，-exec 后面可再接额外的指令来处理搜寻到的结果。
 -print ：将结果打印到屏幕上，这个动作是预设动作！
 
 
在当前目录找出文件名为passwd
find / -name passwd
在/home 目录下查找文件名为.Profile的文件，找到后删除
find /home -name .Profile -exec rm{} \ 


上次访问的时间 参数是 -atime
上次属性变更的时间 参数是 -ctime
上次内容变更的时间 参数是 -mtime

// 查找/home/you目录下60天以前修改过的内容的.txt文件
find /home/you -iname "*.txt" -mtime -60 -print

```

* sort：用于对文本文件各行进行排序

```shell
[root@study ~]# sort [option] 文件列表
选项与参数：
-f ：忽略大小写的差异，例如 A 与 a 视为编码相同；
-b ：忽略最前面的空格符部分；
-M ：以月份的名字来排序，例如 JAN, DEC 等等的排序方法；
-n ：使用『纯数字』进行排序(默认是以文字型态来排序的)；
-r ：反向排序；
-u ：就是 uniq ，相同的数据中，仅出现一行代表；
-t ：分隔符，预设是用 [tab] 键来分隔；
-k ：以那个区间 (field) 来进行排序的意思

```



#### 文件内容比较

* diff

```shell
[root@study ~]# diff [option] 文件1 文件2
-b ：忽略一行当中，仅有多个空白的差异(例如 "about me" 与 "about me" 视为相同
-B ：忽略空白行的差异。
-i ：忽略大小写的不同。
```



#### 文件内容统计

* wc

```shell
[root@study ~]# wc [option] 文件列表
-l ：仅列出行；
-w ：仅列出多少字(英文单字)；
-m ：多少字符；
```





### 目录操作

mkdir

rmdir

rm -rf

### 文件与目录的权限

#### Linux文件属性

![image-20201226212502003](C:\Users\Steven\AppData\Roaming\Typora\typora-user-images\image-20201226212502003.png)

第一列代表文件的类型和权限

* 第一个字符代表这个文件是：目录（d）、文件（-）或链接文件（l）、可存储文件（b）、串行端口设备（c）



Linux系统内文件有三种身份（拥有者、群组和其它人）每种身份都有三种权限（rwx），改变文件权限主要有三种命令chgrp、chown和chmod



#### chgrp

改变文件拥有组

```shell
[root@study ~]# chgrp [-R] dirname/filename ...
```



#### chown

改变文件拥有者

```shell
[root@study ~]# chown [-R] 账号名称 文件或目录 
[root@study ~]# chown [-R] 账号名称:组名 文件或目录
```





#### chmod

改变权限

owner/group/other拥有各自的rwx（read write execute）因此文件对应的权限字符为rwxrwxrwx

```shell
[root@study ~]# chmod [-R] xyz 文件或目录
xyz为掩码
```









### Linux磁盘管理



#### 常用工具

df：列出文件系统的整体磁盘使用量

```shell
[root@study ~]# df [-ahikHTm] [目录或文件名]
选项与参数：
-a ：列出所有的文件系统，包括系统特有的 /proc 等文件系统；(all)
-k ：以 KBytes 的容量显示各文件系统；
-m ：以 MBytes 的容量显示各文件系统；
-h ：以人们较易阅读的 GBytes, MBytes, KBytes 等格式自行显示；
-H ：以 M=1000K 取代 M=1024K 的进位方式；
-T ：连同该 partition 的 filesystem 名称 (例如 xfs) 也列出；(type)
-i ：不用磁盘容量，而以 inode 的数量来显示
```



du：评估文件系统的磁盘使用量

```shell
[root@study ~]# du [-ahskm] 文件或目录名称
选项与参数：
-a ：列出所有的文件与目录容量，因为默认仅统计目录底下的文件量而已。
-h ：以人们较易读的容量格式 (G/M) 显示；
-s ：列出总量而已，而不列出每个各别的目录占用容量；
-S ：不包括子目录下的总计，与 -s 有点差别。
-k ：以 KBytes 列出容量显示；
-m ：以 MBytes 列出容量显示；

```



#### 分区

lsblk 列出系统上的所有磁盘列表

blkid 列出装置的 UUID 等参数

parted 列出磁盘的分区表类型与分区信息

磁盘分区： gdisk/fdisk

partprobe 更新 Linux 核心的分区表信息



#### 磁盘格式化

XFS 文件系统 mkfs.xfs



#### 文件系统的挂载与卸载

mount

```shell
[root@study ~]# mount -a
[root@study ~]# mount [-l]
[root@study ~]# mount [-t 文件系统] LABEL='' 挂载点
[root@study ~]# mount [-t 文件系统] UUID='' 挂载点 # 鸟哥近期建议用这种方式喔！
[root@study ~]# mount [-t 文件系统] 装置文件名 挂载点
```



umount (将装置文件卸除)

```shell
[root@study ~]# umount [-fn] 装置文件名或挂载点
```



#### LVM

逻辑滚动条管理员，可以将几个实体的partations（或disk）透过软件组合成为看起来是一个独立的大磁盘（VG），然后将这个大磁盘经过分区成为可使用的分区槽（LV）最终挂载使用

* Physical Volume, PV物理卷

  pvcreate、pvscan、pvdisplay、pvremove

* Volume Group, VG卷组

  vgcreate、vgscan、vgextend、vgreduce、cgchange、vgremove

* Physical Extent, PE,实体块

  LVM最小的存储单元

* Logical Volume, LV逻辑卷

  lvcreate、lvscan、lvdisplay、lvextend、lvreduce、lvremove、lvresize

  





### 杂项

fuser：查询给定的文件或目录的用户或进程信息

```shell
[root@study ~]# fuser [-aceilmkuv] [目录或文件名]
选项与参数：
-a ：列出所有未被使用的文件
-l ：列出可用的信号
-m ：列出访问某文件系统或块设备的所有进程
-h ：以人们较易阅读的 GBytes, MBytes, KBytes 等格式自行显示；
-H ：以 M=1000K 取代 M=1024K 的进位方式；
-T ：连同该 partition 的 filesystem 名称 (例如 xfs) 也列出；(type)
-i ：interactive
-k：终止访问某文件的进程
-u：除了进程的PID之外，同时列出该进程的拥有者
-v：可以列出每个文件与进程还有指令的完整性
```



dd：建立大文件

```shell
[root@study ~]# dd if=/dev/zero of=/srv/loopdev bs=1M count=512
# if 表示input file，表示输出0的文件
# of 表示output file，表示接收0的文件
```



Linux字符串截取

```shell
# 假设有字符串var=http://www.aaa.com/123.htm
echo ${var#*//}
# #表示删除从左边开始第一个*//前面及其//
echo ${var##*/}
# ##表示删除从左边开始最后一个*/及其/
# %与#的方向正好相反
```







#### Linux转义

1. \和单引号忽略字符特殊含义
2. 双引号保留字符特殊含义





#### 解压压缩

tar：打包

```shell
[dmtsai@study ~]$ tar [-z|-j|-J] [cv] [-f 待建立的新檔名] filename... <==打包与压缩
[dmtsai@study ~]$ tar [-z|-j|-J] [tv] [-f 既有的 tar 檔名] <==察看檔名
[dmtsai@study ~]$ tar [-z|-j|-J] [xv] [-f 既有的 tar 檔名] [-C 目录] <==解压缩
选项与参数：
-c ：建立打包文件，可搭配 -v 来察看过程中被打包的档名(filename)
-t ：察看打包文件的内容含有哪些档名，重点在察看『档名』就是了；
-x ：解打包或解压缩的功能，可以搭配 -C (大写) 在特定目录解开
 特别留意的是， -c, -t, -x 不可同时出现在一串指令列中。
-z ：透过 gzip 的支持进行压缩/解压缩：此时档名最好为 *.tar.gz
-j ：透过 bzip2 的支持进行压缩/解压缩：此时档名最好为 *.tar.bz2
-J ：透过 xz 的支持进行压缩/解压缩：此时档名最好为 *.tar.xz
 特别留意， -z, -j, -J 不可以同时出现在一串指令列中
-v ：在压缩/解压缩的过程中，将正在处理的文件名显示出来！
-f filename：-f 后面要立刻接要被处理的档名！建议 -f 单独写一个选项啰！(比较不会忘记)
-C 目录 ：这个选项用在解压缩，若要在特定目录解压缩，可以使用这个选项。
其他后续练习会使用到的选项介绍：
-p(小写) ：保留备份数据的原本权限与属性，常用于备份(-c)重要的配置文件
-P(大写) ：保留绝对路径，亦即允许备份数据中含有根目录存在之意；
--exclude=FILE：在压缩的过程中，不要将 FILE 打包！

常用
解压 tar -zxvf 压缩包名
压缩一个tar.gz文件 tar -zcvf 压缩包名 压缩文件
```





#### systemctl



```shell
[root@study ~]# systemctl [command] [unit]
command 主要有：
start ：立刻启动后面接的 unit
stop ：立刻关闭后面接的 unit
restart ：立刻关闭后启动后面接的 unit，亦即执行 stop 再 start 的意思
reload ：不关闭后面接的 unit 的情况下，重载配置文件，让设定生效
enable ：设定下次开机时，后面接的 unit 会被启动
disable ：设定下次开机时，后面接的 unit 不会被启动
status ：目前后面接的这个 unit 的状态，会列出有没有正在执行、开机预设执行否、登录等信息等！
is-active ：目前有没有正在运作中
is-enable ：开机时有没有预设要启用这个 unit
list-units ：依据 unit 列出目前有启动的 unit。若加上 --all 才会列出没启动的。
list-unit-files ：依据 /usr/lib/systemd/system/ 内的文件，将所有文件列表说明。

```





#### wget

```shell
[root@study ~]# wget [-bc] url
b:后台下载
c:使用断点续传
```

