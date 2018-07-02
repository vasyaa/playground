/*
 * waighted_jobs_scheduling.h
 *
 *  Created on: Jun 29, 2018
 *      Author: vasyaa
 */

#ifndef SOLVERS_WEIGHTED_JOBS_SCHEDULING_H_
#define SOLVERS_WEIGHTED_JOBS_SCHEDULING_H_

#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

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
    void add(const Job& i) {
        data.push_back(i);
    }

    container_type solve() {
        container_type rc;

        std::sort(data.begin(), data.end());

        Job cur = data[0];
        rc.push_back(cur);
        for(int i = 1; i != (int)data.size(); i++) {
            if(cur.finish <= data[i].start) {
                cur = data[i];
                rc.push_back(cur);
            }
        }

        return rc;
    }

    container_type reqIteration(const container_type& c, int max) {
        container_type rc;
        return rc;
    }

    container_type solve2() {
        container_type rc;



        return rc;
    }
private:
    container_type data;
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

    container_type rc = sch.solve();

    std::copy(rc.begin(), rc.end(), std::ostream_iterator<Job>(std::cout, "\n"));
}

}
}

#endif /* SOLVERS_WEIGHTED_JOBS_SCHEDULING_H_ */
