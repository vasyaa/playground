#ifndef SOLVERS_KNAPSACK_SOLVER_H_
#define SOLVERS_KNAPSACK_SOLVER_H_

#include <vector>
#include <algorithm>
#include <iostream>

#include <cassert>
#include <cstring>
#include <cassert>

namespace solvers {
namespace knapsack_solver {

using namespace std;

namespace internal {
class KnapsackSolverBase {
public:
    void init(const int W, const std::vector<int>& val, const std::vector<int>& wt) {
        assert(val.size() == wt.size());
        this->W = W;
        this->val = val;
        this->wt = wt;
    }

protected:
    int W;
    std::vector<int> val;
    std::vector<int> wt;
};
} // end ns

template <int T>
class KnapsackSolver;

enum {
    RECURSIVE_SOLVER = 1,
    DP_SOLVER = 2
};

template <>
class KnapsackSolver<RECURSIVE_SOLVER> : public internal::KnapsackSolverBase {
public:

    // -------------------------------------------------------------------------
    int solve() {
        std::cout << "Running " << __func__ << std::endl;
        return ks_recursive(W, val.size());
    }

    int ks_recursive(int W, int n) {
        if(W == 0 || n == 0) {
            return 0;
        }
        if(wt[n - 1] > W) {
            return ks_recursive(W, n - 1);
        }
        int a = val[n - 1] + ks_recursive(W - wt[n - 1], n - 1);
        int b = ks_recursive(W, n - 1);

        return max(a, b);
    }
};

template <>
class KnapsackSolver<DP_SOLVER> : public internal::KnapsackSolverBase {
public:
    int solve() {
        std::cout << "Running " << __func__ << std::endl;
        return ks_dp(W, val, wt, val.size());
    }

    int ks_dp(int W, std::vector<int> val, std::vector<int> wt, int n) {
        int dp[n + 1][W + 1];

        for(int i = 0; i <= n; i++) {
            for(int w = 0; w <= W; w++) {
                if(w == 0 || i == 0) {
                    dp[i][w] = 0;
                }
                else if(wt[i - 1] > w) {
                    dp[i][w] = dp[i - 1][w];
                }
                else {
                    int a = val[i - 1] + dp[i - 1][w - wt[i-1]];
                    int b = dp[i - 1][w];
                    dp[i][w] = max(a, b);
                }
            }
        }
        return dp[n][W];
    }
};


inline void test() {
    std::vector<int> val = {60, 100, 120};
    std::vector<int> wt = {10, 20, 30};
    int  W = 50;

    KnapsackSolver<RECURSIVE_SOLVER> rs;
    rs.init(W, val, wt);

    assert(220 == rs.solve());
    std::cout << "KnapsackSolver<RECURSIVE_SOLVER>::solve OK" << std::endl;

    KnapsackSolver<DP_SOLVER> dps;
    dps.init(W, val, wt);
    assert(220 == dps.solve());
    std::cout << "KnapsackSolver<DP_SOLVER>::solve OK" << std::endl;
}

}
}

#endif /* SOLVERS_KNAPSACK_SOLVER_H_ */
