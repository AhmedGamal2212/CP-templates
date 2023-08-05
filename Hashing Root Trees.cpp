void dfs(int src, int par = -1) {
    vector<int> children;
    map<int, int> freq;
    vector<pair<int, int>> res;
    for(auto& nxt : adj[src]) {
        if(nxt == par) {
            continue;
        }
        dfs(nxt, src);
        children.emplace_back(hash_val[nxt]);
        freq[children.back()]++;
        res.emplace_back(children.back(), symmetric[nxt]);
    }
 
    int odd = 0, bad = 0;
    unordered_set<int> used;
    for(auto& [child, sym] : res) {
        if(freq[child] & 1) {
            if(not used.contains(child)) {
                used.emplace(child);
                odd++;
                bad += not sym;
            }
        }
    }
    sort(all(children));
    if(not subtrees.contains(children)) {
        subtrees[children] = (int)subtrees.size();
    }
    hash_val[src] = subtrees[children];
    symmetric[src] = odd < 2 and not bad;
}
