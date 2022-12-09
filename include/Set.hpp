#include <cstddef>
#include <exception>
#include <initializer_list>
#include <algorithm>
#include <cmath>
#include <iostream>

template<typename T>
class Set {
private:
    class Node {
    public:
        T val;
        Node* left;
        Node* right;
        Node* parent;
        Node* most_left;
        Node* most_right;
        long long height;

        Node(T val) {
            this->val = val;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
            this->height = 1;
            this->most_left = this;
            this->most_right = this;
        }
    };

    Node* root = nullptr;
    size_t tree_size = 0;

    bool equal(const T a, const T b) const {
        return (!(a < b) && !(b < a));
    }

    void fix(Node* node) {
        if (node) {
            long long left_height = node->left ? node->left->height : 0;
            long long right_height = node->right ? node->right->height : 0;
            node->height = std::max(left_height, right_height) + 1;
            node->most_left = node->most_right = node;
            node->parent = nullptr;
            if (node->left) {
                node->left->parent = node;
                node->most_left = node->left->most_left;
            }
            if (node->right) {
                node->right->parent = node;
                node->most_right = node->right->most_right;
            }
        }
    }

    long long get_balance(Node* node) {
        long long left_height = node->left ? node->left->height : 0;
        long long right_height = node->right ? node->right->height: 0;
        return right_height - left_height;
    }

    Node* rotate_left(Node* node) {
        Node* q = node->right;
        node->right = q->left;
        q->left = node;
        fix(node);
        fix(q);
        return q;
    }

    Node* rotate_right(Node* node) {
        Node* q = node->left;
        node->left = q->right;
        q->right = node;
        fix(node);
        fix(q);
        return q;
    }

    Node* balance(Node* node) {
        if (node) {
            fix(node);
            long long node_balance = get_balance(node);
            if (node_balance == 2) {
                if (get_balance(node->right) < 0) {
                    node->right = rotate_right(node->right);
                }
                return rotate_left(node);
            } else {
                if (node_balance == -2) {
                    if (get_balance(node->left) > 0) {
                        node->left = rotate_left(node->left);
                    }
                    return rotate_right(node);
                }
            }
        }
        return node;
    }

    Node* insert_(Node* node, const T x){
        if (!node) {
            tree_size++;
            return new Node(x);
        }
        if (equal(x, node->val)) {
            return node;
        }
        if (x < node->val) {
            node->left = insert_(node->left, x);
        } else {
            node->right = insert_(node->right, x);
        }
        return balance(node);
    }

    Node* erase_(Node* node, const T x) {
        if (!node) {
            return nullptr;
        }
        if (equal(x, node->val)) {
            tree_size--;
            Node* left_child = node->left;
            Node* right_child = node->right;
            if (!left_child && !right_child) {
                delete node;
                return nullptr;
            }
            else if (!left_child) {
                delete node;
                return right_child;
            }
            else if (!right_child) {
                delete node;
                return left_child;
            }
            Node* m = find_min(node->right);
            m->right = delete_min(node->right);
            m->left = node->left;
            return balance(m);
        }
        if (node->val < x) {
            node->right = erase_(node->right, x);
        } else {
            node->left = erase_(node->left, x);
        }
        return balance(node);
    }

    Node* find_min(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* delete_min(Node* node) {
        if (!node->left) {
            return node->right;
        }
        node->left = delete_min(node->left);
        return balance(node);
    }

    Node* find_(Node* node, const T x) const {
        if (!node) {
            return nullptr;
        }
        if (equal(node->val, x)) {
            return node;
        }
        if (x < node->val) {
            return find_(node->left, x);
        }
        return find_(node->right, x);
    }

    Node* lower_bound_(Node* node, const T x) const {
        if (!node) {
            return nullptr;
        }
        if (equal(node->val, x)) {
            return node;
        }
        if (x < node->val) {
            Node* bound = lower_bound_(node->left, x);
            if (!bound || node->val < bound->val) {
                return node;
            }
            return bound;
        }
        return lower_bound_(node->right, x);
    }

    Node* deep_copy_(Node* node) {
        if (!node) {
            return nullptr;
        }
        Node* new_node = new Node(node->val);
        new_node->left = deep_copy_(node->left);
        new_node->right = deep_copy_(node->right);
        fix(new_node);
        return new_node;
    }

    void clean_(Node* node) {
        if (!node) {
            return;
        }
        clean_(node->left);
        clean_(node->right);
        delete node;
    }

public:
    class SetIterator {
    private:
        const Set<T>* s;
        const Node* cur_elem;
        bool end;
    public:
        SetIterator(const Set<T>* s=nullptr, const Node* cur_elem=nullptr, bool end=false) {
            this->s = s;
            this->cur_elem = cur_elem;
            this->end = end;
        }

        bool operator!=(const SetIterator& other) const {
            if ((s->root != other.s->root) || (end != other.end) || (cur_elem != other.cur_elem)) {
                return true;
            }
            return false;
        }

        bool operator==(const SetIterator& other) const {
            return !(*this != other);
        }

        SetIterator& operator++() {
            if (end) {
                throw std::exception();
            }
            if (s->root->most_right == cur_elem) {
                end = true;
                cur_elem = nullptr;
                return *this;
            }
            if (cur_elem->right) {
                cur_elem = cur_elem->right;
                while (cur_elem->left) {
                    cur_elem = cur_elem->left;
                }
                return *this;
            }
            while (cur_elem->parent->right == cur_elem) {
                cur_elem = cur_elem->parent;
            }
            cur_elem = cur_elem->parent;
            return *this;
        }

        SetIterator operator++(int) {
            if (end) {
                throw std::exception();
            }
            auto old_s = SetIterator(s, cur_elem, end);
            if (s->root->most_right == cur_elem) {
                end = true;
                cur_elem = nullptr;
                return *this;
            }
            if (cur_elem->right) {
                cur_elem = cur_elem->right;
                while (cur_elem->left) {
                    cur_elem = cur_elem->left;
                }
                return old_s;
            }
            while (cur_elem->parent->right == cur_elem) {
                cur_elem = cur_elem->parent;
            }
            cur_elem = cur_elem->parent;
            return old_s;
        }

        SetIterator& operator--() {
            if (s->root->most_left == cur_elem) {
                throw std::exception();
            }
            if (end) {
                end = false;
                cur_elem = s->root->most_right;
                return *this;
            }
            if (cur_elem->left) {
                cur_elem = cur_elem->left;
                while (cur_elem->right) {
                    cur_elem = cur_elem->right;
                }
                return *this;
            }
            while (cur_elem->parent->left == cur_elem) {
                cur_elem = cur_elem->parent;
            }
            cur_elem = cur_elem->parent;
            return *this;
        }

        SetIterator operator--(int) {
            if (s->root->most_left == cur_elem) {
                throw std::exception();
            }
            auto old_s = SetIterator(s, cur_elem, end);
            if (end) {
                end = false;
                cur_elem = s->root->most_right;
                return old_s;
            }
            if (cur_elem->left) {
                cur_elem = cur_elem->left;
                while (cur_elem->right) {
                    cur_elem = cur_elem->right;
                }
                return old_s;
            }
            while (cur_elem->parent->left == cur_elem) {
                cur_elem = cur_elem->parent;
            }
            cur_elem = cur_elem->parent;
            return old_s;
        }

        const T& operator*() {
            return cur_elem->val;
        }

        const T* operator->() {
            return &(cur_elem->val);
        }

        SetIterator& operator=(const SetIterator& other) {
            s = other.s;
            cur_elem = other.cur_elem;
            end = other.end;
            return *this;
        }
    };

    using iterator = SetIterator;

    Set() {
        root = nullptr;
        tree_size = 0;
    }

    template<class I>
    Set(I iter1, I iter2) {
        root = nullptr;
        tree_size = 0;
        for (; iter1 != iter2; ++iter1) {
            root = insert_(root, *iter1);
        }
    }

    Set(std::initializer_list<T> elems) {
        root = nullptr;
        tree_size = 0;
        for (const auto &elem: elems) {
            root = insert_(root, elem);
        }
    }

    Set(Set<T>& other) {
        if (other.root == root) {
            return;
        }
        clean();
        root = deep_copy_(other.root);
        tree_size = other.tree_size;
    }

    Set<T>& operator=(const Set<T>& other) {
        clean();
        root = deep_copy_(other.root);
        tree_size = other.tree_size;
        return *this;
    }

    ~Set() {
        clean();
    }

    void clean() {
        clean_(root);
        root = nullptr;
        tree_size = 0;
    }

    SetIterator begin() const {
        if (!root) {
            return SetIterator(this, nullptr, true);
        }
        return SetIterator(this, root->most_left, false);
    }

    SetIterator end() const {
        return SetIterator(this, nullptr, true);
    }

    void insert(const T& v) {
        root = insert_(root, v);
    }

    void erase(const T& v) {
        root = erase_(root, v);
    }

    size_t size() const {
        return tree_size;
    }

    bool empty() const {
        return tree_size == 0;
    };

    SetIterator find(const T& v) const {
        Node* node = find_(root, v);
        return SetIterator(this, node, node == nullptr);
    }

    SetIterator lower_bound(const T& v) const {
        Node* node = lower_bound_(root, v);
        return SetIterator(this, node, node == nullptr);
    }

};