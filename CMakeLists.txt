cmake_minimum_required(VERSION 3.19)
project(Gobang2)

set(CMAKE_CXX_STANDARD 17)

set(INC_DIR ./include)
set(LINK_DIR ./lib)
include_directories(${INC_DIR})
link_directories(${LINK_DIR})

add_executable(Gobang2 main.cpp Gobang.cpp Gobang.h EasyX.cpp EasyX.h Play.cpp Play.h Zobrist.cpp Zobrist.h)

target_link_libraries(Gobang2 EasyXa EasyXw VSCustomNativeHeapEtwProvider VsGraphicsHelper)