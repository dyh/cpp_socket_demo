cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD 14)

link_libraries(pthread)

find_package(OpenCV REQUIRED)
add_executable(server test-server.cpp server.cpp server.h message.cpp message.h)

include_directories(./)
include_directories($ENV{HOME}/.local/include)
link_directories($ENV{HOME}/.local/lib)

target_link_libraries(server ${OpenCV_LIBS})