template<typename T = ll>
struct segment_tree {
    int size;
    vector<T> sums;
    const T DEFAULT = 0;

    T merge(T a, T b) {
        return a + b;
    }

    T single(int x){
        return log10(x);
    }
    
    explicit segment_tree(int n) {
        size = 0;
        init(n);
    }

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;
        sums.assign(size * 2, DEFAULT);
    }

    void build(vector<int> &v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < int(v.size()))
                sums[x] = single(v[lx]);
            return;
        }

        int mid = lx - (lx - rx) / 2;
        build(v, 2 * x + 1, lx, mid);
        build(v, 2 * x + 2, mid, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void build(vector<int> &v) {
        build(v, 0, 0, size);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1)
            return void(sums[x] = single(v));

        int mid = lx - (lx - rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        } else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }

    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    T query(int l, int r, int x, int lx, int rx) {
        if (lx >= r or rx <= l)
            return DEFAULT;
        if (lx >= l and rx <= r)
            return sums[x];

        int mid = lx - (lx - rx) / 2;
        T left = query(l, r, 2 * x + 1, lx, mid);
        T right = query(l, r, 2 * x + 2, mid, rx);

        return merge(left, right);
    }

    T query(int l, int r) {
        return query(l, r, 0, 0, size);
    }
};