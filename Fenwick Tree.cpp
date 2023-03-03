template<typename T>
struct fenwick_tree {
    int n{};
    vector<T> bit;
    const T DEFAULT = 0;

    fenwick_tree() = default;

    void init(int n_) {
        this->n = n_;
        bit.assign(n_ + 1, DEFAULT);
    }

    explicit fenwick_tree(int n) {
        init(n);
    }

    explicit fenwick_tree(vector<T> &v) : fenwick_tree(int(v.size())) {
        int idx = 0;
        while (idx < n) {
            add(idx + 1, v[idx]);
            idx++;
        }
    }

    void add(int idx, T value) {
        while (idx <= n) {
            bit[idx] += value;
            idx += idx & -idx;
        }
    }

    T sum(int idx) {
        T ret = 0;
        while (idx) {
            ret += bit[idx];
            idx ^= idx & -idx;
        }
        return ret;
    }

    T sum(int l, int r) {
        if (l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }

    void update_range(int l, int r, T value) {
        add(l, value);
        add(r + 1, -value);
    }

    int size() {
        return this->n;
    }
};