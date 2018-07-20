cmake_minimum_required(VERSION 3.10)
project(playground)

set(CMAKE_CXX_STANDARD 17)

include_directories(algorithms)
include_directories(incubator)
include_directories(solvers)

add_library(playground
    algorithms/avl_tree.h
    algorithms/disjoint_set.h
    algorithms/disjoint_set.t.cpp
    algorithms/disjoint_set_simple.h
    algorithms/disjoint_set_simple_map.h
    algorithms/least_frequently_used.h
    incubator/any.h
#        mt/work_scheduling.h
    solvers/activity_selection_solver.h
    solvers/graph.h
    solvers/jobs_scheduling_solver.h
    solvers/knapsack_solver.h
    solvers/longest_common_subseq_solver.h
    solvers/merge_overlapping_intervals_solver.h
    solvers/weighted_jobs_scheduling_solver.h
#        tmp/dijkstra.cpp
#        todo/big_int.h
#        todo/shared_ptr.h
#        todo/shared_ptr.t.cpp
    )

################################################################################
enable_testing()

add_executable(unittest 
    unittest.cpp 
    test/any.test.cpp 
    test/avl_tree.test.cpp
    test/graph.test.cpp
    test/least_frequently_used.test.cpp
    test/weighted_jobs_scheduling.test.cpp)

target_link_libraries(unittest playground)

add_test(NAME test COMMAND unittest)

################################################################################
add_custom_target(run unittest DEPENDS unittest)

