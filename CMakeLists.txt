cmake_minimum_required(VERSION 3.5.0)
project(playground)

set(SOURCE
	playground.cpp
	test/avl_tree.test.cpp
	test/graph.test.cpp
	test/simple_any.test.cpp
	test/weighted_jobs_scheduling_solver.test.cpp)
	
add_executable(playground ${SOURCE})

add_custom_target(run playground)
