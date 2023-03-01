void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n + 5);

    for(int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<pair<int, int>> longest_a(n + 5), longest_b(n + 5);
    vector<int> p(n + 5, -1);

    auto preprocess = [&](auto preprocess, int src) -> int {
        vector<pair<int, int>> curr(3);
        for(auto& nxt : adj[src]){
            if(nxt == p[src])
                continue;

            p[nxt] = src;
            curr[2] = {preprocess(preprocess, nxt), nxt};
            sort(rall(curr));
        }
        longest_a[src] = curr[0];
        longest_b[src] = curr[1];

        return curr[0].first + 1;
    };

    preprocess(preprocess, 1);

    vector<int> ans(n + 5);

    auto dfs = [&](auto dfs, int src) -> void {
        if(src != 1){
            vector<pair<int, int>> curr = {longest_a[src], longest_b[src]};
            int par_path = longest_a[p[src]].second == src ? longest_b[p[src]].first : longest_a[p[src]].first;
            curr.emplace_back(par_path + 1, p[src]);
            sort(rall(curr));

            longest_a[src] = curr[0];
            longest_b[src] = curr[1];
        }
        ans[src] = longest_a[src].first;

        for(auto& nxt : adj[src]){
            if(nxt == p[src])
                continue;
            dfs(dfs, nxt);
        }
    };

    dfs(dfs, 1);

    for(int i = 1; i <= n; i++){
        cout << ans[i] << ' ';
    }
}
