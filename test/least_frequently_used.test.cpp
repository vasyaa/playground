#include "../incubator/least_frequently_used.h"

#define ASSERT(expr) do {\
    if(!(expr)) { \
    std::cerr << "Assertion failed \"" #expr "\"" << std::endl; \
    abort(); \
    } \
    } while(0)

namespace least_frequently_used {
namespace test {

void test2() {
    using lfu_type = least_frequently_used<int, int>;

    lfu_type lfu(5);

    for (int i = 0; i < 16; i++) {
        lfu.insert(i, i);
        if (i == 5) {
            lfu.get(i);
            lfu.get(i);
        }
        if (i == 12) {
            lfu.get(i);
            lfu.get(i);
            lfu.get(i);
            lfu.print();
            std::cout << std::endl;
        }
        if (i == 2) {
            lfu.get(i);
            lfu.get(i);
        }
        if (i == 8) {
            lfu.get(i);
            lfu.get(i);
        }
        if (i == 9) {
            lfu.print();
            std::cout << std::endl;
            lfu.get(i);
            lfu.get(i);
            lfu.print();
            std::cout << std::endl;
        }
    }

    lfu.print();
    std::cout << std::endl;

    ASSERT(lfu.exists(11) == false);
    ASSERT(lfu.get_count(12) == 4);
    ASSERT(lfu.get_count(5) == 3);
    ASSERT(lfu.get_count(8) == 3);
}

void test1() {
    using lfu_type = least_frequently_used<int, int>;

    lfu_type lfu(5);

    for (int i = 0; i < 16; i++) {
        lfu.insert(i, i);
    }
    lfu.get(11);
    lfu.erase(12);

    lfu.print();
}


void test() {
    test1();
    test2();
}

} // namespace test
} // namespace least_frequently_used
