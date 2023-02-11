template <class T> class MaxSegmentTree {
private:
    /** The operation to use for combining two elements. (Must be associative)
     */
    T comb(T a, T b) { return std::max(a, b); }
    const T DEFAULT = 0;  // Will overflow if T is an int

    vector<T> segtree;
    int len;

public:
    MaxSegmentTree() : len(0), segtree(0, DEFAULT) {}
    MaxSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

    void init(int sz){
        segtree.assign(sz * 2, DEFAULT);
        len = sz;
    }

    /** Sets the value at ind to val. */
    void set(int ind, T val) {
        assert(0 <= ind && ind < len);
        ind += len;
        segtree[ind] = val;
        for (; ind > 1; ind /= 2) {
            segtree[ind >> 1] = comb(segtree[ind], segtree[ind ^ 1]);
        }
    }

    /** @return the minimum element in the range [start, end) */
    T range_max(int start, int end) {
        assert(0 <= start && start < len && 0 < end && end <= len);
        T sum = DEFAULT;
        for (start += len, end += len; start < end; start /= 2, end /= 2) {
            if ((start & 1) != 0) { sum = comb(sum, segtree[start++]); }
            if ((end & 1) != 0) { sum = comb(sum, segtree[--end]); }
        }
        return sum;
    }

    int size(){
        return len;
    }
};