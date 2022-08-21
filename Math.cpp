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


