#ifndef ALGORITHMS_DISJOINT_SET_SIMPLE_H_
#define ALGORITHMS_DISJOINT_SET_SIMPLE_H_

#include <iostream>

namespace algorithms {
namespace disjoint_set_simple {

struct disjoint_set {
    int* parent;

    disjoint_set(int size) {
        parent = new int[size + 1];
        for(int i = 0; i <= size; i++) {
            parent[i] = i;
        }
    }

    ~disjoint_set() {
        delete [] parent;
    }

    int find(int s) {
        int root = s;
        while(root != parent[root]) {
            root = parent[root];
        }
        return root;
    }

    void join(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        parent[root_x] = root_y;
    }

    void check_insert(int s) {
//        if()
    }
    disjoint_set(const disjoint_set&) = delete;
    disjoint_set& operator=(const disjoint_set&) = delete;
};

inline void test() {
    disjoint_set s(20);

    s.join(1, 6);
    s.join(2, 7);
    s.join(3, 8);
    s.join(4, 9);
    s.join(2, 6);

    s.join(10, 11);
    s.join(11, 12);

    assert(s.find(1) == s.find(6));
    assert(s.find(2) == s.find(6));
    assert(s.find(3) == s.find(8));
    assert(s.find(4) == s.find(9));
    assert(s.find(6) == s.find(6));
    assert(s.find(7) == s.find(6));
    assert(s.find(8) == s.find(8));
    assert(s.find(9) == s.find(9));
    assert(s.find(10) == s.find(12));
    assert(s.find(11) == s.find(12));
    assert(s.find(12) == s.find(12));

    std::cout << "disjoint_set_simple::disjoint_set OK" << std::endl;
}

}
}

#endif /* ALGORITHMS_DISJOINT_SET_SIMPLE_H_ */
