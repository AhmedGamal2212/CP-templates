struct lazy_freq {
    int n, timer, sf = int(5e4);
    vector<int> freq, time;

    explicit lazy_freq(int n) {
        this -> n = n;
        timer = 0;
        time = freq = vector<int>(n + sf + 5, 0);
    }

    void clear(){
        timer++;
    }

    bool has_key(int key){
        return time[key + sf] == timer;
    }

    void set(int key, int value){
        time[key + sf] = timer;
        freq[key + sf] = value;
    }

    int get(int key){
        return freq[key + sf];
    }
};