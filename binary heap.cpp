struct binary_heap {
    int n;
    vector<int> v;

    void init(){
        n = 0;
        v = {-inf};
    }

    binary_heap(){
        init();
    }

    binary_heap(vector<int>& v){
        init();
        for(auto& i : v){
            add(i);
        }
    }

    void add(int x){
        n++;
        v.emplace_back(x);
        shift_up(n);
    }

    int get_min(){
        return v[1];
    }

    int extract_min(){
        int x = v[1];
        v[1] = v[n];
        n--;
        shift_down(1);
        return x;
    }

    void shift_up(int pos){
        while(pos > 1 and v[pos / 2] > v[pos]){
            swap(v[pos], v[pos / 2]);
            pos >>= 1;
        }
    }

    void shift_down(int pos){
        while(pos * 2 <= n){
            int child = pos * 2;
            if(pos * 2 + 1 <= n and v[pos * 2 + 1] < v[child]){
                child = pos * 2 + 1;
            }
            if(v[pos] <= v[child])
                break;
            swap(v[pos], v[child]);
            pos = child;
        }
    }

    bool empty() {
        return not n;
    }
};