//
// Based on https://kukuruku.co/post/avl-trees/
//

#ifndef ALGORITHMS_AVL_TREE_H_
#define ALGORITHMS_AVL_TREE_H_

#include <algorithm>
#include <utility>
#include <stdint.h>

namespace algorithms {
namespace avl_tree {

namespace internal {

template <typename T>
struct node {
    typedef T value_type;

    value_type value;
    uint64_t height;
    node* left;
    node* right;

    node* parent;
    node(const value_type& v)
        : value(v), height(1), left(0), right(0), parent(0) {}

    ~node() {
    }
};

template <typename T, typename Reference, typename Pointer>
class avl_tree_iterator {
public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Pointer pointer;
    typedef Reference reference;
    typedef T node_type;

    avl_tree_iterator(): current(0) {}

    avl_tree_iterator(T* p)
        : current(p) {}

    avl_tree_iterator(const avl_tree_iterator& it)
        : current(it.current) {}

    avl_tree_iterator& operator=(const avl_tree_iterator& it) {
        if(&it == this) {
            return *this;
        }
        current = it.current;
        return *this;
    }

    reference operator*() {
        return current->value;
    }

    pointer operator->() {
        return &current->value;
    }

    bool operator==(const avl_tree_iterator& o) {
        return current == o.current;
    }

    bool operator!=(const avl_tree_iterator& o) {
        return ! operator==(o);
    }

    avl_tree_iterator operator++() {
        throw std::runtime_error("operator++ not implemented");
    }

    node_type* current_ptr() {
       return current;
    }
private:
    node_type* current;
};

}

template <typename K, typename T, typename Compare = std::less<T> >
class avl_tree {
public:
    typedef size_t size_type;
    typedef K key_type;
    typedef T mapped_type;
    typedef std::pair<const K, T> value_type;
    typedef Compare key_compare;
    typedef internal::node<value_type> node_type;
    typedef internal::avl_tree_iterator<node_type, value_type&, value_type*> iterator;

    avl_tree() {}
    avl_tree(const Compare& comp): compare(comp) {}
    avl_tree(const avl_tree& o) = delete;
    avl_tree(avl_tree&& o) noexcept {
        root = o.root;
        compare = o.compare;
        size_ = o.size_;

        o.root = 0;
        o.size_ = 0;
    }

    avl_tree& operator=(const avl_tree& o) = delete;
    avl_tree& operator=(avl_tree&& o) {
        if(this == &o) {
            return *this;
        }
        std::swap(root, o.root);
        std::swap(compare, o.compare);
        std::swap(size_, o.size_);

        return *this;
    }

    ~avl_tree() noexcept {
        node_type* n = root;
        r_delete(n);
    }

    void insert(const value_type& v) {
        root = insert(root, v);
        ++size_;
    }

    iterator find(const key_type& k) {
        node_type* n = find(root, k);
        iterator i(n);
        return i;
    }

    size_type erase(const K& k) {
        iterator i(find(k));
        if(i == end()) {
            return 0;
        }
        root = remove(root, k);
        --size_;
        return 1;
    }

    iterator erase(iterator it) {
        if(it == end()) {
            return end();
        }

        iterator i(find(it->first));
        if(i == end()) {
            return end();
        }

        iterator rc(it.current_ptr()->right);
        root = remove(root, it->first);
        return rc;
    }

    iterator begin() {
        node_type* n = findmin(root);
        return iterator(n);
    }

    iterator end() {
        return iterator(0);
    }

    size_type size() {
        return size_;
    }

private:
    Compare compare;
    node_type *root = 0;
    size_type size_ = 0;

    uint64_t height(node_type* p) {
        return p ? p->height : 0;
    }

    int bfactor(node_type* p) {
        return height(p->right) - height(p->left);
    }

    void fixheight(node_type* p) {
        unsigned char hl = height(p->left);
        unsigned char hr = height(p->right);
        p->height = (hl>hr ? hl : hr) + 1;
    }

    node_type* rotateright(node_type* p) {
        node_type* q = p->left;
        p->left = q->right;
        q->right = p;
        fixheight(p);
        fixheight(q);
        return q;
    }

    node_type* rotateleft(node_type* q) {
        node_type* p = q->right;
        q->right = p->left;
        p->left = q;
        fixheight(q);
        fixheight(p);
        return p;
    }

    node_type* balance(node_type* p) {
        fixheight(p);
        if( bfactor(p)==2 ) {
            if( bfactor(p->right) < 0 )
                p->right = rotateright(p->right);

            return rotateleft(p);
        }
        if( bfactor(p)==-2 ) {
            if( bfactor(p->left) > 0  )
                p->left = rotateleft(p->left);

            return rotateright(p);
        }

        return p;
    }

    node_type* find(node_type* p, const key_type& key) {
        while(1) {
            if(p == 0) {
                return 0;
            }
            if(p->value.first == key) {
                return p;
            }
            else if(compare(p->value.first, key)) {
                p = p->right;
            }
            else { // p->value.first > key if key_compare 'less'
                p = p->left;
            }
        }
    }

    node_type* find(node_type* p, node_type* to_find) {
        return find(p, to_find->value.first);
    }

    // remove
    node_type* findmin(node_type* p) {
        return p->left ? findmin(p->left):p;
    }

    node_type* insert(node_type* p, const value_type& v) {
        if( !p )
            return new node_type(v);

        if(v.first == p->value.first) {
            throw std::logic_error("Can not insert duplicated key");
        }
        if( compare(v.first, p->value.first))
            p->left = insert(p->left, v);
        else
            p->right = insert(p->right, v);
        return balance(p);
    }

    node_type* removemin(node_type* p) {
        if( p->left == 0 ) {
            return p->right;
        }

        p->left = removemin(p->left);
        return balance(p);
    }

    node_type* remove(node_type* p, int k) {
        if( !p )
            return 0;

        if( k < p->value.first ) {
            p->left = remove(p->left,k);
        }
        else if( k > p->value.first ) {
            p->right = remove(p->right,k);
        }
        else //  k == p->key
        {
            node_type* q = p->left;
            node_type* r = p->right;
            delete p;

            if( !r ) {
                return q;
            }

            node_type* min = findmin(r);
            min->right = removemin(r);
            min->left = q;
            return balance(min);
        }

        return balance(p);
    }

    void r_delete(node_type* n) {
        if (n == 0)
            return;

        r_delete(n->left);
        r_delete(n->right);

        delete n;
        n = 0;
    }
};

void test(void);

}
}


#endif /* ALGORITHMS_AVL_TREE_H_ */
