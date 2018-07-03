/*
 * any_incubator.h
 *
 *  Created on: Jul 3, 2018
 *      Author: vasyaa
 */

#ifndef INCUBATOR_SIMPLE_ANY_H_
#define INCUBATOR_SIMPLE_ANY_H_

#include <iostream>

#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace simple_any {

class any;

namespace internal {

template <typename T>
T any_cast(any& o);

template <typename T>
T* any_cast(any* o);

}

class any_holder {
public:
    friend class any;

    template <typename T>
    friend T internal::any_cast(any& o);

    template <typename T>
    friend T* internal::any_cast(any* o);

    template <typename T>
    any_holder(const T& t): info(typeid(T)) {
        ptr_ = (void*)new T(t);
        deleter = [](void* p) {delete (T*)p;};
    }

    ~any_holder() {
        deleter(ptr_);
    }
private:
    const std::type_info& info;
    void* ptr_ = nullptr;
    std::function<void(void*)> deleter = [](void* p){};
};


class any {
public:
    template <typename T>
    friend T internal::any_cast(any& o);

    template <typename T>
    friend T* internal::any_cast(any* o);

    any() {}

    template <typename T>
    any(const T& t) {
        holder = std::shared_ptr<any_holder>(new any_holder(t));
    }

    explicit any(const any& o) {
        holder = o.holder;
    }

    explicit any(any&& o) {
        holder = std::move(o.holder);
        o.holder = nullptr;
    }

    template <typename T>
    any& operator=(const T& t) {
        holder = std::shared_ptr<any_holder>(new any_holder(t));
        return *this;
    }

    any& operator=(const any& o) {
        if(this == &o) {
            return *this;
        }
        holder = o.holder;
        return *this;
    }

    any& operator=(any&& o) {
        if(this == &o) {
            return *this;
        }
        holder = std::move(o.holder);
        o.holder = nullptr;
        return *this;
    }

    template< class T, class... Args >
    void emplace( Args&&... args );

    template< class T, class U, class... Args >
    void emplace( std::initializer_list<U> il, Args&&... args );

    void reset() noexcept {
        holder = nullptr;
    }

    void swap(any& other) {
        std::swap(holder, other.holder);
    }

    bool has_value() const noexcept {
        return holder != nullptr;
    }

    const std::type_info& type() const {
        return holder->info;
    }
private:
    std::shared_ptr<any_holder> holder;
};

namespace internal {

template <typename T>
T* any_cast(any* o) {
    if(o->holder->info != typeid(T)) {
        std::ostringstream str;
        str << "Can not convert " << o->holder->info.name() << " to " << typeid(T).name();
        throw std::runtime_error(str.str());
    }
    return static_cast<T*>(o->holder->ptr_);
}

template <typename T>
T any_cast(any& o) {
    if(o.holder->info != typeid(T)) {
        std::ostringstream str;
        str << "Can not convert " << o.holder->info.name() << " to " << typeid(T).name();
        throw std::runtime_error(str.str());
    }
    return (*static_cast<T*>(o.holder->ptr_));
}

} // end ns

template <typename T>
T any_cast(const any& o) {
    return internal::any_cast<T>((any&)o);
}

template <typename T>
T any_cast(any& o) {
    return internal::any_cast<T>(o);
}

template <typename T>
T any_cast(any&& o) {
    return internal::any_cast<T>(o);
}

template <typename T>
const T* any_cast(const any* o) {
    return internal::any_cast<T>((any*)o);
}

template <typename T>
T* any_cast(any* o) {
    return internal::any_cast<T>(o);
}

//template< class T, class... Args >
//std::any make_any( Args&&... args );
//
//template< class T, class U, class... Args >
//std::any make_any( std::initializer_list<U> il, Args&&... args );

inline void test() {
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
    }
    catch (const std::exception& e) {
        std::cout << "Expected exception " << e.what()
                  << " at " << __FILE__ << ":" << __LINE__
                  << std::endl;
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

    any* pa = new any(62);
    std::cout << *any_cast<int>(pa) << std::endl;

    const any* pca = new any(72);
    std::cout << *any_cast<int>(pca) << std::endl;

    delete pa;
    delete pca;
}

}


#endif /* INCUBATOR_SIMPLE_ANY_H_ */
