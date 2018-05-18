#ifndef SOLVERS_KNAPSACK_SOLVER_H_
#define SOLVERS_KNAPSACK_SOLVER_H_

#include <vector>
#include <algorithm>
#include <iostream>

#include <cassert>
#include <cstring>

namespace solvers {
namespace knapsack_solver {

using namespace std;

class KnapsackSolver {
public:
    void init(const int W, const std::vector<int>& val, const std::vector<int>& wt) {
        this->W = W;
        this->val = val;
        this->wt = wt;
    }


    // -------------------------------------------------------------------------
    int solve_recursive() {
        return ks_recursive(W, val, wt, val.size());
    }

    int ks_recursive(int W, std::vector<int> val, std::vector<int> wt, int n) {
        if(W == 0 || n == 0) {
            return 0;
        }
        if(wt[n - 1] > W) {
            return ks_recursive(W, val, wt, n - 1);
        }
        int a = val[n - 1] + ks_recursive(W - wt[n - 1], val, wt, n - 1);
        int b = ks_recursive(W, val, wt, n - 1);

        return max(a, b);
    }

    // -------------------------------------------------------------------------
    int solve() {
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
protected:
    int W;
    std::vector<int> val;
    std::vector<int> wt;
};


inline void test() {
    std::vector<int> val = {60, 100, 120};
    std::vector<int> wt = {10, 20, 30};
    int  W = 50;

    KnapsackSolver s;
    s.init(W, val, wt);

    assert(220 == s.solve_recursive());
    std::cout << "KnapsackSolver::solve_recusrsive OK" << std::endl;

    assert(220 == s.solve());
    std::cout << "KnapsackSolver::solve OK" << std::endl;
}

}
}

#endif /* SOLVERS_KNAPSACK_SOLVER_H_ */
