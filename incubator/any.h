/*
 * any_incubator.h
 *
 *  Created on: Jul 3, 2018
 *      Author: vasyaa
 */

#ifndef INCUBATOR_ANY_H_
#define INCUBATOR_ANY_H_

#include <iostream>

#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace any {

class any;

namespace internal {

template <typename T>
T any_cast(any &o);

template <typename T>
T *any_cast(any *o);

} // namespace internal

class any_holder {
public:
    friend class any;

    template <typename T>
    friend T internal::any_cast(any &o);

    template <typename T>
    friend T *internal::any_cast(any *o);

    template <typename T>
    any_holder(const T &t) : info(typeid(T)) {
        ptr_ = (void *)new T(t);
        deleter = [](void *p) { delete (T *)p; };
    }

    ~any_holder() { deleter(ptr_); }

private:
    const std::type_info &info;
    void *ptr_ = nullptr;
    std::function<void(void *)> deleter = [](void *p) {};
};

class any {
public:
    template <typename T>
    friend T internal::any_cast(any &o);

    template <typename T>
    friend T *internal::any_cast(any *o);

    any() {}

    template <typename T>
    any(const T &t) {
        holder = std::shared_ptr<any_holder>(new any_holder(t));
    }

    explicit any(const any &o) { holder = o.holder; }

    explicit any(any &&o) {
        holder = std::move(o.holder);
        o.holder = nullptr;
    }

    template <typename T>
    any &operator=(const T &t) {
        holder = std::shared_ptr<any_holder>(new any_holder(t));
        return *this;
    }

    any &operator=(const any &o) {
        if (this == &o) {
            return *this;
        }
        holder = o.holder;
        return *this;
    }

    any &operator=(any &&o) {
        if (this == &o) {
            return *this;
        }
        holder = std::move(o.holder);
        o.holder = nullptr;
        return *this;
    }

    template <class T, class... Args>
    void emplace(Args &&... args);

    template <class T, class U, class... Args>
    void emplace(std::initializer_list<U> il, Args &&... args);

    void reset() noexcept { holder = nullptr; }

    void swap(any &other) { std::swap(holder, other.holder); }

    bool has_value() const noexcept { return holder != nullptr; }

    const std::type_info &type() const { return holder->info; }

private:
    std::shared_ptr<any_holder> holder;
};

namespace internal {

template <typename T>
T *any_cast(any *o) {
    if (o->holder->info != typeid(T)) {
        std::ostringstream str;
        str << "Can not convert " << o->holder->info.name() << " to "
            << typeid(T).name();
        throw std::runtime_error(str.str());
    }
    return static_cast<T *>(o->holder->ptr_);
}

template <typename T>
T any_cast(any &o) {
    if (o.holder->info != typeid(T)) {
        std::ostringstream str;
        str << "Can not convert " << o.holder->info.name() << " to "
            << typeid(T).name();
        throw std::runtime_error(str.str());
    }
    return (*static_cast<T *>(o.holder->ptr_));
}

} // namespace internal

template <typename T>
T any_cast(const any &o) {
    return internal::any_cast<T>((any &)o);
}

template <typename T>
T any_cast(any &o) {
    return internal::any_cast<T>(o);
}

template <typename T>
T any_cast(any &&o) {
    return internal::any_cast<T>(o);
}

template <typename T>
const T *any_cast(const any *o) {
    return internal::any_cast<T>((any *)o);
}

template <typename T>
T *any_cast(any *o) {
    return internal::any_cast<T>(o);
}

// template< class T, class... Args >
// std::any make_any( Args&&... args );
//
// template< class T, class U, class... Args >
// std::any make_any( std::initializer_list<U> il, Args&&... args );

namespace test {

void test();
}
} // namespace any

#endif /* INCUBATOR_ANY_H_ */
