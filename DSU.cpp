
struct dsu {
    vector<int> p, rank;

    explicit dsu(int size) {
        p.resize(size + 1);
        rank.resize(size + 1);

        iota(all(p), 0);
    }

    int get(int x) {
        return p[x] = x == p[x] ? x : get(p[x]);
    }

    void join(int u, int v){
        u = get(u), v = get(v);

        if(u == v)
            return;

        rank[u] += rank[v] == rank[u];
        if(rank[v] > rank[u])
            swap(u, v);
        
        p[v] = u;
    }
};