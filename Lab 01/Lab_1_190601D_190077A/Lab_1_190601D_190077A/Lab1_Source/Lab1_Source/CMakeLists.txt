cmake_minimum_required(VERSION 3.26)
project(Lab1_CC C)
find_package(Threads REQUIRED)
set(CMAKE_C_STANDARD 11)

add_executable(Lab1_CC main.c linked_list.c serial.c mutex.c rw_lock.c helper_func.c)
target_link_libraries(Lab1_CC PRIVATE Threads::Threads)