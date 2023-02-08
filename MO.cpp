template<typename T = int>
struct MO {
    static const int blk = 400;

    struct Query {
        int l{}, r{}, idx{}, k{};

        Query(){
            l = r = idx = k = 0;
        }

        Query(int l, int r, int idx, int k){
            this -> l = l;
            this -> r = r;
            this -> idx = idx;
            this -> k = k;
        }

        pair<int, int> to_pair() {
            return make_pair(l / blk, (l / blk) & 1 ? -r : r);
        }

        bool operator<(Query& other) {
            return to_pair() < other.to_pair();
        }
    };

    ll res = 0;
    int q {};
    vector<Query> queries;

    explicit MO(int q){
        this -> q = q;
    }

    void add(int x){
        
    }

    void remove(int x){
        
    }

    void input(){
        for(int i = 0; i < q; i++){
            int u, k; cin >> u >> k;
            queries.emplace_back(u, k);
        }
    }

    vector<T> get_ans(){
        sort(all(queries));
        vector<T> ans(q);

        int curr_l = queries[0].l, curr_r = queries[0].l - 1;

        for(auto& [l, r, idx, k] : queries){
            while(curr_l > l){
                add(--curr_l);
            }
            while(curr_r < r){
                add(++curr_r);
            }
            while(curr_l < l){
                remove(curr_l++);
            }
            while(curr_r > r){
                remove(curr_r--);
            }

            ans[idx] = res;
        }

        return ans;
    }

    vector<T> solve(){
        input();
        auto ans = get_ans();
        return ans;
    }
};