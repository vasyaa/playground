#ifndef ALGORITHMS_DISJOINT_SET_SIMPLE_MAP_H_
#define ALGORITHMS_DISJOINT_SET_SIMPLE_MAP_H_

#include <iostream>
#include <map>

namespace algorithms {
namespace disjoint_set_simple_map {

template <typename Key>
struct disjoint_set {
    typedef std::map<Key, Key> parent_type;
    parent_type parent;

    disjoint_set() {}

    ~disjoint_set() {}

    int find(int s) {
        check_insert(s);

        int root = s;
        while (root != parent[root]) {
            root = parent[root];
        }
        return root;
    }

    void join(int x, int y) {
        Key root_x = find(x);
        Key root_y = find(y);

        parent[root_x] = root_y;
    }

    void check_insert(int s) {
        if (parent.find(s) == parent.end()) {
            parent[s] = s;
        }
    }

    void print() {
        typename parent_type::iterator it = parent.begin();
        for (; it != parent.end(); ++it) {
            std::cout << it->first << ":" << it->second << std::endl;
        }
    }

    disjoint_set(const disjoint_set &) = delete;
    disjoint_set &operator=(const disjoint_set &) = delete;
};

inline void test() {
    disjoint_set<int> s;

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

    std::cout << "disjoint_set_simple_map::disjoint_set OK" << std::endl;
}

} // namespace disjoint_set_simple_map
} // namespace algorithms

#endif /* ALGORITHMS_DISJOINT_SET_SIMPLE_MAP_H_ */
