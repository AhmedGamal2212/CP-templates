// Those who cannot remember the past are
// condemned to repeat it (use DP -_-)
// - George Santayana

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define ll long long
#define ull unsigned long long
#define MOD 1000000007
#define PI acos(-1)
#define ceil(a, b) (((a) / (b)) + ((a) % (b) ? 1 : 0))
#define imin INT_MIN
#define imax INT_MAX
#define llmax LLONG_MAX
#define llmin LLONG_MIN
#define inf 2000000000
#define nl '\n'
#define ppcnt __builtin_popcount
#define ppcntll __builtin_popcountll
#define clz __builtin_clz
#define clzll __builtin_clzll
#define ctz __builtin_ctz
#define ctzll __builtin_ctzll
#define modulo(a, b, mod) ((((a) % (mod)) + ((b) % (mod))) % (mod))
#define cnte(v, x) count(all(v), (x))
#define mine(v) min_element(all(v))
#define maxe(v) max_element(all(v))
#define updmin(a, b) a = min(a, b)
#define updmax(a, b) a = max(a, b)
#define findmod(x, m) x = ((x) % (m) + (m)) % m
#define getmod(x, m) ((x) % (m) + (m)) % (m)
#define clr(memo, x) memset(memo, x, sizeof memo)
#define debug(x) cout << "x: " << (x) << nl;
#define debug2(x, y) cout << "x: " << (x) << " y: " << y << nl;
#define ordered_set tree<pair<int, int>, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_map tree<int, int, less<>, rb_tree_tag, tree_order_statistics_int_update>

//vector<int> dx = {0, 0, 1, -1, 1, 1, -1, -1}, dy = {1, -1, 0, 0, 1, -1, 1, -1};
//vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};
//vector<int> dx = {2, 1, -1, -2, -2, -1, 1, 2}, dy = {1, 2, 2, 1, -1, -2, -2, -1};

template<typename T = int>
istream &operator>>(istream &in, vector<pair<int, int>> &v) {
    for (auto &[x, y]: v) in >> x >> y;
    return in;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (T &i: v) in >> i;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x: v)
        out << x << ' ';
    return out;
}

template<typename T = pair<int, int>>
ostream &operator<<(ostream &out, const vector<pair<int, int>> &v) {
    for (auto &[x, y]: v) {
        out << x << ' ' << y << nl;
    }
    return out;
}

void Start_Crushing() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
int n, LOG;
vector<vector<int>> adj, up;
vector<int> depth;

void dfs(int src){
    for(auto& nxt : adj[src]){
        depth[nxt] = depth[src] + 1;
        up[nxt][0] = src;

        for(int j = 1; j < LOG; j++){
            up[nxt][j] = up[up[nxt][j - 1]][j - 1];
        }
        dfs(nxt);
    }
}

int get_lca(int u, int v){
    if(depth[u] < depth[v])
        swap(u, v);

    int k = depth[u] - depth[v];
    for(int bit = 0; bit < LOG; bit++){
        if(k & (1 << bit))
            u = up[u][bit];
    }

    if(u == v)
        return u;

    for(int bit = LOG - 1; ~bit; bit--){
        if(up[u][bit] != up[v][bit]){
            u = up[u][bit];
            v = up[v][bit];
        }
    }

    return up[u][0];
}

void solve(){
    cin >> n;
    adj.assign(n + 5, vector<int>());
    depth.assign(n + 5, 0);
    LOG = 0;
    while((1 << LOG) <= n)
        LOG++;

    up.assign(n, vector<int>(LOG));

    for(int u = 0; u < n; u++){
        int num; cin >> num;
        while(num--){
            int v; cin >> v;
            adj[u].emplace_back(v);
        }
    }
    dfs(0);

    int q; cin >> q;
    while(q--){
        int u, v; cin >> u >> v;
        cout << get_lca(u, v) << nl;
    }
}

void set_file(string &file_name) {
    freopen((file_name + ".in").c_str(), "r", stdin);
    freopen((file_name + ".out").c_str(), "w", stdout);
}

int main() {
    Start_Crushing();

//    string file_name = "knapsack";
//    set_file(file_name);
    int t = 1;
//    /*Multiple test cases?*/ cin >> t;
    while (t--) {
        solve();
//        if (!t)
//            break;
        cout << nl;
    }

//    for(int tc = 1; tc <= t; tc++){
//        cout << "Case " << tc << ": ";
//        solve();
////        if(tc != t)
//            cout << nl;
//    }

    return 0;
}
