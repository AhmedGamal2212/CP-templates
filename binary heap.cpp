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

    int add(int x){
        n++;
        v.emplace_back(x);
        return shift_up(n);
    }

    int get_max(){
        return v[1];
    }

    pair<int, int> extract_max(){
        int x = v[1];
        v[1] = v[n];
        n--;
        v.pop_back();
        return {shift_down(1) * (n > 0), x};
    }

    int shift_up(int pos){
        while(pos > 1 and v[pos >> 1] < v[pos]){
            swap(v[pos], v[pos >> 1]);
            pos >>= 1;
        }
        return pos;
    }

    int shift_down(int pos){
        while(pos * 2 <= n){
            int child = pos * 2;
            if(pos * 2 + 1 <= n and v[pos * 2 + 1] > v[child]){
                child = pos * 2 + 1;
            }
            if(v[pos] >= v[child])
                break;
            swap(v[pos], v[child]);
            pos = child;
        }
        return pos;
    }

    int remove_pos(int pos){
        int x = v[pos];
        v[pos] = v[n];
        n--;
        v.pop_back();
        if(x > v[pos])
            shift_down(pos);
        else
            shift_up(pos);
        return x;
    }

    bool empty() {
        return not n;
    }

    int size(){
        return n;
    }
};