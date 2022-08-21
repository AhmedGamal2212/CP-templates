
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

// big int mod

ll big_int_mod(string& num, int mod){
	ll res = 0;
	for(auto& i : num){
		res = (res * 10 + int(i - '0')) % mod;
	}
	return res;
}


// binary exponentiation

ll bin_exp(ll b, ll e){
	ll res = 1;
	while(e){
		if(e & 1)
			res *= a;
		a *= a;
		b >>= 1;
	}
	return res;
}