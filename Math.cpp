namespace Math {
    template<typename T> static ll bin_exp(T b, T e, int mod = MOD) {
        ll res = 1;
        while(e) {
            if(e & 1)
                res = modulo(res, b, mod);

            b = modulo(b, b, mod);
            e >>= 1;
        }
        return res;
    }

    template<typename T, typename E> static void sub(T& a, E b, int mod = MOD) {
        a -= b;
        if(a < 0)
            a += mod;
    }

    template<typename T, typename E> static void add(T& a, E b, int mod = MOD) {
        a += b;
        if(a >= mod)
            a -= mod;
    }

    template<typename T> static T inv(T x, T mod = MOD) {
        x %= mod;
        if(x < 0)
            x += mod;

        T b = mod, ret = 0, c = 1;
        while(x) {
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

    template<typename T> static void mul(T& a, T b, T mod = MOD) {
        ll res = 0;
        while(b) {
            if(b & 1) {
                add(res, a, mod);
            }
            add(a, a, mod);
            b >>= 1;
        }
        a = res;
    }
};