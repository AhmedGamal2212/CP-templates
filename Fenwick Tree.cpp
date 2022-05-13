struct fenwick_tree{
    int n;
    vector<int> bit;

    fenwick_tree(int n){
        this -> n = n;
        bit.assign(n + 1, 0);
    }

    fenwick_tree(vector<int>& v) : fenwick_tree(int(v.size())){
        int idx = 0;
        while(idx < n){
            add(idx + 1, v[idx]);
            idx++;
        }
    }

    void add(int idx, int value){
        while(idx <= n){
            bit[idx] += value;
            idx += idx & -idx;
        }
    }

    int sum(int idx){
        int ret = 0;
        while(idx){
            ret += bit[idx];
            idx ^= idx & -idx;
        }
        return ret;
    }

    int sum(int l, int r){
        return sum(r) - sum(l - 1);
    }
};