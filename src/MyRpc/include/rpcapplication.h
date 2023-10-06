#pragma once

#include "rpcconfig.h"
#include "rpcchannel.h"
#include "rpcprovider.h"
//#include "rpccontroller.h"

// mprpc框架的基础类，负责框架的一些初始化操作
class RpcApplication
{
public:
    static void Init(int argc, char **argv);
    static RpcApplication& GetInstance();
    static RpcConfig& GetConfig();
private:
    static RpcConfig m_config;

    RpcApplication(){}
    RpcApplication(const RpcApplication&) = delete;
    RpcApplication(RpcApplication&&) = delete;
};