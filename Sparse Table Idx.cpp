template<typename T = int> struct sparse_table {
    int n, m;
    vector<vector<T>> sp;
    vector<int> lg, v;

    explicit sparse_table(int n) : n(n) {
        m = __lg(n) + 1;
        sp = vector<vector<T>>(m + 5, vector<int>(n + 5));
        lg = vector<int>(n + 5);
    }

    void build(vector<int>& tmp) {
        v = tmp;
        lg[0] = -1;
        for(int i = 0; i < n; i++) {
            sp[0][i] = i;
            lg[i + 1] = lg[i] + !(i & (i + 1));
        }

        for(int j = 1; 1 << j <= n; j++) {
            for(int i = 0; i + (1 << j) <= n; i++) {
                int a = sp[j - 1][i];
                int b = sp[j - 1][i + (1 << (j - 1))];
                sp[j][i] = v[a] < v[b] ? a : b;
            }
        }
    }

    T get_mn(int st, int ed) {
        int sz = ed - st + 1;
        int LOG = lg[sz];
        int a = sp[LOG][st], b = sp[LOG][ed - (1 << LOG) + 1];
        return v[a] < v[b] ? a : b;
    }
};
