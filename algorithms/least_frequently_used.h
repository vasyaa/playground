/*
 * least_frequently_used.h
 *
 *  Created on: Jul 18, 2018
 *      Author: vasyaa
 */

#ifndef ALGORITHMS_LEAST_FREQUENTLY_USED_H_
#define ALGORITHMS_LEAST_FREQUENTLY_USED_H_

#include <iostream>
#include <cassert>

#include <algorithm>
#include <deque>
#include <queue>
#include <map>
#include <ostream>
#include <vector>

namespace least_frequently_used {

namespace internal {

template <typename V>
struct node {
    V value;
    int counter;

    node() : counter(0) {}
    explicit node(const V &val) : value(val), counter(1) {}

    friend std::ostream &operator<<(std::ostream &str, const node &o) {
        str << o.value << " (" << o.counter << ")";
        return str;
    }
};

} // namespace internal

template <typename K, typename V>
class least_frequently_used {
public:
    using map_type = std::map<K, internal::node<V>>;
    using map_iterator = typename map_type::iterator;
//    using queue_type = std::deque<map_iterator>;
    struct my_compare {
        bool operator()(const map_iterator &lh, const map_iterator &rh) {
            return lh->second.counter > rh->second.counter;
        }
    };

    using queue_type = std::priority_queue<map_iterator, std::vector<map_iterator>, my_compare>;

    least_frequently_used(const size_t cap) : capacity_(cap) {}

    void add(const K &key, const V &val) {
        if (q.size() == capacity_) {
            map_iterator it = q.top();
            q.pop();
            m.erase(it);
        }

        std::pair<map_iterator, bool> rc =
                m.insert(std::make_pair(key, internal::node<V>(val)));
        q.push(rc.first);
    }

    V &get(const K &key) {
        map_iterator it = m.find(key);
        if (it == m.end()) {
            throw std::runtime_error("out of bounds index=");
        }
        it->second.counter += 1;
        return it->second.value;
    }

    const int &get_count(const K &key) {
        map_iterator it = m.find(key);
        if (it == m.end()) {
            throw std::runtime_error("out of bounds index=");
        }
        return it->second.counter;
    }

    void print(std::ostream &str) {
        map_iterator it = m.begin();
        str << "top: " << q.top()->first << " " << q.top()->second << " -> ";
        for (; it != m.end(); ++it) {
            str << it->first << " " << it->second << ", ";
        }
    }
private:
    queue_type q;
    map_type m;
    size_t capacity_;

};

namespace test {

inline void test() {
    using lfu_type = least_frequently_used<int, int>;

    lfu_type lfu(5);

    for (int i = 0; i < 16; i++) {
        lfu.add(i, i);
        if(i == 5) {
            lfu.get(i);
            lfu.get(i);
        }
    }

    lfu.print(std::cout);
    std::cout << std::endl;

    assert(lfu.get_count(5) == 3);
}

} // namespace test

} // namespace least_frequently_used

#endif /* ALGORITHMS_LEAST_FREQUENTLY_USED_H_ */