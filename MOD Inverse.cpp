template<typename T = ll> struct MODINV {
 
    ll n;
    int mod;
    vector<ll> fact, inv;
 
    ll fast_power(ll b, ll e) {
        ll power = 1;
        while(e){
            if(e & 1) power = modulo(power, b, mod);
            e >>= 1, b = modulo(b, b, mod);
        }
        return power % mod;
    }
 
    ll inverse(ll x) {
        return fast_power(x, mod - 2) % mod;
    }
 
    MODINV(){
        n = mod = 0;
    }
 
    MODINV(ll n, int mod){
        assign(n, mod);
    }
 
    void assign(ll n_, int mod_){
        this -> n = n_;
        this -> mod = mod_;
        fact.assign(n + 10, 1), inv.resize(n + 10, 1);
        for(ll i = 1; i <= n; i++){
            fact[i] = modulo(fact[i - 1], i, mod);
            inv[i] = inverse(fact[i]);
        }
    }
 
    void add(T& a, T b){
        a += b;
        if(a >= mod)
            a -= mod;
    }
 
    void mul(T& a, T b){
        ll res = 0;
        while(b){
            if(b & 1) {
                add(res, a);
            }
            add(a, a);
            b >>= 1;
        }
        a = res;
    }
 
    T nCr(T n_, T r){
        T res = 1;
        for(auto& i : {fact[n_], inv[r], inv[n_ - r]})
            mul(res, i);
        return res;
    }

    T nPr(T n_, T r){
        T res = 1;
        for(auto& i : {fact[n_], inv[n_ - r]})
            mul(res, i);
        return res;
    }
};