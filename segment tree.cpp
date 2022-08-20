struct segment_tree {
    struct node {
        ll seg, pref, suf, sum;

        node(){
            seg = pref = suf = sum = 0;
        }

        node(ll seg, ll pref, ll suf, ll sum){
            this -> seg = seg;
            this -> pref = pref;
            this -> suf = suf;
            this -> sum = sum;
        }
    };

    int size;
    vector<node> tree;
    const node DEFAULT = {0, 0, 0, 0};


    node single(int value){
        if(value > 0){
            return {value, value, value, value};
        }
        return {0, 0, 0, value};
    }

    node merge(node& a, node& b){
        return {
            max({a.seg, b.seg, a.suf + b.pref}),
            max(a.pref, a.sum + b.pref),
            max(b.suf, b.sum + a.suf),
            a.sum + b.sum
        };
    }

    segment_tree(){
        size = 1;
    }

    explicit segment_tree(vector<int>& v){
        size = 1;
        init((int)v.size());
        build(v);
    }

    void init(int n){
        size = 1;
        while(size < n)
            size *= 2;

        tree.assign(size * 2, node());
    }

    void build(vector<int>& v, int idx, int l, int r){
        if(r - l == 1){
            if(l < int(v.size()))
                tree[idx] = single(v[l]);
            return;
        }

        int mid = l - (l - r) / 2;
        build(v, 2 * idx + 1, l, mid);
        build(v, 2 * idx + 2, mid, r);
        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    void build(vector<int>& v){
        build(v, 0, 0, size);
    }

    void set(int target, int value, int idx, int l, int r){
        if(r - l == 1)
            return void(tree[idx] = single(value));

        int mid = l - (l - r) / 2;
        if(target < mid){
            set(target, value, 2 * idx + 1, l, mid);
        }else{
            set(target, value, 2 * idx + 2, mid, r);
        }

        tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    void set(int target, int value){
        set(target, value, 0, 0, size);
    }

    node query(int st, int ed, int x, int l, int r){
        if(l >= ed or r <= st)
            return DEFAULT;
        if(l >= st and r <= ed)
            return tree[x];

        int mid = l - (l - r) / 2;
        node left = query(st, ed, 2 * x + 1, l, mid);
        node right = query(st, ed, 2 * x + 2, mid, r);

        return merge(left, right);
    }

    node query(int st, int ed){
        return query(st, ed, 0, 0, size);
    }
};
