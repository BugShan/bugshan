set(BUGSHAN_IO bugshan_io)

# include files
include_directories(${BUGSHAN_ROOT_DIR}/include)

# source files
file(GLOB BUGSHAN_IO_INC "${BUGSHAN_ROOT_DIR}/include/bugshan/io/*.h")
source_group("Header Files\\io" FILES ${BUGSHAN_IO_INC})
file(GLOB BUGSHAN_IO_SRC "${BUGSHAN_ROOT_DIR}/source/io/*.cpp")
source_group("Source Files\\io" FILES ${BUGSHAN_IO_SRC})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS}")

add_library(${BUGSHAN_IO} STATIC ${BUGSHAN_IO_INC} ${BUGSHAN_IO_SRC})
set_target_properties(${BUGSHAN_IO} PROPERTIES FOLDER ${BUGSHAN_TOP_LEVEL_FOLDER})
