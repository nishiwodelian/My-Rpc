set(SRC_LIST 
    rpcapplication.cc 
    rpcconfig.cc
    rpcprovider.cc
    rpcchannel.cc
    rpcheader.pb.cc
    zookeeperutil.cc  
    )
add_library(MyRpc SHARED ${SRC_LIST})
target_link_libraries(MyRpc  MyNetworkLib protobuf zookeeper_mt)