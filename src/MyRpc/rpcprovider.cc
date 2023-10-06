#include "rpcprovider.h"
#include "rpcheader.pb.h"
#include "rpcapplication.h"
#include <string>
#include "Socket.h"
#include "zookeeperutil.h"

void RpcProvider::NotifyService(google::protobuf::Service *service){
     ServiceInfo service_info;

    // 获取了服务对象的描述信息
    const google::protobuf::ServiceDescriptor *pserviceDesc = service->GetDescriptor();
    // 获取服务的名字
    std::string service_name = pserviceDesc->name();
    // 获取服务对象service的方法的数量
    int methodCnt = pserviceDesc->method_count();

    // std::cout << "service_name:" << service_name << std::endl;
   // LOG_INFO("service_name:%s", service_name.c_str());

    for (int i=0; i < methodCnt; ++i)
    {
        // 获取了服务对象指定下标的服务方法的描述（抽象描述） UserService   Login
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        std::string method_name = pmethodDesc->name();
        service_info.m_methodMap.insert({method_name, pmethodDesc});

        //LOG_INFO("method_name:%s", method_name.c_str());
    }
    service_info.m_service = service;
    m_serviceMap.insert({service_name, service_info});
}

void RpcProvider::Run(){
    // 读取配置文件rpcserver的信息
    std::string ip = RpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(RpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());
    // 创建TcpServer对象
    Server *server = new Server(ip.c_str(), port);
    //写业务代码
    server->NewConnect(
        [](Connection *conn) {
            std::cout << "New connection fd: " << conn->GetSocket()->GetFd() << std::endl;
        }
    );
    server->OnMessage(
        [this](Connection *conn) {
            //std::cout << "message come! "<<std::endl;
            // 网络上接收的远程rpc调用请求的字符流    Login args
            std::string recv_buf = conn->ReadString();
            //std::cout<<recv_buf<<std::endl;
            // 从字符流中读取前4个字节的内容
            uint32_t header_size = 0;
            recv_buf.copy((char*)&header_size, 4, 0);
            // 根据header_size读取数据头的原始字符流，反序列化数据，得到rpc请求的详细信息
            std::string rpc_header_str = recv_buf.substr(4, header_size);
            MyRpc::RpcHeader rpcHeader;
            std::string service_name;
            std::string method_name;
            uint32_t args_size;
            if (rpcHeader.ParseFromString(rpc_header_str))
            {
                // 数据头反序列化成功
                service_name = rpcHeader.service_name();
                method_name = rpcHeader.method_name();
                args_size = rpcHeader.args_size();
            }
            else
            {
                // 数据头反序列化失败
                std::cout << "rpc_header_str:" << rpc_header_str << " parse error!" << std::endl;
                return;
            }

            // 获取rpc方法参数的字符流数据
            std::string args_str = recv_buf.substr(4 + header_size, args_size);

            // 打印调试信息
            std::cout << "============================================" << std::endl;
            std::cout << "header_size: " << header_size << std::endl; 
            std::cout << "rpc_header_str: " << rpc_header_str << std::endl; 
            std::cout << "service_name: " << service_name << std::endl; 
            std::cout << "method_name: " << method_name << std::endl; 
            std::cout << "args_str: " << args_str << std::endl; 
            std::cout << "============================================" << std::endl;

            // 获取service对象和method对象
            auto it = m_serviceMap.find(service_name);
            if (it == m_serviceMap.end())
            {
                std::cout << service_name << " is not exist!" << std::endl;
                return;
            }

            auto mit = it->second.m_methodMap.find(method_name);
            if (mit == it->second.m_methodMap.end())
            {
                std::cout << service_name << ":" << method_name << " is not exist!" << std::endl;
                return;
            }

            google::protobuf::Service *service = it->second.m_service; // 获取service对象  new UserService
            const google::protobuf::MethodDescriptor *method = mit->second; // 获取method对象  Login

            // 生成rpc方法调用的请求request和响应response参数
            google::protobuf::Message *request = service->GetRequestPrototype(method).New();
            if (!request->ParseFromString(args_str))
            {
                std::cout << "request parse error, content:" << args_str << std::endl;
                return;
            }
            google::protobuf::Message *response = service->GetResponsePrototype(method).New();

            // 给下面的method方法的调用，绑定一个Closure的回调函数
            google::protobuf::Closure *done = google::protobuf::NewCallback<RpcProvider, 
                                                                            Connection*, 
                                                                            google::protobuf::Message*>
                                                                            (this, 
                                                                            &RpcProvider::SendRpcResponse, 
                                                                            conn, response);

            // 在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
            // new UserService().Login(controller, request, response, done)
            service->CallMethod(method, nullptr, request, response, done);
        }
    );
    // 把当前rpc节点上要发布的服务全部注册到zk上面，让rpc client可以从zk上发现服务
    // session timeout   30s     zkclient 网络I/O线程  1/3 * timeout 时间发送ping消息
    ZkClient zkCli;
    zkCli.Start();
    // service_name为永久性节点    method_name为临时性节点
    for (auto &sp : m_serviceMap) 
    {
        // /service_name   /UserServiceRpc
        std::string service_path = "/" + sp.first;
        zkCli.Create(service_path.c_str(), nullptr, 0);
        for (auto &mp : sp.second.m_methodMap)
        {
            // /service_name/method_name   /UserServiceRpc/Login 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" + mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data, "%s:%d", ip.c_str(), port);
            // ZOO_EPHEMERAL表示znode是一个临时性节点
            zkCli.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);
        }
    }

    // rpc服务端准备启动，打印信息
    std::cout << "RpcProvider start service at ip:" << ip << " port:" << port << std::endl;
    server->Start();
}

// Closure的回调操作，用于序列化rpc的响应和网络发送
void RpcProvider::SendRpcResponse(Connection* conn, google::protobuf::Message *response)
{
    std::string response_str;
    if (response->SerializeToString(&response_str)) // response进行序列化
    {
        // 序列化成功后，通过网络把rpc方法执行的结果发送会rpc的调用方
        conn->Send(response_str);
        //std::cout << "response string:"<< response_str << std::endl; 
    }
    else
    {
        std::cout << "serialize response_str error!" << std::endl; 
    }
    conn->shutdown(); // 模拟http的短链接服务，由rpcprovider主动断开连接
}