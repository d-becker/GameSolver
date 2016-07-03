cmake_minimum_required (VERSION 2.8)

set(SRC_FILES
	AlphaBeta.cpp
	TreeNode.cpp
   )

add_executable(GameSolverExe "main.cpp" ${SRC_FILES})
add_library(GameSolver SHARED ${SRC_FILES})
