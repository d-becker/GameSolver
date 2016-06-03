cmake_minimum_required (VERSION 2.8)

set(TEST_SRC_FILES
	main_unit_test.cpp

	TreeNodeTest.cpp
   )

add_executable(GameSolverUnitTest ${TEST_SRC_FILES})
target_link_libraries(GameSolverUnitTest gtest GameSolver)
