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


    ll comb(ll n, ll r){
        ll ans = 1, k = 1;

        updmin(r, n - r);

        if(r){
            while(r){
                ans *= n, k *= r;
                ll g = gcd(ans, k);
                ans /= g, k /= g;
                n--, r--;
            }
        }else{
            ans = 1;
        }
        return ans;
    }
};