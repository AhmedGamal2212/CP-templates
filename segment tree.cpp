struct segment_tree {
    struct node {
        int value, cnt;

        node(){
            value = cnt = 0;
        }

        node(int value, int cnt){
            this -> value = value;
            this -> cnt = cnt;
        }
    };

    int size;
    vector<node> tree;
    const node DEFAULT = {imax, 0};



    node merge(node& a, node& b){
        if(a.value < b.value)
            return a;
        if(a.value > b.value)
            return b;

        return {a.value, a.cnt + b.cnt};
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
                tree[idx] = {v[l], 1};
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
            return void(tree[idx] = {value, 1});

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