#include "disjoint_set.h"
#include <iostream>

namespace algorithm {

namespace disjoint_set {

typedef disjoint_set<int> set_type;

void fill_data(set_type &s) {
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);

    s.merge(1, 6);
    s.merge(2, 7);
    s.merge(3, 8);
    s.merge(4, 9);
    s.merge(2, 6);
}

void test1() {
    set_type s;
    fill_data(s);

    set_type::map_type::iterator it;

    size_t minval = 1000000;
    size_t maxval = 0;
    for (int i = 0; i < 10; i++) {
        set_type::node_type *n = s.find(i);
        if (n) {
            if (n->size() > 1) {
                minval = std::min(minval, n->size());
            }
            maxval = std::max(maxval, n->size());
        }
    }
    std::cout << minval << " " << maxval << std::endl;
}

void test2() {
    set_type s1;
    fill_data(s1);

    set_type s2;

    s2 = std::move(s1);

    std::cout << s1.size() << std::endl;
}
void test() {
    test1();
    test2();
}

} // namespace disjoint_set
} // namespace algorithm
