struct lazy_freq {
    int n, timer;
    vector<int> freq, time;

    lazy_freq(int n) {
        this -> n = n;
        timer = 0;
        freq.assign(n + 5, 0);
    }

    void clear(){
        timer++;
    }

    bool has_key(int key){
        return time[key] == timer;
    }

    void set(int key, int value){
        time[key] = timer;
        freq[key] = value;
    }

    int get(int key){
        return freq[key];
    }
};
