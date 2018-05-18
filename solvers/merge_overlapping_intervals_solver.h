#ifndef SOLVERS_MERGE_OVERLAPPING_INTERVALS_SOLVER_H_
#define SOLVERS_MERGE_OVERLAPPING_INTERVALS_SOLVER_H_

#include <vector>
#include <utility>
#include <algorithm>

#include <stack>
#include <iostream>

namespace solvers {
namespace merge_overlapping_intervals_solver {

struct OverlappingIntervalsSolver {
public:
    typedef std::pair<int, int> interval_type;
    typedef std::vector<interval_type> data_type;
    typedef data_type result_type;

    OverlappingIntervalsSolver() = default;
    OverlappingIntervalsSolver& init(const data_type& dataIn){
        data = dataIn;
        return *this;
    }

    OverlappingIntervalsSolver& add(int a, int b) {
        data.insert(data.end(), std::make_pair(a,b));
        return *this;
    }

    result_type solve() {
        std::sort(data.begin(), data.end(),
                [](interval_type& a, interval_type& b){return a.first < b.first;}
        );

        std::stack<interval_type> s;

        s.push(data[0]);
        for(size_t i = 1; i < data.size(); i++) {
            interval_type p = s.top();

            if(p.second < data[i].first) {
                s.push(data[i]);
            }
            else if(p.second < data[i].second) {
                p.second = data[i].second;
                s.pop();
                s.push(p);
            }
        }

        result_type res;
        while(! s.empty()) {
            interval_type p = s.top();
            res.insert(res.end(), p);
            s.pop();
        }

        return res;
    }
private:
    data_type data;
};

inline void test() {
    OverlappingIntervalsSolver::data_type data = { {6,8}, {1,9}, {2,4}, {4,7} };

    OverlappingIntervalsSolver as;
    as.init(data);
    as.add(8, 9).add(5,9).add(10,23);

    OverlappingIntervalsSolver::result_type res;
    res = as.solve();

    for(size_t i = 0; i < res.size(); i++) {
        std::cout << res[i].first << ":" << res[i].second << " ";
    }
    std::cout << std::endl;
}

}
}

#endif /* SOLVERS_MERGE_OVERLAPPING_INTERVALS_SOLVER_H_ */
