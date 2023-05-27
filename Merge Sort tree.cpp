template<typename T = int> struct merge_sort_tree {
    int n {}, size;
    vector<vector<int>> tree;

    explicit merge_sort_tree(vector<int>& v) {
        this->n = int(v.size());
        size = 1;
        while(size <= n) {
            size <<= 1;
        }
        tree.assign(size << 1, vector<int>());
        build(0, 0, size, v);
    }

    void build(int x, int lx, int rx, vector<int>& v) {
        if(rx - lx == 1) {
            if(lx < v.size())
                tree[x].emplace_back(v[lx]);
            return;
        }

        int mx = (lx + rx) >> 1;
        build(2 * x + 1, lx, mx, v);
        build(2 * x + 2, mx, rx, v);

        merge(all(tree[2 * x + 1]), all(tree[2 * x + 2]), back_inserter(tree[x]));
    }

    int query(int l, int r, int value, int x, int lx, int rx) {
        if(rx <= l or lx >= r) {
            return 0;
        }
        if(lx >= l and rx <= r) {
            int lq = int(lower_bound(all(tree[x]), value) - tree[x].begin());
            return tree[x].size() - lq;
        }

        int mx = (lx + rx) >> 1;
        int left = query(l, r, value, 2 * x + 1, lx, mx);
        int right = query(l, r, value, 2 * x + 2, mx, rx);

        return left + right;
    }

    int query(int l, int r, int value) {
        return query(l, r, value, 0, 0, size);
    }
};