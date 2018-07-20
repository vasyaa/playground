#include "../incubator/any.h"

namespace any {

namespace test {

void test() {
    any a(123);
    any b = 234;
    any c;

    c = 3456;

    any d;
    d = a;

    any e(a);

    std::cout << any_cast<int>(a) << std::endl;
    std::cout << any_cast<int>(b) << std::endl;
    std::cout << any_cast<int>(c) << std::endl;
    std::cout << any_cast<int>(d) << std::endl;
    std::cout << any_cast<int>(e) << std::endl;

    try {
        any f = any(a);
        std::cout << any_cast<int>(f) << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Expected exception " << e.what() << " at " << __FILE__
                  << ":" << __LINE__ << std::endl;
    }

    a = b = c = d = e;
    std::cout << any_cast<int>(a) << std::endl;
    std::cout << any_cast<int>(e) << std::endl;

    //    any g(any(a));
    //    std::cout << any_cast<int>(g) << std::endl;

    //    int x = 5;
    //    int y(int(int(x)));
    //    std::cout << y << std::endl;

    const any ca(23);
    std::cout << any_cast<int>(ca) << std::endl;

    any *pa = new any(62);
    std::cout << *any_cast<int>(pa) << std::endl;

    const any *pca = new any(72);
    std::cout << *any_cast<int>(pca) << std::endl;

    delete pa;
    delete pca;
}
}

} // namespace simple_any
