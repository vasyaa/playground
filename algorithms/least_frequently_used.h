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

#include <algorithm>
#include <map>
#include <ostream>
#include <deque>
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

    struct my_compare {
        bool operator()(const map_iterator &lh, const map_iterator &rh) {
            return lh->second.counter > rh->second.counter;
        }
    };

//    using queue_type =
//        std::priority_queue<map_iterator, std::vector<map_iterator>,
//                            my_compare>;
    using queue_type =
        std::deque<map_iterator>;

    least_frequently_used(const size_t cap) : capacity_(cap) {}

    void add(const K &key, const V &val) {
        if (q.size() == capacity_) {
            map_iterator it = q.front();
//            q.pop_front();
            m.erase(it);
        }

        std::pair<map_iterator, bool> rc =
            m.insert(std::make_pair(key, internal::node<V>(val)));
        if (q.size() == capacity_) {
           std::swap(q.front(), rc.first);
//           std::make_heap(q.begin(), q.end(), my_compare());
        }
        else {
            q.push_front(rc.first);
        }
    }

    bool exists(const K &key) {
        return m.find(key) != m.end();
    }

    V &get(const K &key) {
        map_iterator it = m.find(key);
        if (it == m.end()) {
            throw std::runtime_error("out of bounds index=");
        }
        it->second.counter += 1;
        std::make_heap(q.begin(), q.end(), my_compare());
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
        str << "top: " << q.front()->first << " " << q.front()->second << " -> ";
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

void test();

} // namespace test

} // namespace least_frequently_used

#endif /* ALGORITHMS_LEAST_FREQUENTLY_USED_H_ */
