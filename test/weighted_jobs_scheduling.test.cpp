/*
 * weighted_jobs_scheduling_solver.test.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: vasyaa
 */

#include "../solvers/weighted_jobs_scheduling_solver.h"

namespace solvers {
namespace weighted_jobs_scheduling {

namespace {

template <typename SolverType> void test_impl(const std::vector<Job> &arr) {
    SolverType sch;
    for (auto &i : arr) {
        sch.add(i);
    }

    auto res = sch.solve();
    auto &rc = std::get<1>(res);
    auto val = std::get<0>(res);

    std::cout << "value=" << val << std::endl;
    std::cout << "path:" << std::endl;
    std::copy(rc.begin(), rc.end(),
              std::ostream_iterator<Job>(std::cout, "\n"));
}

} // namespace

void test() {
    std::vector<Job> arr = {
        {3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};

    std::cout << "Recursive solution" << std::endl;
    test_impl<WeightedJobScheduling<RECURSIVE_SOLVER>>(arr);

    std::cout << "DP solution" << std::endl;
    test_impl<WeightedJobScheduling<DP_SOLVER>>(arr);
}

} // namespace weighted_jobs_scheduling
} // namespace solvers
