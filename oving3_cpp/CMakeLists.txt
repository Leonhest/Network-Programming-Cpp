cmake_minimum_required(VERSION 3.25)
project(oving3_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(SocketClient SocketClient.cpp Data.cpp)
add_executable(MultiServer MultiServer.cpp)
