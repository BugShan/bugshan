cmake_minimum_required(VERSION 3.0)
set(BUGSHAN bugshan)
set(BUGSHAN_ROOT_DIR ./)
project(${BUGSHAN})

# include files
include_directories(./include)

# source files
file(GLOB BUGSHAN_INC "./include/bugshan/*.h")
file(GLOB BUGSHAN_IO_INC "./include/bugshan/io/*.h")
source_group("Header Files\\io" FILES ${BUGSHAN_IO_INC})
file(GLOB BUGSHAN_IO_SRC "./source/io/*.cpp")
source_group("Source Files\\io" FILES ${BUGSHAN_IO_SRC})

# cxx flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS}")

add_library(${BUGSHAN} STATIC ${BUGSHAN_IO_SRC} ${BUGSHAN_INC} ${BUGSHAN_IO_INC})
