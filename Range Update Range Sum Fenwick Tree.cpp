template<typename T = ll> struct FenwickTree {
    vector<T> m, c;
    int n;

    explicit FenwickTree(int n) : n(1 << (__lg(n) + 1)) {
        m = c = vector<T>(this->n);
    }

    T get(int pos) {
        int i = pos;
        T ret = 0;
        for(++pos; pos; pos -= pos & -pos) {
            ret += i * m[pos - 1] + c[pos - 1];
        }
        return ret;
    }

    void add(int pos, ll add_m, ll add_c) {
        for(++pos; pos <= n; pos += pos & -pos) {
            m[pos - 1] += add_m;
            c[pos - 1] += add_c;
        }
    }

    void add_range(int st, int ed, ll val) {
        add(st, val, -(st - 1) * val);
        add(ed + 1, -val, ed * val);
    }

    T get_range(int st, int ed) {
        return get(ed) - get(st - 1);
    }
};
