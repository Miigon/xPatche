cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 14)

aux_source_directory(./src SRC_DIR)

add_library(xpatche SHARED ${SRC_DIR})
find_library(LIB_LUAJIT luajit)
target_link_libraries(xpatche ${LIB_LUAJIT})
target_include_directories(xpatche PUBLIC /usr/local/include)
target_include_directories(xpatche PUBLIC ./include)

aux_source_directory(./test TEST_DIR)

add_executable(tester ${TEST_DIR})
target_include_directories(tester PUBLIC ./include)
target_link_libraries(tester xpatche)
target_link_libraries(tester "-pagezero_size 10000 -image_base 100000000") # luajit needs this to run on 64bit macOS
