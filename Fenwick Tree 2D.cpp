struct fenwick_tree_2d{
    int n, m;
    vector<vector<int>> bit;

    fenwick_tree_2d(int n, int m){
        this -> n = n;
        this -> m = m;
        bit.assign(n + 1, vector<int>(m + 1));
    }

    fenwick_tree_2d(vector<vector<int>>& v) : fenwick_tree_2d(v.size(), v.front().size()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                add(i + 1, j + 1, v[i][j]);
            }
        }
    }

    int sum(int x, int y){
        int ret = 0;
        while(x){
            int idx = y;
            while(idx){
                ret += bit[x][idx];
                idx ^= idx & -idx;
            }
            x ^= x & -x;
        }
        return ret;
    }

    void add(int x, int y, int value){
        while(x <= n){
            int idx = y;
            while(idx <= m){
                bit[x][idx] += value;
                idx += idx & -idx;
            }
            x += x & -x;
        }
    }
};