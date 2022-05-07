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