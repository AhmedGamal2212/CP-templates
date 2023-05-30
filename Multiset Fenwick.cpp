template<typename T = ll> struct FenwickTree {
    int M;
    vector<T> BIT;
    const T DEFAULT = 0;

    explicit FenwickTree(int size) {
        M = 1 << (__lg(size) + !!(size & (size - 1)));
        BIT.assign(M, DEFAULT);
    }

    // 1-based
    void add(int pos, T val) {
        for(++pos; pos <= M; pos += pos & -pos) {
            BIT[pos - 1] += val;
        }
    }

    T get(int pos) {
        T ret = 0;
        for(++pos; pos; pos -= pos & -pos) {
            ret += BIT[pos - 1];
        }
        return ret;
    }

    int bs(T val) {
        int s = 0;
        for(int sz = M >> 1; sz; sz >>= 1) {
            if(BIT[s + sz - 1] < val) {
                val -= BIT[(s += sz) - 1];
            }
        }
        return s;
    }

    void init_multiset() {
        BIT.assign(M, 0);
        add(0, -1);
    }

    void insert(int val) {
        add(val, 1);
    }

    void count(int val) {
        return get(val) - get(val - 1);
    }

    void erase(int val) {
        add(val, -count(val));
    }

    int get_by_idx(int val) {
        return bs(val);
    }

    void erase_idx(int idx) {
        add(get_by_idx(idx), -1);
    }

    int size() {
        return get(M - 1) + 1;
    }

    bool empty() {
        return not size();
    }
};