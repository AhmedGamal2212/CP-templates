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