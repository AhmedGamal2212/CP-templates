template<typename T = int, typename E = int> struct fenwick_tree_2d {
    int n {}, m {};
    vector<vector<T>> bit;

    fenwick_tree_2d(int n, int m) {
        this->n = n;
        this->m = m;
        bit.assign(n + 1, vector<T>(m + 1));
    }

    explicit fenwick_tree_2d(vector<vector<E>>& v): fenwick_tree_2d(v.size(), v.front().size()) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                add(i, j, v[i][j]);
            }
        }
    }

    T sum(int x, int y) {
        x++, y++;
        T ret = 0;
        while(x) {
            int idx = y;
            while(idx) {
                ret += bit[x - 1][idx - 1];
                idx ^= idx & -idx;
            }
            x ^= x & -x;
        }
        return ret;
    }

    void add(int x, int y, int value) {
        x++, y++;
        while(x <= n) {
            int idx = y;
            while(idx <= m) {
                bit[x - 1][idx - 1] += value;
                idx += idx & -idx;
            }
            x += x & -x;
        }
    }
};