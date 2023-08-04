struct TreeCanonical {
    int n {};
    vector<vector<int>> adj;
    vector<int> deg;
    vector<vector<string>> children_canonical;

    explicit TreeCanonical(int n, vector<vector<int>>& adj) : n(n), adj(adj) {
        deg.assign(n + 5, -1);
        children_canonical.assign(n + 5, vector<string>());
    }

    string sub_tree_canonical(int src) {
        string sub_tree = "(";
        sort(all(children_canonical[src]));
        for(auto& child : children_canonical[src]) {
            sub_tree += child;
        }
        sub_tree += ")";
        return sub_tree;
    }

    string tree_canonical() {
        queue<int> leaves;
        int rem_nodes = n;

        for(int i = 1; i <= n; i++) {
            if(adj[i].size() <= 1) {
                leaves.emplace(i);
            } else {
                deg[i] = (int)adj[i].size();
            }
        }

        while(rem_nodes > 2) {
            int size = int(leaves.size());
            while(size--) {
                int src = leaves.front();
                leaves.pop();

                string node_canonical = sub_tree_canonical(src);
                for(auto& nxt : adj[src]) {
                    children_canonical[nxt].emplace_back(node_canonical);
                    if(--deg[nxt] == 1) {
                        leaves.emplace(nxt);
                    }
                }
                --rem_nodes;
            }
        }

        int center_a = leaves.front();
        leaves.pop();

        if(leaves.empty()) {
            return sub_tree_canonical(center_a);
        }

        int center_b = leaves.front();

        auto iso_a = sub_tree_canonical(center_a);
        auto iso_b = sub_tree_canonical(center_b);

        children_canonical[center_b].emplace_back(iso_a);
        children_canonical[center_a].emplace_back(iso_b);

        return min(sub_tree_canonical(center_a), sub_tree_canonical(center_b));
    }
};
