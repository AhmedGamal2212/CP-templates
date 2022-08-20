struct suffix_array {
    string x;
    int n;
    vector<int> suffix;

    suffix_array(string s = "") {
        x = s + '$';
        n = (int)x.size();
        suffix.resize(n);
    }

    void count_sort(vector<int> &p,  vector<int> &c) {
        vector<int> cnt(n);
        for(auto a: c)
            cnt[a]++;
        vector<int> p_new(n), pos(n);
        pos[0] = 0;
        for(int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];
        for(auto a: p){
            int i = c[a];
            p_new[pos[i]] = a;
            pos[i]++;
        }
        p = p_new;
    }

    void build() {
        vector<int> c(n);
        vector<pair<char, int>> v(n);
        for(int i = 0; i < n; i++)
            v[i] = {x[i], i};
        sort(all(v));
        for(int i = 0; i < n; i++)
            suffix[i] = v[i].second;
        c[suffix[0]] = 0;
        for(int i = 1; i < n; i++)
            c[suffix[i]] = c[suffix[i - 1]] + (v[i].first != v[i - 1].first);

        for(int k = 0; (1 << k) < n; k++){
            for(int i = 0; i < n; i++)
                suffix[i] = (suffix[i] - (1 << k) + n) % n;
            count_sort(suffix, c);
            c[suffix[0]] = 0;
            vector <int> c_new(n);
            c_new[suffix[0]] = 0;
            for(int i = 1; i < n; i++) {
                pair<int, int> prev = {c[suffix[i - 1]], c[(suffix[i - 1] + (1 << k)) % n]};
                pair<int, int> cur = {c[suffix[i]], c[(suffix[i] + (1 << k)) % n]};
                c_new[suffix[i]] = c_new[suffix[i - 1]] + (prev != cur);
            }
            c = c_new;
        }
    }
};