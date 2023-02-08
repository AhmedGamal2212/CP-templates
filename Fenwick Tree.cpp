template<typename T>
struct fenwick_tree{
    int n{};
    vector<T> bit;

    fenwick_tree() = default;

    void init(int n_){
        this -> n = n_;
        bit.assign(n_ + 1, 0);
    }

    explicit fenwick_tree(int n){
        init(n);
    }

    explicit fenwick_tree(vector<T>& v) : fenwick_tree(int(v.size())){
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

    T sum(int idx){
        T ret = 0;
        while(idx){
            ret += bit[idx];
            idx ^= idx & -idx;
        }
        return ret;
    }

    ll sum(int l, int r){
        if(l > r)
            return 0;
        return sum(r) - sum(l - 1);
    }

    void update_range(int l, int r, int value){
        add(l, value);
        add(r + 1, -value);
    }

    int size(){
        return this -> n;
    }
};
