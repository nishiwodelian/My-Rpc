add_executable(client client.cc)
target_link_libraries(client MyNetworkLib)

add_executable(server server.cc)
target_link_libraries(server MyNetworkLib)

add_executable(HTTPServer http_server.cc)
target_link_libraries(HTTPServer MyNetworkLib)