cmake_minimum_required(VERSION 3.17)
project(client)

set(CMAKE_CXX_STANDARD 14)

link_libraries(pthread)

find_package(OpenCV REQUIRED)
add_executable(client test-client.cpp client.cpp client.h message.cpp message.h client.cpp client.h test-client.cpp)

include_directories(./)
include_directories($ENV{HOME}/.local/include)
link_directories($ENV{HOME}/.local/lib)

target_link_libraries(client ${OpenCV_LIBS})