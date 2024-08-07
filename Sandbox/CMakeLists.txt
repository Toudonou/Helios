cmake_minimum_required(VERSION 3.28)

include_directories(../Helios/third-party/include)
link_directories(../Helios/third-party/lib)

add_executable(Sandbox main.cpp)

target_link_libraries(Sandbox PRIVATE Helios)
