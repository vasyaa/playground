#include "algorithms/avl_tree.h"
#include "algorithms/least_frequently_used.h"
#include "incubator/any.h"
//#include "mt/work_scheduling.h"
#include "solvers/activity_selection_solver.h"
#include "solvers/graph.h"
#include "solvers/knapsack_solver.h"
#include "solvers/longest_common_subseq_solver.h"
#include "solvers/merge_overlapping_intervals_solver.h"

//#include "algorithms/disjoint_set.h"
#include "algorithms/disjoint_set_simple.h"
#include "algorithms/disjoint_set_simple_map.h"
#include "solvers/jobs_scheduling_solver.h"
#include "solvers/weighted_jobs_scheduling_solver.h"

//#include "todo/big_int.h"
//#include "todo/shared_ptr.h"

using namespace std;

int main(void) {
    least_frequently_used::test::test();
    any::test::test();
    return 0;
    solvers::graph::test();
    solvers::weighted_jobs_scheduling::test();

    //    solvers::scheduling_jobs_solver::test();
    //
    solvers::knapsack_solver::test();
    //    solvers::longest_common_subseq_solver::test();
    //
    //    solvers::merge_overlapping_intervals_solver::test();
    //    solvers::activity_selection_solver::test();
    //    algorithms::avl_tree::test();
    //    algorithms::disjoint_set_simple::test();
    //    algorithms::disjoint_set_simple_map::test();
    //
    ////    algorithms::shared_ptr::test();
    ////    algorithms::big_num::test();
    ////    algorithms::disjoint_set::test();
    return 0;
}
