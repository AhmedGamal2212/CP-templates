template<typename T = ll> struct segment_tree {

    struct node {
        int value, cnt;

        node(): value(0), cnt(0) {
        };

        node(int value): value(value), cnt(1) {
        };

        node(int value, int cnt): value(value), cnt(cnt) {
        };
    };


    // 0-based
    int size;
    vector<node> tree;
    const node DEFAULT = node(imax);

    node single(int value) {
        return {value};
    }

    segment_tree() {
        size = 1;
    }

    explicit segment_tree(int n) {
        size = 1;
        init(n);
    }

    explicit segment_tree(vector<int>& v) {
        size = 1;
        init(int(v.size()));
        build(v);
    }

    node merge(node& a, node& b) {
        if(a.value < b.value) {
            return a;
        } else if(a.value > b.value) {
            return b;
        }
        return {a.value, a.cnt + b.cnt};
    }

    void init(int n) {
        size = 1;
        while(size < n)
            size <<= 1;
        tree.assign(size << 1, DEFAULT);
    }

    void build(vector<int>& v, int x, int lx, int rx) {
        if(rx - lx == 1) {
            if(lx < int(v.size())) {
                tree[x] = single(v[lx]);
            }
            return;
        }

        int m = (lx + rx) >> 1;
        build(v, 2 * x + 1, lx, m);
        build(v, 2 * x + 2, m, rx);

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<int>& v) {
        build(v, 0, 0, size);
    }

    // lx, rx are the borders of the segment covered by node x
    // note that the segment is [lx, rx)
    void set(int i, int value, int x, int lx, int rx) {
        if(rx - lx == 1) {
            tree[x] = value;
            return;
        }

        int m = (lx + rx) >> 1;
        if(i < m) {
            set(i, value, 2 * x + 1, lx, m);
        } else {
            set(i, value, 2 * x + 2, m, rx);
        }

        tree[x] = merge(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void set(int i, int value) {
        // set(idx required, new value, initial position, lx, rx (not included))
        set(i, value, 0, 0, size);
    }

    node query(int l, int r, int x, int lx, int rx) {
        if(lx >= r or l >= rx) {
            return DEFAULT;
        }
        if(lx >= l and rx <= r) {
            return tree[x];
        }

        // go deeper
        int m = (lx + rx) >> 1;

        node left = query(l, r, 2 * x + 1, lx, m);
        node right = query(l, r, 2 * x + 2, m, rx);

        return merge(left, right);
    }

    node query(int l, int r) {
        // set(idx required, new value, initial position, lx, rx (not included))
        return query(l, r, 0, 0, size);
    }
};