template<typename T = int> struct TwoDimFenwickTree {
    int n, m;
    vector<vector<T>> BIT;

    TwoDimFenwickTree() {
        n = m = 0;
    }

    explicit TwoDimFenwickTree(int n, int m): n(n), m(m) {
        BIT = vector<vector<T>>(n, vector<T>(m));
    }

    T get(int i, int j) {
        ++j;
        T ret = 0;
        for(++i; i; i -= i & -i) {
            for(int k = j; k; k -= k & -k) {
                ret += BIT[i - 1][k - 1];
            }
        }
        return ret;
    }

    void add(int i, int j, int val) {
        ++j;
        for(++i; i <= n; i += i & -i) {
            for(int k = j; k <= m; k += k & -k) {
                BIT[i - 1][k - 1] += val;
            }
        }
    }

    T get_rec(int i_mn, int j_mn, int i_mx, int j_mx) {
        T ret = 0;
        ret += get(i_mx, j_mx);
        ret -= get(i_mn - 1, j_mx);
        ret -= get(i_mx, j_mn - 1);
        ret += get(i_mn - 1, j_mn - 1);
        return ret;
    }
};
