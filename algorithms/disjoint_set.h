#ifndef DISJOINT_SET_H_
#define DISJOINT_SET_H_

#include <map>
#include <cstdlib>
#include <utility>

namespace algorithm {

namespace disjoint_set {

template <typename K>
class disjoint_set;

namespace internal {

template <typename K>
struct node {
    friend class disjoint_set<K>;
    typedef size_t size_type;

    node(): P(this), rank(0), size_(1) {}

    size_type size() {
        return size_;
    }

private:
    node(const node& n);
    node& operator=(const node& n);

    node* P;
    int rank;
    size_type size_;
};

}

template <typename K>
class disjoint_set {
public:
    typedef internal::node<K> node_type;
    typedef std::map<int, node_type*> map_type;
    typedef size_t size_type;

    disjoint_set(){}

    disjoint_set(disjoint_set&& o) {
        m = std::move(o.m);
    }

    disjoint_set& operator=(disjoint_set&& o) {
        if(this == &o) {
            return *this;
        }
        m = std::move(o.m);
        return *this;
    }

    ~disjoint_set() {
        typename map_type::iterator it = m.begin();
        while(it != m.end()) {
            it = m.erase(it);
        }
    }

    void insert(const K& k) {
        if(m.find(k) != m.end()) {
            throw std::logic_error("Duplicated item");
        }

        node_type* n = new node_type();
        m.insert(std::make_pair(k, n));
    }

    void merge(const K& x, const K& y) {
        merge(m[x], m[y]);
    }

    bool joined(const K& x, const K& y) {
        node_type* px = find(x);
        if(!px) {
            return false;
        }
        node_type* py = find(y);
        if(!py) {
            return false;
        }

        return px == py;
    }

    node_type* find(const K& x) {
        typename map_type::iterator it = m.find(x);
        if(it == m.end()) {
            return 0;
        }
        node_type* n = find(it->second);
        return n;
    }

    size_type size() {
        return m.size();
    }

private:
    map_type m;

    node_type* find(node_type* x) {
        if(x != x->P)
            x->P = find(x->P);
        return x->P;
    }

    void merge(node_type* x, node_type* y) {
        node_type *px = find(x);
        node_type *py = find(y);

        if(px == py)
            return;

        if(px->rank > py->rank) {
            py->P = px;
            px->size_ += py->size_;
        }
        else {
            px->P = py;
            py->size_ += px->size_;
        }

        if(px->rank == py->rank) {
            py->rank = py->rank + 1;
        }
    }
};

// test
void test(void);

}
}

#endif /* DISJOINT_SET_H_ */
