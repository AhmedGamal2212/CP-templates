struct DSUWithSets {
    // Zero based DSU
    vector<int> group_size, par, roots, tail, nxt, pos;

    explicit DSUWithSets(int size) {
        par.assign(size - 1, -1);
        group_size = vector<int>(size, 1);
        roots = pos = tail = vector<int>(size);
        nxt.assign(size, -1);

        iota(all(roots), 0);
        iota(all(pos), 0);
        iota(all(tail), 0);
    }

    int find(int u) {
        if(par[u] == -1) {
            return u;
        }
        return par[u] = find(par[u]);
    }

    bool join(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) {
            return false;
        }
        if(group_size[x] > group_size[y]) {
            swap(x, y);
        }
        par[x] = y;
        group_size[y] += group_size[x];

        int p = pos[x];
        roots[p] = roots.back();
        pos[roots[p]] = p;
        roots.pop_back();

        nxt[tail[y]] = x;
        tail[y] = tail[x];

        return true;
    }

    void print() {
        for(auto& x : roots) {
            for(int y = x; ~y; y = nxt[y]) {
                cout << y << " \n"[!~nxt[y]];
            }
        }
    }
};
