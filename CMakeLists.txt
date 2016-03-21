cmake_minimum_required(VERSION 3.0)

set(BUGSHAN bugshan)
project(${BUGSHAN})

set(BUGSHAN_ROOT_DIR ./)
set(BUGSHAN_TOP_LEVEL_FOLDER "bugshan")

include(./cmake/BugShan_IO.cmake)
include(./cmake/BugShan_Reflection.cmake)
