template < typename T = int > struct Sparse_Table {

    struct Node {

        ll val;

        Node(ll V = 0) : val(V) {}
    
        Node operator = (const T& rhs) {
            val = rhs;
            return *this;
        }

    };

    int n, LOG;
    vector < vector < Node > > table;
    vector < int > Bin_Log;
    Node DEFAULT;

    Sparse_Table(vector < T >& vec){
        n = sz(vec), DEFAULT = 0, LOG = __lg(n) + 1;
        table = vector < vector < Node > > (n + 10, vector < Node > (LOG));
        Bin_Log = vector < int > (n + 10);
        for(int i = 2; i <= n; i++)
            Bin_Log[i] = Bin_Log[i >> 1] + 1;
        for(int i = 0; i < n; i++)
            table[i][0] = vec[i];
        Build_Table();
    }

    Node operation(Node a, Node b){
        Node res;
        res.val = a.val + b.val;
        return res;
    }

    void Build_Table(){
        for(int log = 1; log < LOG; log++)
            for(int i = 0; i + (1 << log) - 1 < n; i++)
                table[i][log] = operation(table[i][log - 1], table[i + (1 << (log - 1))][log - 1]);
    }

    Node query_1(int L, int R){
        int log = Bin_Log[R - L + 1];
        return operation(table[L][log], table[R - (1 << log) + 1][log]);
    }

    Node query_log_n(int L, int R){
        T answer = DEFAULT;
        for (int log = LOG; log >= 0; log--){
            if (L + (1 << log) - 1 <= R) {
                answer = operation(answer, table[L][log]);
                L += 1 << log;
            }
        }
        return answer;
    }

    T query(int L, int R, bool overlap = false){
        return (overlap ? query_1(L, R) : query_log_n(L, R)).val;
    }

};