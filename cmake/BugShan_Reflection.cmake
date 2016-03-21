set(BUGSHAN_REFLECTION bugshan_reflection)

# include files
include_directories(${BUGSHAN_ROOT_DIR}/include)

# source files
file(GLOB BUGSHAN_REFLECTION_INC "${BUGSHAN_ROOT_DIR}/include/bugshan/reflection/*.h")
source_group("Header Files\\reflection" FILES ${BUGSHAN_REFLECTION_INC})
file(GLOB BUGSHAN_REFLECTION_SRC "${BUGSHAN_ROOT_DIR}/source/reflection/*.cpp")
source_group("Source Files\\reflection" FILES ${BUGSHAN_REFLECTION_SRC})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS}")

add_library(${BUGSHAN_REFLECTION} STATIC ${BUGSHAN_REFLECTION_INC} ${BUGSHAN_REFLECTION_SRC})
set_target_properties(${BUGSHAN_REFLECTION} PROPERTIES FOLDER ${BUGSHAN_TOP_LEVEL_FOLDER})
