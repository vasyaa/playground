#ifndef LONGEST_INCREASING_SUBSEQ_H_
#define LONGEST_INCREASING_SUBSEQ_H_

#include <vector>
#include <string>
#include <algorithm>

#include <iostream>
#include <cassert>

namespace solvers {
namespace longest_common_subseq_solver {

// interface
enum {
    RECURSIVE_BACK_SOLVER = 1,
    RECURSIVE_SOLVER,
    MEMOIZATION_SOLVER,
    DP_SOLVER
};

template <int Type>
class LongestCommonSubseqSolver {};

typedef LongestCommonSubseqSolver<RECURSIVE_BACK_SOLVER> RecurBackSolver;
typedef LongestCommonSubseqSolver<RECURSIVE_SOLVER> RecurSolver;
typedef LongestCommonSubseqSolver<MEMOIZATION_SOLVER> MemoizSolver;
typedef LongestCommonSubseqSolver<DP_SOLVER> DPSolver;

// implementation
typedef std::string data_type;

// fun
struct DPBase {
    void init(int m, int n, int initVal) {
        dp.resize(m);
        for(auto &r: dp) {
            r.resize(n, initVal);
        }
    }
protected:
    std::vector<std::vector<int>> dp;
};

class LongestIncreasingSubseqSolverBase {
public:
    void init(const data_type& a_, const data_type& b_) {
        a = a_;
        b = b_;
    }
public:
    data_type a;
    data_type b;
};

template <>
class LongestCommonSubseqSolver<RECURSIVE_BACK_SOLVER>
    : public LongestIncreasingSubseqSolverBase {
public:
    //--------------------------------------------------------------------------
    int lcs_reqursive_back(data_type& a, data_type& b, size_t m, size_t n) {
        if(m == 0 ||  n == 0)
            return 0;
        if(a[m-1] == b[n-1])
            return 1 + lcs_reqursive_back(a, b, m - 1, n -1);
        else
            return std::max(lcs_reqursive_back(a, b, m, n-1), lcs_reqursive_back(a, b, m - 1, n));
    }

    int solve() {
        return lcs_reqursive_back(a, b, a.size(), b.size());
    }
};

template <>
class LongestCommonSubseqSolver<RECURSIVE_SOLVER>
    : public LongestIncreasingSubseqSolverBase {
public:
    int solve() {
        return lcs_reqursive(a, b, 0, 0);
    }
private:
    int lcs_reqursive(data_type& a, data_type& b, size_t m, size_t n) {
        if(a[m] == 0 ||  b[n] == 0)
            return 0;
        if(a[m] == b[n])
            return 1 + lcs_reqursive(a, b, m + 1, n + 1);
        else
            return std::max(lcs_reqursive(a, b, m, n + 1), lcs_reqursive(a, b, m + 1, n));
    }
};

template <>
class LongestCommonSubseqSolver<MEMOIZATION_SOLVER>
    : public LongestIncreasingSubseqSolverBase
      , public DPBase{
public:
    void init(const data_type& a_, const data_type& b_) {
        LongestIncreasingSubseqSolverBase::init(a_, b_);

        int m = a.size() + 1;
        int n = b.size() + 1;
        DPBase::init(m, n, -1);
    }
    int solve() {
        lcs_memoization(a, b, 0, 0);
        return dp[0][0];
    }

    void print() {
        std::cout << "Matrix" << std::endl;
        for(size_t i = 0; i <= a.size(); i++) {
            for(size_t j = 0; j <= b.size(); j++) {
                std::cout << dp[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:
    int lcs_memoization(data_type& a, data_type& b, size_t m, size_t n) {
        if(dp[m][n] > -1)
            return dp[m][n];
        if(a[m] == 0 ||  b[n] == 0)
            dp[m][n] = 0;
        else if(a[m] == b[n])
            dp[m][n] = 1 + lcs_memoization(a, b, m + 1, n + 1);
        else
            dp[m][n] = std::max(lcs_memoization(a, b, m, n + 1), lcs_memoization(a, b, m + 1, n));

        return dp[m][n];
    }
};

template <>
class LongestCommonSubseqSolver<DP_SOLVER>
    : public LongestCommonSubseqSolver<MEMOIZATION_SOLVER> {
public:
    int solve() {
        return lcs_dp(a, b, a.size(), b.size());
    }
private:
    int lcs_dp(data_type& a, data_type& b, size_t M, size_t N) {
        for(size_t m = 0; m <= M; m++) {
            for(size_t n = 0; n <= N; n++) {
                if(m == 0 || n == 0) {
                    dp[m][n] = 0;
                }
                else if(a[m - 1] == b[n - 1])
                    dp[m][n] = 1 + dp[m - 1][n - 1];
                else
                    dp[m][n] = std::max(dp[m][n - 1], dp[m - 1][n]);
            }
        }
        return dp[M][N];
    }
};

inline void test() {
    {
    RecurBackSolver s;
    s.init("AGGTAB", "GXTXAYB");
    int rc = s.solve();
    assert(rc == 4);
    std::cout << "longest_common_subseq_solver solve_reqursive_back OK" << std::endl;
    }

    {
    RecurSolver s;
    s.init("AGGTAB", "GXTXAYB");
    int rc = s.solve();
    assert(rc == 4);
    std::cout << "longest_common_subseq_solver solve_reqursive OK" << std::endl;
    }

    {
    MemoizSolver s;
    s.init("AGGTAB", "GXTXAYB");
    int rc = s.solve();
    assert(rc == 4);
    std::cout << "longest_common_subseq_solver solve_memoization OK" << std::endl;
    }

    {
    DPSolver s;
    s.init("AGGTAB", "GXTXAYB");
    int rc = s.solve();
    assert(rc == 4);
    std::cout << "longest_common_subseq_solver solve_dp OK" << std::endl;
    }
}

}
}

#endif /* LONGEST_INCREASING_SUBSEQ_H_ */
