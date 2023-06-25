struct node {
    int mn, cnt;
 
    explicit node(int mn = 0, int cnt = 0): mn(mn), cnt(cnt) {
 
    }
 
    node operator+(const node b) const {
        node res;
 
        if(mn == b.mn) {
            res = node(mn, cnt + b.cnt);
        } else if(mn < b.mn) {
            res = *this;
        } else {
            res = b;
        }
 
        return res;
    }
};
 
template<typename T = int, typename E = int> struct segment_tree {
    // 0-based indexing
    // [l, r) is the range on which the node is built
    // use single(x) to convert x to node
    // use mrg(a, b) to merge nodes a and b (remember to overload + in node struct)
    // use DEFAULT to set the default value of node
    // use put(x, v) to set the value of leaf node x to v
    // use set(i, v) to set the value of i-th element to v (also updates the tree)
    // use qry(l, r) to get the query result for range [l, r)
    vector<T> tree;
    const T DEFAULT = node(inf, 1);
    int n;
 
    explicit segment_tree(int n): n(n) {
        assign(n);
    }
 
    void assign(int size) {
        tree.assign(size << 1 | 1, DEFAULT);
    }
 
    void put(int x, E v) {
        tree[x + n] = single(v);
    }
 
    T single(E x) {
        return node(x, 1);
    }
 
    T mrg(T a, T b) {
        return a + b;
    }
 
    void build() {
        for(int i = n - 1; i; --i) {
            tree[i] = mrg(tree[i << 1], tree[i << 1 | 1]);
        }
    }
 
    void set(int i, E x) {
        for(tree[i += n] = single(x); i; i >>= 1) {
            tree[i >> 1] = mrg(tree[i], tree[i ^ 1]);
        }
    }
 
    T qry(int l, int r) {
        r++;
        T res = DEFAULT;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                res = mrg(res, tree[l++]);
            }
            if(r & 1) {
                res = mrg(res, tree[--r]);
            }
        }
        return res;
    }
};