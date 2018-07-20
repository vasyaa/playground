#include "../algorithms/avl_tree.h"
#include <cassert>
#include <iostream>

using namespace std;

namespace algorithms {
namespace avl_tree {

namespace {

const int N = 10;
typedef algorithms::avl_tree::avl_tree<int, int> tree_type;

void fill_tree(tree_type &t) {
    for (int i = 0; i < N; i++) {
        t.insert(std::make_pair(i, i + N));
    }
}

void print_tree(tree_type &t) {
    tree_type::iterator it;
    for (int i = 0; i < N; i++) {
        it = t.find(i);

        if (it != t.end()) {
            cout << it->second << " ";
        }
        else {
            cout << i << " not found ";
        }
    }
    cout << endl;
}

void test1() {

    tree_type t;
    tree_type::iterator it;

    fill_tree(t);
    for (int i = 0; i < N; i++) {
        it = t.find(i);
        assert(N + i == it->second);
        //        cout << it->second << endl;
    }
    cout << endl;

    it = t.find(8);
    assert(it != t.end());
    assert(8 == it->first);
    assert(N + 8 == it->second);

    //    cout << it->second << endl << endl;;

    bool rc = t.erase(5);
    assert(rc == true);

    it = t.find(2);
    it = t.erase(it);
    //    assert();

    for (int i = 0; i < N; i++) {
        it = t.find(i);

        if (it != t.end()) {
            //            cout << it->second << endl;
            assert(!(i == 2 || i == 5));
        }
        else {
            //            cout << i << " not found" << endl;
            assert(i == 2 || i == 5);
        }
    }
}

void test2() {
    typedef algorithms::avl_tree::avl_tree<int, int> tree_type;

    tree_type t1;
    tree_type t2;

    fill_tree(t1);

    t2 = std::move(t1);
    //    t2 = t1;

    print_tree(t1);
    print_tree(t2);
}

} // namespace

void test(void) {
    test1();
    test2();
}

} // namespace avl_tree
} // namespace algorithms
