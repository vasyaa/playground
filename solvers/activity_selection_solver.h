#ifndef SOLVERS_ACTIVITY_SELECTION_SOLVER_H_
#define SOLVERS_ACTIVITY_SELECTION_SOLVER_H_

#include <algorithm>
#include <utility>
#include <vector>

#include <iostream>
//#include <cassert>

namespace solvers {
namespace activity_selection_solver {

using namespace std;

class ActivitySelectionSolver {
public:
    typedef std::pair<int, int> interval_type;
    typedef std::vector<interval_type> data_type;
    typedef data_type result_type;

    ActivitySelectionSolver() = default;
    ActivitySelectionSolver &init(const data_type &dataIn) {
        data = dataIn;
        return *this;
    }

    ActivitySelectionSolver &add(int a, int b) {
        data.insert(data.end(), std::make_pair(a, b));
        return *this;
    }

    result_type solve() {
        std::sort(data.begin(), data.end(),
                  [](interval_type &a, interval_type &b) {
                      return a.second < b.second;
                  });
        result_type res;

        interval_type p = data[0];
        res.insert(res.end(), p);
        for (size_t i = 1; i < data.size(); i++) {
            if (p.second <= data[i].first) {
                p = data[i];
                res.insert(res.end(), p);
            }
        }
        return res;
    }

private:
    data_type data;
};

inline void test() {
    ActivitySelectionSolver::data_type data = {{1, 2}, {3, 4}, {0, 6}, {5, 7}};

    ActivitySelectionSolver as;
    as.init(data);
    as.add(8, 9).add(5, 9);

    ActivitySelectionSolver::result_type res;
    res = as.solve();

    for (size_t i = 0; i < res.size(); i++) {
        cout << res[i].first << ":" << res[i].second << " ";
    }
    cout << endl;
}

} // namespace activity_selection_solver
} // namespace solvers

#endif /* SOLVERS_ACTIVITY_SELECTION_SOLVER_H_ */
