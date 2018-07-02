/*
 * waighted_jobs_scheduling.h
 *
 *  Created on: Jun 29, 2018
 *      Author: vasyaa
 */

#ifndef SOLVERS_WEIGHTED_JOBS_SCHEDULING_H_
#define SOLVERS_WEIGHTED_JOBS_SCHEDULING_H_

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

typedef std::vector<Job> container_type;

class WeightedJbScheduling {
public:
    WeightedJbScheduling() {
        data = std::vector<Job>(1);
    }

    void add(const Job& i) {
        data.push_back(i);
    }

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

    // recursive solution
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

    // bottom up solution
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
            path.push_back(data[j]);
            recreate_path(p[j - 1]);
        }
        else {
            recreate_path(p[j - 1]);
        }
    }

    std::tuple<int, container_type> solve() {
        std::sort(data.begin(), data.end());
        calc_p();
        dp = std::vector<int>(data.size(),0);

//        int res = recursive_compute_opt(data.size() - 1);
        int res = iterative_compute_opt();
        path = container_type();
        recreate_path(data.size() - 1);
        std::reverse(path.begin(), path.end());
        return make_tuple(res, path);
    }

private:
    container_type data;
    std::vector<int> dp;
    std::vector<int> p;
    std::vector<Job> path;
};


inline void test() {
    Job arr[] = {{3, 10, 20}, {1, 2, 50}, {6, 19, 100}, {2, 100, 200}};
//    Job arr[] = {{5, 9}, {1, 2}, {3, 4}, {0, 6},
//                                       {5, 7}, {8, 9}};

//    int n = sizeof(arr)/sizeof(arr[0]);

    WeightedJbScheduling sch;
    for(auto &i: arr) {
        sch.add(i);
    }

    auto res = sch.solve();
    container_type rc = std::get<1>(res);
    int val = std::get<0>(res);
    std::cout << "value=" << val << std::endl;
    std::copy(rc.begin(), rc.end(), std::ostream_iterator<Job>(std::cout, "\n"));
}

}
}

#endif /* SOLVERS_WEIGHTED_JOBS_SCHEDULING_H_ */
