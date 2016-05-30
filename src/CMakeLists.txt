cmake_minimum_required (VERSION 2.8)

set(SRC_FILES

   )

add_executable(GameSolverTest "main.cpp" ${SRC_FILES})
add_library(GameSolver SHARED ${SRC_FILES})
