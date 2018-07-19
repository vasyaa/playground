/*
 * scheduling_jobs.h
 *
 *  Created on: May 19, 2018
 *      Author: vasyaa
 */

#ifndef SOLVERS_JOBS_SCHEDULING_SOLVER_H_
#define SOLVERS_JOBS_SCHEDULING_SOLVER_H_

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace solvers {
namespace jobs_scheduling_solver {

using namespace std;

namespace internal {
struct Interval {
    char id;
    int deadline;
    int profit;

    Interval() = default;
    Interval(char id_, int deadline_, int profit_)
        : id(id_), deadline(deadline_), profit(profit_) {}
};

struct FindUnion {
    FindUnion(int size_) {
        data.resize(size_ + 1);
        for (size_t i = 0; i < data.size(); i++) {
            data[i] = i;
        }
    }

    int find(int i) {
        if (i == data[i]) {
            return i;
        }
        data[i] = find(data[i]);
        return data[i];
    }

    void merge(int a, int b) {
        data[b] = a;
        int key_a = find(a);
        int key_b = find(b);
        data[key_a] = key_b;
    }

    vector<int> data;
};

inline void test() {
    const int N = 10;
    FindUnion s(N);

    s.merge(1, 2);
    s.merge(2, 3);

    s.merge(5, 6);
    s.merge(5, 7);
    s.merge(7, 8);

    for (int i = 0; i < N; i++) {
        cout << i << ":" << s.data[i] << " ";
    }
    cout << endl;
}
} // namespace internal

using namespace internal;

class SchedulingJobsSolver {
public:
    typedef std::vector<internal::Interval> data_type;

    void init(const data_type &data_) { data = data_; }

    data_type solve_greedy() {
        // 1. sort
        sort(data.begin(), data.end(),
             [](const internal::Interval &a, const internal::Interval &b) {
                 return a.profit > b.profit;
             });

        const int n = data.size();
        vector<int> result(n, 0);
        vector<int> occ_slots(n, 0);

        for (int i = 0; i < n; i++) {
            int j = min(n, data[i].deadline) - 1;

            for (; j >= 0; j--) {
                if (occ_slots[j] == false) {
                    result[j] = i;
                    occ_slots[j] = true;
                    break;
                }
            }
        }

        data_type rc;
        for (int i = 0; i < n; i++) {
            if (occ_slots[i]) {
                rc.push_back(data[result[i]]);
            }
        }

        return rc;
    }

    // find union
    int findMaxDeadline() {
        int rc = -1;
        for (size_t i = 0; i < data.size(); i++) {
            rc = max(rc, data[i].deadline);
        }
        return rc;
    }

    data_type solve() {
        sort(data.begin(), data.end(),
             [](const internal::Interval &a, const internal::Interval &b) {
                 return a.profit > b.profit;
             });

        int m = findMaxDeadline();
        FindUnion fu(m);

        data_type rc;
        const int n = data.size();
        for (int i = 0; i < n; i++) {
            int availSlot = fu.find(data[i].deadline);

            if (availSlot > 0) {
                fu.merge(availSlot - 1, availSlot);
                rc.push_back(data[i]);
            }
        }

        return rc;
    }

    SchedulingJobsSolver &add(char id, int deadline, int profit) {
        data.emplace_back(id, deadline, profit);
        return *this;
    }

    void print() {
        for (size_t i = 0; i < data.size(); i++) {
            std::cout << data[i].id << ":" << data[i].deadline << ":"
                      << data[i].profit << std::endl;
        }
    }

private:
    data_type data;
};

void test() {
    SchedulingJobsSolver::data_type data = {
        {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};
    SchedulingJobsSolver::data_type result;

    SchedulingJobsSolver s;
    s.init(data);

    result = s.solve_greedy();
    assert(result[0].id == 'c');
    assert(result[1].id == 'a');
    assert(result[2].id == 'e');
    std::cout << "SchedulingJobsSolver::solve_greedy Ok" << std::endl;

    result = s.solve();
    assert(result[0].id == 'a');
    assert(result[1].id == 'c');
    assert(result[2].id == 'e');
    std::cout << "SchedulingJobsSolver::solve Ok" << std::endl;
}

} // namespace jobs_scheduling_solver
} // namespace solvers

#endif /* SOLVERS_JOBS_SCHEDULING_SOLVER_H_ */
