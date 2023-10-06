## My-Rpc
### 项目介绍

本项目是基于[My-Network-Library](https://github.com/nishiwodelian/My-Network-Library)多线程网络库实现的分布式网络通信框架(RPC)。为分布式环境下服务器之间进行远程方法调用提供了一套接口，通过本框架可以方便快速地实现RPC方法调用。

项目使用Protobuf完成序列化和反序列化，使用ZooKeeper实现服务注册中心。



### 项目特点

- 研究实现了RPC远程过程调用
- 采用Protobuf数据序列化和反序列化协议
- 注册中心采用ZooKeeper分布式一致性协调服务
- 通信部分由[My-Network-Library](https://github.com/nishiwodelian/My-Network-Library)多线程网络库完成
- conf配置文件
- CMake构建项目集成编译环境

### 开发环境

- 操作系统：Ubuntu 20.04.5 LTS
- 编译器：g++ 9.4.0

### 项目构建

安装Cmake

```
sudo apt-get update
sudo apt-get install cmake
```

构建项目

```
mkdir build && cd build
cmake ..
make install
make
```

### 运行案例

```
cd ./bin
```

#### ./provider -i test.conf

服务提供者，从test.conf中读取服务端ip地址和端口号,ZooKeepter的ip地址和端口号

#### ./consumer -i test.conf

服务调用者，向服务端发起远程调用，从test.conf中读取ZooKeepter的ip地址和端口号





  

  
