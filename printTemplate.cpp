// fast input

ios_base::sync_with_stdio(false);
cin.tie(nullptr);

// ordered set

#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>

// range XOR

ll rangeXor(ll x){
    ll res[] = {x, 1, x + 1, 0};
    return res[x % 4];
}

// Coordinate Compression

struct Coordinate_Compression {

    map < ll, ll > mapping;
    vector < ll > orig, comp, nums;
    int sz;

    Coordinate_Compression(vector < ll >& Nums){
        sz = 1;
        nums = Nums;
        sort(all(nums));
        nums.resize(unique(all(nums)) - nums.begin());
        for(auto& i : nums)
            mapping[i] = sz++;
        orig.resize(sz);
        for(auto& [f, s] : mapping) orig[s] = f;
        comp = nums;
        for(auto& i : comp) i = mapping[i];
    }

    vector < ll > orignal(){
        return orig;
    }

    vector < ll > compressed(){
        return comp;
    }

};

// 2D Prefix Sum 

void prefix_2d(){
    vector<vector<int>> v;
    int n, m; // Row and Col

    // Accumulate
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j] += v[i][j - 1];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j] += v[i - 1][j];
        }
    }
    int i, j; // Upper left
    int k, l; // Lower right
    // sum
    v[k][l] - v[k][j - 1] - v[i - 1][l] + v[i - 1][j - 1];
}


// RMQ 

const int N = 1 << 17; // has to be power of 2
const int inf = 1 << 28;

struct RMQ {
    int a[N * 2];
    RMQ() {
        FOR(i, N * 2)
            a[i] = inf;
    }
    void SetMin(int pos, int x) {
        for (int i = pos + N; i; i >>= 1)
            a[i] = min(a[i], x);
    }
    int GetMin(int L, int R) const // [L, R) i.e. L <= i < R
    {
        int res = inf;
        for (L += N, R += N; L < R; L >>= 1, R >>= 1) {
            if (L & 1) {
                res = min(res, a[L]);
                L++;
            }
            if (R & 1) {
                R--;
                res = min(res, a[R]);
            }
        }
        return res;
    }
};

// DSU 

struct dsu{
    vector<int> p, rank;

    explicit dsu(int size){
        p.resize(size + 1);
        rank.resize(size + 1);

        iota(all(p), 0);
    }

    int get(int x){
        return p[x] = x == p[x] ? x : get(p[x]);
    }

    void join(int u, int v){
        u = get(u), v = get(v);

        if(u == v)
            return;

        if(rank[u] == rank[v])
            rank[u]++;

        if(rank[u] > rank[v])
            p[v] = u;
        else
            p[u] = v;
    }
};

// Fenwick Tree

template<typename T>
struct fenwick_tree{
    int n{};
    vector<T> bit;

    explicit fenwick_tree(int n){
        this -> n = n;
        bit.assign(n + 1, 0);
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

    T sum(int l, int r){
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

// 2D Fenwick Tree

struct fenwick_tree_2d{
    int n, m;
    vector<vector<int>> bit;

    fenwick_tree_2d(int n, int m){
        this -> n = n;
        this -> m = m;
        bit.assign(n + 1, vector<int>(m + 1));
    }

    fenwick_tree_2d(vector<vector<int>>& v) : fenwick_tree_2d(v.size(), v.front().size()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                add(i + 1, j + 1, v[i][j]);
            }
        }
    }

    int sum(int x, int y){
        int ret = 0;
        while(x){
            int idx = y;
            while(idx){
                ret += bit[x][idx];
                idx ^= idx & -idx;
            }
            x ^= x & -x;
        }
        return ret;
    }

    void add(int x, int y, int value){
        while(x <= n){
            int idx = y;
            while(idx <= m){
                bit[x][idx] += value;
                idx += idx & -idx;
            }
            x += x & -x;
        }
    }
};


// LIS Optimization (BS)

vector<int> lis(n, 1), lds(n, 1);

vector<int> d(n + 1, inf);
d.front() = -inf;

for (int i = 0; i < n; i++) {
	int pos = int(upper_bound(all(d), v[i]) - d.begin());
	bool found = d[int(lower_bound(all(d), v[i]) - d.begin())] == v[i];

	if (d[pos - 1] < v[i] and v[i] < d[pos]) {
		d[pos] = v[i];
	}
	lis[i] = pos - found;
}

// LIS Optimization (Fenwick Tree)

template<typename T>
struct fenwick_tree{
    int n{};
    vector<T> bit;

    explicit fenwick_tree(int n){
        this -> n = n;
        bit.assign(n + 5, 0);
    }

    void add(int idx, int value){
        while(idx <= n){
            updmax(bit[idx], value);
            idx += idx & -idx;
        }
    }

    T query(int idx){
        T ret = 0;
        while(idx){
            updmax(ret, bit[idx]);
            idx ^= idx & -idx;
        }
        return ret;
    }

    void assign(int size, int value){
        this -> n = size;
        bit.assign(size, value);
    }
};

vector<int> co;

int idx(int x){
    return int(upper_bound(all(co), x) - co.begin()) + 1;
}

void solve(){
    int n;
    while(cin >> n){
        vector<int> v(n); cin >> v;

        co = v;
        sort(all(co));
        co.erase(unique(all(co)), co.end());

        int ans = 1;
        fenwick_tree<int> ft(n);

        vector<int> lis(n), lds(n);

        for (int i = 0; i < n; i++) {
            ft.add(idx(v[i]), ft.query(idx(v[i]) - 1) + 1);
            lis[i] = ft.bit[idx(v[i])];
        }
        ft.assign(10005, 0);
        reverse(all(v));

        for (int i = 0; i < n; i++) {
            ft.add(idx(v[i]), ft.query(idx(v[i]) - 1) + 1);
            lds[n - i - 1] = ft.bit[idx(v[i])];
        }

        for (int i = 0; i < n; i++) {
            int len = min(lis[i], lds[i]);
            updmax(ans, len * 2 - 1);
        }
        cout << ans << nl;
    }
}

// Segment Tree

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


// Sparse Table

template < typename T = int > struct Sparse_Table {

    struct Node {

        ll val;

        Node(ll V = 0) : val(V) {}
    
        Node operator = (const T& rhs) {
            val = rhs;
            return *this;
        }

    };

    int n, LOG;
    vector < vector < Node > > table;
    vector < int > Bin_Log;
    Node DEFAULT;

    Sparse_Table(vector < T >& vec){
        n = sz(vec), DEFAULT = 0, LOG = __lg(n) + 1;
        table = vector < vector < Node > > (n + 10, vector < Node > (LOG));
        Bin_Log = vector < int > (n + 10);
        for(int i = 2; i <= n; i++)
            Bin_Log[i] = Bin_Log[i >> 1] + 1;
        for(int i = 0; i < n; i++)
            table[i][0] = vec[i];
        Build_Table();
    }

    Node operation(Node a, Node b){
        Node res;
        res.val = a.val + b.val;
        return res;
    }

    void Build_Table(){
        for(int log = 1; log < LOG; log++)
            for(int i = 0; i + (1 << log) - 1 < n; i++)
                table[i][log] = operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
    }

    Node query_1(int L, int R){
        int log = Bin_Log[R - L + 1];
        return operation(table[L][log], table[R - (1 << log) + 1][log]);
    }

    Node query_log_n(int L, int R){
        T answer = DEFAULT;
        for (int log = LOG; log >= 0; log--){
            if (L + (1 << log) - 1 <= R) {
                answer = operation(answer, table[L][log]);
                L += 1 << log;
            }
        }
        return answer;
    }

    T query(int L, int R, bool overlap = false){
        return (overlap ? query_1(L, R) : query_log_n(L, R)).val;
    }

};

// Sliding Queue

struct Stack{
    vector<ll> sMax = {LLONG_MIN}, sMin = {LLONG_MAX}, s;
 
    void push(ll x){
        s.push_back(x);
        sMax.push_back(::max(x, sMax.back()));
        sMin.push_back(::min(x, sMin.back()));
    }
 
    bool empty(){
        return s.empty();
    }
 
    ll pop(){
        ll p = s.back();
        s.pop_back(), sMax.pop_back(), sMin.pop_back();
        return p;
    }
 
    ll max(){
        return sMax.back();
    }
 
    ll min(){
        return sMin.back();
    }
 
};
::Stack s1, s2;
 
void add(ll x){
    s2.push(x);
}
 
bool good(){
    ll mn = min(s1.min(), s2.min()),
    mx = max(s1.max(), s2.max());
 
    return mx - mn <= k;
}
 
void remove(ll x){
    if(s1.empty()){
        while(!s2.empty())
            s1.push(s2.pop());
    }
    s1.pop();
}

// GRAPH

// topo sort kahn
void kahn(){
    int n; // Number of nodes
    vector <vector<int>> adj;
    vector <int> deg;
    for(int i = 1; i <= n; i++)
        for(auto x : adj[i])
            deg[x]++;

    queue<int>ready;
    for(int i = 1; i <= n; i++)
        if(!deg[i])
            ready.push(i);
        vector < int > ans;
    while(ready.size()){
        int x = ready.front();
        ready.pop();
        ans.push_back(x);
        for(auto i : adj[x]){
            if(!(--deg[i]))
                ready.push(i);
        }
    }
    // ready.size() != n if cycle

}

// Normal djikstra
const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);
    vector<bool> u(n, false);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
}

// Djikstra on sparse graph
const int INF = 1000000000;
vector<vector<pair<int, int>>> adj;

void dijkstra(int s, vector<int> & d, vector<int> & p) {
    int n = adj.size();
    d.assign(n, INF);
    p.assign(n, -1);

    d[s] = 0;
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int v = q.top().second;
        int d_v = q.top().first;
        q.pop();
        if (d_v != d[v])
            continue;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
                q.push({d[to], to});
            }
        }
    }
}

// Bellman ford
void Bellman()
{
    vector<int> d (n, INF);
    d[v] = 0;
    for (;;)
    {
        bool any = false;

        for (int j=0; j<m; ++j)
            if (d[e[j].a] < INF)
                if (d[e[j].b] > d[e[j].a] + e[j].cost)
                {
                    d[e[j].b] = d[e[j].a] + e[j].cost;
                    any = true;
                }

        if (!any) break;
    }
    // display d, for example, on the screen
}

// Bipartite matching
int n, k;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    //... reading the graph ...

    mt.assign(k, -1);
    for (int v = 0; v < n; ++v) {
        used.assign(n, false);
        try_kuhn(v);
    }

    for (int i = 0; i < k; ++i)
        if (mt[i] != -1)
            printf("%d %d\n", mt[i] + 1, i + 1);
}


// SCC: condensation

vector<vector<int>> adj, adj_rev;
vector<bool> used;
vector<int> order, component;

void dfs1(int v) {
    used[v] = true;

    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);

    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    component.push_back(v);

    for (auto u : adj_rev[v])
        if (!used[u])
            dfs2(u);
}

int main() {
    int n;
    // ... read n ...

    for (;;) {
        int a, b;
        // ... read next directed edge (a,b) ...
        adj[a].push_back(b);
        adj_rev[b].push_back(a);
    }

    used.assign(n, false);

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs1(i);

    used.assign(n, false);
    reverse(order.begin(), order.end());

    for (auto v : order)
        if (!used[v]) {
            dfs2 (v);

            // ... processing next component ...

            component.clear();
        }
}


// Condensation graph construction

// continuing from previous code

vector<int> roots(n, 0);
vector<int> root_nodes;
vector<vector<int>> adj_scc(n);

for (auto v : order)
    if (!used[v]) {
        dfs2(v);

        int root = component.front();
        for (auto u : component) roots[u] = root;
        root_nodes.push_back(root);

        component.clear();
    }


for (int v = 0; v < n; v++)
    for (auto u : adj[v]) {
        int root_v = roots[v],
            root_u = roots[u];

        if (root_u != root_v)
            adj_scc[root_v].push_back(root_u);
    }


// SCC: Tarjan

void tarjan(int src){
    dfs_num[src] = dfs_low[src] = counter++;

    dfs_stack.push_back(src);
    in_stack[src] = true;

    for(auto& nxt : adj[src]){
        if(not dfs_num[nxt])
            tarjan(nxt);

        if(in_stack[nxt])
            dfs_low[src] = min(dfs_low[src], dfs_low[nxt]);
    }


    // this is the the root of the SCC

    if(dfs_low[src] == dfs_num[src]){
        while(true){
            int curr = dfs_stack.back();
            dfs_stack.pop_back();
            in_stack[curr] = false;

            if(curr == src)
                break;
        }
    }
}


// MST: Kruskal 

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<int> tree_id(n);
vector<Edge> result;
for (int i = 0; i < n; i++)
    tree_id[i] = i;

sort(edges.begin(), edges.end());

for (Edge e : edges) {
    if (tree_id[e.u] != tree_id[e.v]) {
        cost += e.weight;
        result.push_back(e);

        int old_id = tree_id[e.u], new_id = tree_id[e.v];
        for (int i = 0; i < n; i++) {
            if (tree_id[i] == old_id)
                tree_id[i] = new_id;
        }
    }
}


// MST: Kruskal (DSU)

vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

int n;
vector<Edge> edges;

int cost = 0;
vector<Edge> result;
parent.resize(n);
rank.resize(n);
for (int i = 0; i < n; i++)
    make_set(i);

sort(edges.begin(), edges.end());

for (Edge e : edges) {
    if (find_set(e.u) != find_set(e.v)) {
        cost += e.weight;
        result.push_back(e);
        union_sets(e.u, e.v);
    }
}



// Floyd-Warshall


for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (d[i][k] < INF && d[k][j] < INF)
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
        }
    }
}

// Modification in Floyd Warshall Algorithm (path contstruction)

#define MAXN 100

// Infinite value for array

const int INF = 1e7;
 
int dis[MAXN][MAXN];
int Next[MAXN][MAXN];
 
// Initializing the distance and
// Next array

void initialise(int V, vector<vector<int> >& graph){
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dis[i][j] = graph[i][j];
 
            // No edge between node
            // i and j
            
            if(graph[i][j] == INF)
                Next[i][j] = -1;
            else
                Next[i][j] = j;
        }
    }
}
 
// Function construct the shortest
// path between u and v

vector<int> constructPath(int u, int v){
    // If there's no path between
    // node u and v, simply return
    // an empty array
    
    if (Next[u][v] == -1)
        return {};
 
    // Storing the path in a vector
    
    vector<int> path = {u};
    while (u != v) {
        u = Next[u][v];
        path.push_back(u);
    }
    return path;
}
 
// Standard Floyd Warshall Algorithm
// with little modification Now if we find
// that dis[i][j] > dis[i][k] + dis[k][j]
// then we modify next[i][j] = next[i][k]

void floydWarshall(int V){
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
 
                // We cannot travel through
                // edge that doesn't exist

                if (dis[i][k] == INF || dis[k][j] == INF)
                    continue;
 
                if (dis[i][j] > dis[i][k] + dis[k][j]){
                    dis[i][j] = dis[i][k] + dis[k][j];
                    Next[i][j] = Next[i][k];
                }
            }
        }
    }
}
 
// Print the shortest path

void printPath(vector<int>& path){
    int n = path.size();
    for (int i = 0; i < n - 1; i++)
        cout << path[i] << " -> ";
    cout << path[n - 1] << endl;
}


// LCA: binary lifting 

template < typename T = int > struct LCA {
    
    struct Edge {

        ll v, w;

        Edge(ll V = 0, ll W = 0) : v(V), w(W) {}

        bool operator < (const Edge &rhs) const {
            return w < rhs.w;
        }

    };

    int N, LOG;
    vector < vector < T > > anc, cost;
    vector < vector < Edge > > adj;
    vector < int > dep;
    
    LCA(int n){
        N = n + 10, LOG = 0;
        while((1 << LOG) <= n) LOG++;
        dep = vector < int > (N);
        adj = vector < vector < Edge > > (N);
        anc = cost = vector < vector < T > > (N, vector < T > (LOG));
    }
    
    void add_edge(int u, int v, T w){
        adj[u].push_back(Edge(v, w));
        adj[v].push_back(Edge(u, w));
    }

    void build_adj(int edges){
        for(int i = 0, u, v, w; i < edges && cin >> u >> v >> w; i++)
            add_edge(u, v, w);
    }

    T operation(T a, T b){
        return a + b;
    }
    
    void dfs(int u, int p = 0){
        for(auto& [v, w] : adj[u]){
            if(v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u, cost[v][0] = w;
            for(int bit = 1; bit < LOG; bit++){
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
                cost[v][bit] = operation(cost[v][bit - 1], cost[anc[v][bit - 1]][bit - 1]);
            }
            dfs(v, u);
        }
    }
    
    int kth_ancestor(int u, int k){
        if(dep[u] < k) 
            return -1;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(k & (1 << bit))
                u = anc[u][bit];
        return u;
    }
    
    int get_lca(int u, int v){
        if(dep[u] < dep[v])
            swap(u, v);
        u = kth_ancestor(u, dep[u] - dep[v]);
        if(u == v)
            return u;
        for(int bit = LOG - 1; bit >= 0; bit--)
            if(anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }
    
    T get_cost(int u, int dist){
        if(dep[u] < dist) return -1;
        T ans = 0;
        for(int bit = 0; bit < LOG; bit++)
            if(dist & (1 << bit))
                ans = operation(ans, cost[u][bit]), u = anc[u][bit];
        return ans;
    }
    
    T query(int u, int v){
        int lca = get_lca(u, v);
        return operation(get_cost(u, dep[u] - dep[lca]), get_cost(v, dep[v] - dep[lca]));
    }

};


// Tree Diameter 

vector<vector<int>> adj;
//int maxi = imin, node;

// length and the node
pair<int, int> dfs(int src, int parent){
    pair<int, int> ret = {0, src};

    for(auto& nxt : adj[src]){
        if(nxt == parent)
            continue;

        auto [len, node] = dfs(nxt, src);
        if(len > ret.first){
            ret = {len, node};
        }
    }

    return {ret.first + 1, ret.second};
}

void solve(){
    int n; cin >> n;
    adj.assign(n + 5, vector<int>());


    for(int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    auto [len, node] = dfs(1, -1);

    debug2(len - 1, node)

    debug2(dfs(node, -1).first - 1, dfs(node, -1).second)
}

// MOD Inverse

struct MOD_Inverse {

    ll n;
    int mod;
    vector<ll> fact, inv;

    ll fast_power(ll b, ll e){
        ll power = 1;
        while(e){
            if(e & 1) power = modulo(power, b, mod);
            e >>= 1, b = modulo(b, b, mod);
        }
        return power % mod;
    }

    ll Inverse(ll x){
        return fast_power(x, mod - 2) % mod;
    }

    MOD_Inverse(ll n, int mod){
        this -> n = n;
        this -> mod = mod;
        fact.assign(n + 10, 1), inv.resize(n + 10, 1);
        for(ll i = 1; i <= n; i++){
            fact[i] = modulo(fact[i - 1], i, mod);
            inv[i] = Inverse(fact[i]);
        }
    }

};


// Math

struct Math{
    template<typename T>
    static ll BinExp(T b, T e, int mod){
        ll res = 1;
        while(e){
            if(e & 1)
                res = modulo(res, b, mod);

            b = modulo(b, b, mod);
            e >>= 1;
        }
        return res;
    }

    template<typename T, typename E>
    static void sub(T& a, E b, int mod){
        a -= b;
        if(a < 0)
            a += mod;
    }

    template<typename T, typename E>
    static void add(T& a, E b, int mod){
        a += b;
        if(a >= mod)
            a -= mod;
    }

    template<typename T>
    static T inv(T x, T mod){
        x %= mod;
        if(x < 0)
            x += mod;

        T b = mod, ret = 0, c = 1;
        while(x){
            int tmp = b / x;

            b -= tmp * x;
            swap(x, b);

            ret -= tmp * c;
            swap(ret, c);
        }
        if(ret < 0)
            ret += mod;
        return ret;
    }


};

// Permutation
ll nPr(ll n, ll r){
    if(r > n) return 0;
    ll npr = 1;
    while(r-- > 0)
        npr *= n--;
    return npr;
}

// Combination
ll nCr(ll n, ll r){
    if(r > n) return 0;
    ll p = 1, k = 1;
    if (n - r < r) r = n - r;
    // condition for minimum choose
    if(n < 1) return 0;
    while (r > 0){
        p *= n, k *= r;
        ll m = __gcd(p, k);
        p /= m, k /= m, n--, r--;        
    }
    return p;
}

// Get vector with the prime factors of number

vector < int > prime_factorization(ll n){
    vector < int > factors;
    while(n % 2 == 0) 
        factors.push_back(2), n /= 2;
    for(int i = 3; i <= sqrt(n); i += 2)
        while(n % i == 0) factors.push_back(i), n /= i;
    if(n > 2) 
        factors.push_back(n);
    return factors;
}

// Convert Decimal to any base

string decimal_to_any_base(ll decimal, ll base){
    if(decimal == 0) return "0";
    string num = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    do{
        result.push_back(num[decimal % base]);
        decimal /= base;
    }while(decimal != 0);

    return string(result.rbegin(), result.rend());
}

// Convert any base to decimal

ll  any_base_to_decimal(string str, int base) {
    auto val = [](char c){
        return (c >= '0' && c <= '9' ? (int) c - '0' : (int) c - 'A' + 10);
    };

    ll len = sz(str), power = 1, num = 0, i;
    for (i = len - 1; i >= 0; i--) {
        num += val(str[i]) * power;
        power = power * base;
    }
    return num;
}
// Euler's phi
int phi(int n)
{
    int result = n;
  
    for(int p = 2; p * p <= n; ++p)
    {
         
        // Check if p is a prime factor.
        if (n % p == 0)
        {
             
            while (n % p == 0)
                n /= p;
                 
            result -= result / p;
        }
    }
  
    if (n > 1)
        result -= result / n;
         
    return result;
}

// Linear seive

const int N = 10000000;
vector<int> lp(N+1);
vector<int> pr;

for (int i=2; i <= N; ++i) {
    if (lp[i] == 0) {
        lp[i] = i;
        pr.push_back(i);
    }
    for (int j=0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= N; ++j) {
        lp[i * pr[j]] = pr[j];
    }
}

// Geometric sequence
float sumOfGP(float a, float r, int n)
{
    // a : first term, r : common ratio, n : number of terms
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + a;
        a = a * r;
    }
    return sum;
}

// mod inverse

template < typename T = int > struct Power_Inverse {
    
    T n, r, mod;
    vector < T > fact, inv;

    T fast_power(T b, T e, T MOD){
        T power = 1;
        while(e){
            if(e & 1) power = mod_combine(power, b, MOD);
            e >>= 1, b = mod_combine(b, b, MOD);
        }
        return power % MOD;
    }

    T Inverse(T N, T MOD){
        return fast_power(N, MOD - 2, MOD) % MOD;
    }

    Power_Inverse(T N, T R, T MOD){
        n = N, r = R, mod = MOD;
        fact.assign(n + 10, 1), inv.resize(n + 10, 1);
        for(ll i = 1; i <= n; i++){
            fact[i] = mod_combine(fact[i - 1], i, mod);
            inv[i] = Inverse(fact[i], mod);
        }
    }

    // Combination

    T nCr(){
        if(r > n) return 0ll;
        return (((fact[n] % mod) * (inv[r] % mod) % mod) * (inv[n - r] % mod)) % mod;
    }

    // Permutation

    T nPr(){
        if(r > n) return 0ll;
        return ((fact[n] % mod) * (inv[r] % mod)) % mod;
    }

};

/* Divisibility : 

- Rule: A number passes the test for 8 if the last three digits form a number is divisible 8.
- Rule: A number is divisible by 9 if the sum of the digits are evenly divisible by 9.
- Rule: A number passes the test for 11 if the difference of the sums of alternating digits is divisible by 11.(This abstract and confusing sounding rule is much clearer with a few examples).

Arithemetic progression : 
xn = a + d(n−1)



*/

// Pisano Period for Fibonacci numbers mod m O(m * m)

long pisano(long m){
    long prev = 0;
    long curr = 1;
    long res = 0;
 
    for(int i = 0; i < m * m; i++){
        long temp = 0;
        temp = curr;
        curr = (prev + curr) % m;
        prev = temp;
 
        if (prev == 0 && curr == 1)
            res = i + 1;
    }
    return res;
}
 
// Calculate Fn mod m
long fibonacciModulo(long n, long m){
     
    // Getting the period
    long pisanoPeriod = pisano(m);
 
    n = n % pisanoPeriod;
 
    long prev = 0;
    long curr = 1;
 
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
 
    for(int i = 0; i < n - 1; i++){
        long temp = 0;
        temp = curr;
        curr = (prev + curr) % m;
        prev = temp;
    }
    return curr % m;
}


// BIG INT

struct BigInt {

    const int BASE = 1000000000;
    vector < int > v;
    
    BigInt() {}

    BigInt(const long long &val) {
        *this = val;
    }
    
    BigInt(const string &val) {
        *this = val;
    
    }
    
    int size() const { return v.size(); }
    
    bool zero() const { return v.empty(); }
    
    BigInt& operator = (long long val) {
        v.clear();
        while (val) {
            v.push_back(val % BASE);
            val /= BASE;
        }
        return *this;
    }

    BigInt& operator = (const BigInt &a) {
        v = a.v;
        return *this;
    }

    BigInt& operator = (const vector < int > &a) {
        v = a;
        return *this;
    }

    BigInt& operator = (const string &s) {
        *this = 0;
        for (const char &ch : s)
            *this = *this * 10 + (ch - '0');
        return *this;
    }
    
    bool operator < (const BigInt &a) const {
        if (a.size() != size())
            return size() < a.size();
        for (int i = size() - 1; i >= 0; i--)
            if (v[i] != a.v[i])
                return v[i] < a.v[i];
        return false;
    }

    bool operator > (const BigInt &a) const {
        return a < *this;
    }

    bool operator == (const BigInt &a) const {
        return (!(*this < a) && !(a < *this));
    }

    bool operator <= (const BigInt &a) const {
        return ((*this < a) || !(a < *this));
    }
    
    ll val(){
        ll ans = 0;
        for (int i = 0; i < size(); i++)
            ans = ans * 10 + v[i];
        return ans;
    }

    BigInt operator + (const BigInt &a) const {
        BigInt res = *this;
        int idx = 0, carry = 0;
        while (idx < a.size() || carry) {
            if (idx < a.size())
                carry += a.v[idx];
            if (idx == res.size())
                res.v.push_back(0);
            res.v[idx] += carry;
            carry = res.v[idx] / BASE;
            res.v[idx] %= BASE;
            idx++;
        }
        return res;
    }
    
    BigInt& operator += (const BigInt &a) {
        *this = *this + a;
        return *this;
    }
    
    BigInt operator * (const BigInt &a) const {
        BigInt res;
        if (this -> zero() || a.zero())
            return res;
        res.v.resize(size() + a.size());
        for (int i = 0; i < size(); i++) {
            if (v[i] == 0)
                continue;
            long long carry = 0;
            for (int j = 0; carry || j < a.size(); j++) {
                carry += 1LL * v[i] * (j < a.size() ? a.v[j] : 0);
                while (i + j >= res.size())
                    res.v.push_back(0);
                carry += res.v[i + j];
                res.v[i + j] = carry % BASE;
                carry /= BASE;
            }
        }
        while (!res.v.empty() && res.v.back() == 0)
            res.v.pop_back();
        return res;
    }

    BigInt& operator *= (const BigInt &a) {
        *this = *this * a;
        return *this;
    }

    BigInt& operator -= (const BigInt &b){
        if(*this < b)
            throw("UNDERFLOW");
        int n = this -> size(), m = b.size();
        int i, t = 0, s;
        for (i = 0; i < n;i++){
            if(i < m)
                s = this -> v[i] - b.v[i]+ t;
            else
                s = this -> v[i] + t;
            if(s < 0)
                s += 10,
                t = -1;
            else
                t = 0;
            this -> v[i] = s;
        }
        while(n > 1 && this -> v[n - 1] == 0)
            this -> v.pop_back(),
            n--;
        return *this;
    }

    BigInt operator - (const BigInt&b){
        BigInt a = *this;
        a -= b;
        return a;
    }

    BigInt operator -- (const int){
        *this -= BigInt(1);
        return *this;
    }

    BigInt operator ++ (const int){
        *this += BigInt(1);
        return *this;
    }

    BigInt& operator /=(const ll a) {
        ll carry = 0;
        for (int i = (int) v.size() - 1; i >= 0; i--) {
            ll cur = v[i] + carry * BASE;
            v[i] = cur / a;
            carry = cur % a;
        }
        while (!v.empty() && v.back() == 0)
            v.pop_back();
        return *this;
    }
    
    BigInt operator / (const ll a) {
        ll carry = 0;
        vector < int > res = this -> v;
        for (int i = (int) res.size() - 1; i >= 0; i--) {
            ll cur = res[i] + carry * BASE;
            res[i] = cur / a;
            carry = cur % a;
        }
        BigInt ans;
        ans = res;
        return ans;
    }
    
    BigInt operator % (const ll a){
        ll res = 0;
        for (int i = (int) v.size() - 1; i >= 0; i--)
            res = (res * 10 + v[i]) % a;
        BigInt ans = res;
        return ans;
    }

    BigInt& operator %= (const ll a) {
        *this = *this % a;
        return *this;
    }

    friend ostream& operator<<(ostream &out, const BigInt &a) {
        out << (a.zero() ? 0 : a.v.back());
        for (int i = (int) a.v.size() - 2; i >= 0; i--)
            out << setfill('0') << setw(9) << a.v[i];
        return out;
    }

    friend istream& operator>>(istream &in, BigInt &a) {
        string s;
        in >> s;
        a = s;
        return in;
    }

};

// MOD INT

template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) { 
    for (const T &x : v) out << x << ' '; 
    return out;
}

template < int MOD = 1000000007 > struct ModInt {

    int val;

    ModInt(int V = 0) : val(V) { val %= MOD; }

    ModInt& operator += (const ModInt& rhs) {
        if ((val += rhs.val) >= MOD) val -= MOD;
        return *this;
    }
    ModInt& operator += (const int rhs) {
        if ((val += rhs) >= MOD) val -= MOD;
        return *this;
    }

    ModInt& operator -= (const ModInt& rhs) { 
        if ((val += MOD - rhs.val) >= MOD) val -= MOD; 
        return *this; 
    }
    ModInt& operator -= (const int rhs) { 
        if ((val += MOD - rhs) >= MOD) val -= MOD; 
        return *this; 
    }

    ModInt& operator *= (const ModInt& rhs) { val = (1ll * val * rhs.val) % MOD; return *this; }
    ModInt& operator *= (const int rhs) { val = (1ll * val * rhs) % MOD; return *this; }

    ModInt& operator /= (const ModInt& rhs) { return *this *= rhs.inverse(); }
    ModInt& operator /= (const int rhs) { return *this *= ModInt(rhs).inverse(); }

    ModInt& operator %= (const ModInt& rhs) { val %= rhs.val; return *this; }
    ModInt& operator %= (const int rhs) { val %= rhs; return *this; }

    ModInt& operator ++() { return *this += 1; }
    ModInt& operator --() { return *this -= 1; }
 
    ModInt operator ++(int unused) { ModInt res(*this); ++*this; return res; }
    ModInt operator --(int unused) { ModInt res(*this); --*this; return res; }
    
    ModInt operator + (const ModInt& rhs) const { ModInt res(*this); return res += rhs; }
    ModInt operator + (const int rhs) const { ModInt res(*this); return res += rhs; }

    ModInt operator % (const ModInt& rhs) const { ModInt res(*this); return res %= rhs; }
    ModInt operator % (const int rhs) const { ModInt res(*this); return res %= rhs; }

    ModInt operator - (const ModInt& rhs) const { ModInt res(*this); return res -= rhs; }
    ModInt operator - (const int rhs) const { ModInt res(*this); return res -= rhs; }

    ModInt operator * (const ModInt& rhs) const { ModInt res(*this); return res *= rhs; }
    ModInt operator * (const int rhs) const { ModInt res(*this); return res *= rhs; }

    ModInt operator / (const ModInt& rhs) const { ModInt res(*this); return res /= rhs; }
    ModInt operator / (const int rhs) const { ModInt res(*this); return res /= rhs; }

    ModInt& operator = (const ModInt& rhs) { val = rhs.val; return *this; }
    ModInt& operator = (const int rhs) { val = rhs; return *this; }

    bool operator == (const ModInt& rhs) const { return val == rhs.val; }
    bool operator == (const int rhs) const { return val == rhs; }

    bool operator != (const ModInt& rhs) const { return val != rhs.val; }
    bool operator != (const int rhs) const { return val != rhs; }

    bool operator < (const ModInt& rhs) const { return val < rhs.val; }
    bool operator < (const int rhs) const { return val < rhs; }

    bool operator <= (const ModInt& rhs) const { return val <= rhs.val; }
    bool operator <= (const int rhs) const { return val <= rhs; }

    bool operator > (const ModInt& rhs) const { return val > rhs.val; }
    bool operator > (const int rhs) const { return val > rhs; }

    bool operator >= (const ModInt& rhs) const { return val >= rhs.val; }
    bool operator >= (const int rhs) const { return val >= rhs; }

    int operator () () const { return val; }

    ModInt inverse() const { return power(MOD - 2); }

    ModInt power(ll n) const {
        ModInt a = *this, res = 1;
        while (n > 0) {
            if (n & 1) res *= a;
            a *= a, n >>= 1;
        }
        return res;
    }

    ModInt power(ModInt n) const {
        ModInt a = *this, res = 1;
        int e = n();
        while (e > 0) {
            if (e & 1) res *= a;
            a *= a, e >>= 1;
        }
        return res;
    }

    friend ModInt operator ^ (ModInt rhs, ll n) { return rhs.power(n); }
    friend ModInt operator ^ (ModInt rhs, ModInt n) { return rhs.power(n); }

    friend std::istream& operator>>(std::istream& is, ModInt& x) noexcept { return is >> x.val; }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& x) noexcept { return os << x.val; }

};
using Mint = ModInt < 998244353 >;


// Suffix Array

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


// Manacher's algorithm

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

// for even lengths

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}


// manacher's (GeeksforGeeks implementation)

void findLongestPalindromicString()
{
    int N = strlen(text);
    if(N == 0)
        return;
    N = 2*N + 1; //Position count
    int L[N]; //LPS Length Array
    L[0] = 0;
    L[1] = 1;
    int C = 1; //centerPosition
    int R = 2; //centerRightPosition
    int i = 0; //currentRightPosition
    int iMirror; //currentLeftPosition
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;
    int diff = -1;
     
    //Uncomment it to print LPS Length array
    //printf("%d %d ", L[0], L[1]);
    for (i = 2; i < N; i++)
    {
        //get currentLeftPosition iMirror for currentRightPosition i
        iMirror = 2*C-i;
        L[i] = 0;
        diff = R - i;
        //If currentRightPosition i is within centerRightPosition R
        if(diff > 0)
            L[i] = min(L[iMirror], diff);
 
        //Attempt to expand palindrome centered at currentRightPosition i
        //Here for odd positions, we compare characters and
        //if match then increment LPS Length by ONE
        //If even position, we just increment LPS by ONE without
        //any character comparison
        while ( ((i + L[i]) < N && (i - L[i]) > 0) &&
            ( ((i + L[i] + 1) % 2 == 0) ||
            (text[(i + L[i] + 1)/2] == text[(i - L[i] - 1)/2] )))
        {
            L[i]++;
        }
 
        if(L[i] > maxLPSLength) // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }
 
        //If palindrome centered at currentRightPosition i
        //expand beyond centerRightPosition R,
        //adjust centerPosition C based on expanded palindrome.
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
        //Uncomment it to print LPS Length array
        //printf("%d ", L[i]);
    }
    
    //printf("\n");
    start = (maxLPSCenterPosition - maxLPSLength)/2;
    end = start + maxLPSLength - 1;
    printf("LPS of string is %s : ", text);
    for(i=start; i<=end; i++)
        printf("%c", text[i]);
    printf("\n");
}
