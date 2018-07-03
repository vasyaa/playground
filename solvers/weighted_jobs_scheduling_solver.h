/*
 * waighted_jobs_scheduling.h
 *
 *  Created on: Jun 29, 2018
 *      Author: vasyaa
 */

#ifndef SOLVERS_WEIGHTED_JOBS_SCHEDULING_SOLVER_H_
#define SOLVERS_WEIGHTED_JOBS_SCHEDULING_SOLVER_H_

//
// https://courses.cs.washington.edu/courses/cse521/13wi/slides/06dp-sched.pdf
// https://ocw.tudelft.nl/wp-content/uploads/Algoritmiek_Weighted_Interval_Scheduling.pdf
//

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <iostream>

namespace solvers {
namespace weighted_jobs_scheduling {

struct Job {
    int start;
    int finish;
    int weight;

    bool operator<(const Job& other) {
        return finish < other.finish;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const Job& other) {
        ostr << "start=" << other.start
                << " finish=" << other.finish
                << " weight=" << other.weight;
        return ostr;
    }
};

namespace internal {

template <
    typename ContainerType = std::vector<Job>,
    typename RefContainerType = std::vector<Job>
    >
class WeightedJobSchedulingBase {
public:
    typedef ContainerType container_type;
    typedef RefContainerType ref_container_type;

    WeightedJobSchedulingBase() {
        data = ContainerType(1);
    }

    void add(const Job& i) {
        data.push_back(i);
    }

protected:
    ContainerType data;
    std::vector<int> p;

    void calc_p() {
        p = std::vector<int>(data.size(), 0);
        for(int i = data.size() - 1; i >= 0; i-- ) {
            for(int k = i - 1; k >= 0; k--) {
                if(data[k].finish <= data[i].start) {
                    p[i] = k;
                    break;
                }
            }
        }
    }
};

} // end ns

using namespace internal;

enum {
    RECURSIVE_SOLVER = 1,
    DP_SOLVER = 2
};

template <int T>
class WeightedJobScheduling;

// recursive solution
template <>
class WeightedJobScheduling<RECURSIVE_SOLVER>
    : public WeightedJobSchedulingBase<> {
public:
    std::tuple<int, container_type> solve() {
        std::sort(data.begin(), data.end());

        calc_p();

        int res = recursive_compute_opt(data.size() - 1);
        return make_tuple(res, container_type());
    }

private:
    int recursive_compute_opt(int j) {
        if(j == 0) {
            return 0;
        }
        else {
            int rc;
            rc = std::max(
                    data[j].weight + recursive_compute_opt(p[j]),
                    recursive_compute_opt(j - 1));
            return rc;
        }
    }

};

// bottom up solution
template <>
class WeightedJobScheduling<DP_SOLVER>
    : public WeightedJobSchedulingBase<> {
public:
    std::tuple<int, ref_container_type> solve() {
        std::sort(data.begin(), data.end());
        calc_p();
        dp = std::vector<int>(data.size(),0);

        int res = iterative_compute_opt();
        path.clear();
        recreate_path(data.size() - 1);
        std::reverse(path.begin(), path.end());
        return make_tuple(res, path);
    }

private:
    std::vector<int> dp;
    ref_container_type path;

    int iterative_compute_opt() {
        dp = std::vector<int>(data.size(), 0);
        for(int j = 0; j < (int)dp.size(); j++) {
            dp[j] = std::max(data[j].weight + dp[p[j]], dp[p[j - 1]]);
        }

        return dp[dp.size() - 1];
    }

    void recreate_path(int j) {
        if(j == 0) {
            return;
        }
        if(data[j].weight + dp[p[j]] > dp[j - 1]) {
            path.push_back(std::reference_wrapper<Job>(data[j]));
            recreate_path(p[j - 1]);
        }
        else {
            recreate_path(p[j - 1]);
        }
    }
};

template <typename SolverType>
inline void test_impl(const std::vector<Job>& arr) {
    SolverType sch;
    for(auto &i: arr) {
        sch.add(i);
    }

    auto res = sch.solve();
    auto &rc = std::get<1>(res);
    int val = std::get<0>(res);

    std::cout << "value=" << val << std::endl;
    std::cout << "path:" << std::endl;
    std::copy(rc.begin(), rc.end(), std::ostream_iterator<Job>(std::cout, "\n"));
}

inline void test() {
    std::vector<Job> arr = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};

    std::cout << "Recursive solution" << std::endl;
    test_impl<WeightedJobScheduling<RECURSIVE_SOLVER>>(arr);

    std::cout << "DP solution" << std::endl;
    test_impl<WeightedJobScheduling<DP_SOLVER>>(arr);
}

}
}

#endif /* SOLVERS_WEIGHTED_JOBS_SCHEDULING_SOLVER_H_ */
