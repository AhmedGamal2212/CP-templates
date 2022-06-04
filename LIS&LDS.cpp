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
#define PI 3.14159265
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
#define debug(x) cout << "x: " << (x) << nl;
#define debug2(x, y) cout << "x: " << (x) << " y: " << y << nl;
#define ordered_set tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_map tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update>

//vector<int> dx = {0, 0, 1, -1, 1, 1, -1, -1}, dy = {1, -1, 0, 0, 1, -1, 1, -1};
//vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};

template<typename T = int> istream& operator>>(istream& in, vector<pair<int, int>>& v){
    for (auto& [x, y] : v) in >> x >> y;
    return in;
}

template<typename T = int> istream& operator>>(istream& in, vector<T>& v){
    for (T& i : v) in >> i;
    return in;
}

template<typename T = int> ostream& operator<<(ostream& out, const vector<T>& v){
    for (const T& x : v)
        out << x << ' ';
    return out;
}

template<typename T = pair<int, int>> ostream& operator << (ostream& out, const vector<pair<int, int>>& v){
    for(auto& [x, y] : v){
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

void solve(){
    int n;
    while(cin >> n){
        vector<int> v(n);
        cin >> v;


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

        d.assign(n + 1, inf);
        d.front() = -inf;

        reverse(all(v));

        for (int i = 0; i < n; i++) {
            int pos = int(upper_bound(all(d), v[i]) - d.begin());
            bool found = d[int(lower_bound(all(d), v[i]) - d.begin())] == v[i];

            if (d[pos - 1] < v[i] and v[i] < d[pos]) {
                d[pos] = v[i];
            }
            lds[n - i - 1] = pos - found;
        }
        
    }
}

int main(){
    Start_Crushing();
//    freopen("perm.in", "r", stdin);

    int t = 1;
//    /*Multiple test cases?*/ cin >> t;
    while (t--) {
        solve();
//        if(!t)
//            break;
//        cout << nl;
    }

//    for(int tc = 1; tc <= t; tc++){
//        cout << "Case #" << tc << ": ";
//        solve();
//        if(tc != t)
//            cout << nl;
//    }

    return 0;
}