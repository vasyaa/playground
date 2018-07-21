/*
 * least_frequently_used.h
 *
 *  Created on: Jul 18, 2018
 *      Author: vasyaa
 */

#ifndef ALGORITHMS_LEAST_FREQUENTLY_USED_H_
#define ALGORITHMS_LEAST_FREQUENTLY_USED_H_

#include <cassert>
#include <iostream>
#include <sstream>

#include <algorithm>
#include <map>
#include <ostream>
#include <set>
#include <vector>

namespace least_frequently_used {

namespace internal {

template <typename V>
struct node {
    V value;
    int counter;

    node() : counter(-1) {}
    explicit node(const V &val, int counter_ = -1)
        : value(val), counter(counter_) {}

    friend std::ostream &operator<<(std::ostream &str, const node &o) {
        str << "[value=" << o.value << " counter=" << o.counter << "]";
        return str;
    }
};

} // namespace internal

template <typename K, typename V>
class least_frequently_used {
public:
    using map_objects_type = std::map<K, internal::node<V>>;
    using object_iterator = typename map_objects_type::iterator;

    struct my_compare {
        bool operator()(const object_iterator &lh,
                        const object_iterator &rh) const {
            return lh->second.counter < rh->second.counter;
        }
    };

    using map_freq_type = std::map<int, std::set<K>>;
    using freq_iterator = typename map_freq_type::iterator;

    least_frequently_used(const size_t cap) : capacity_(cap) {}

    void insert(const K &key, const V &val, int n = 1) {
        if (m.size() == capacity_) {
            const int counter = f.begin()->first;
            K erase_key = *f[counter].begin();
            erase(erase_key);
        }

        std::pair<object_iterator, bool> rc =
            m.insert(std::make_pair(key, internal::node<V>(val, n)));

        object_iterator it = rc.first;
        int counter = it->second.counter;
        f[counter].insert(key);
    }

    bool erase(const K &key) {
        check_exists_throw(key);

        int counter = m[key].counter;
        f[counter].erase(key);
        if (f[counter].empty()) {
            f.erase(counter);
        }
        m.erase(key);

        return true;
    }

    bool exists(const K &key) {
        bool rc = m.find(key) != m.end();
        return rc;
    }

    V &get(const K &key) {
        check_exists_throw(key);

        int counter = m[key].counter;
        V value = m[key].value;

        erase(key);

        insert(key, value, counter + 1);
        return m[key].value;
    }

    int get_count(const K &key) { return m[key].counter; }

    size_t size() { return m.size();}
    size_t capacity() { return capacity_;}

    void print() {
        print_objs();
        std::cout << std::endl;
        print_freq();
    }

private:
    map_objects_type m;
    map_freq_type f;
    size_t capacity_;

    void check_exists_throw(const K &key) {
        if (!exists(key)) {
            std::ostringstream str;
            str << "Key not exists in obj_map key=" << key;
            throw std::runtime_error(str.str());
        }
        int counter = m[key].counter;
        if (f[counter].find(key) == f[counter].end()) {
            std::ostringstream str;
            str << "Key not exists in freq_map counter=" << counter
                << " key=" << key;
            throw std::runtime_error(str.str());
        }
    }

    void print_one_obj(const K &key) {
        auto i = m.find(key);
        std::cout << "[key=" << i->first << " value=" << i->second << "]";
    }

    void print_objs() {
        std::cout << "objects=   ";
        auto i = m.begin();
        for (; i != m.end(); ++i) {
            print_one_obj(i->first);
        }
    }

    void print_freq() {
        auto j = f.begin();
        for (; j != f.end(); ++j) {
            auto i = j->second.begin();
            for (; i != j->second.end(); ++i) {
                std::cout << "counter=" << j->first << "->";
                print_one_obj(*i);
            }
            std::cout << std::endl;
        }
    }
};

namespace test {

void test();

} // namespace test

} // namespace least_frequently_used

#endif /* ALGORITHMS_LEAST_FREQUENTLY_USED_H_ */
