


struct Coordinate_Compression {

    map < ll, ll > mapping;
    vector < ll > orig, comp, nums;
    int sz;

    Coordinate_Compression(vector < ll >& Nums){
        sz = 1;
        nums = Nums;
        sort(all(nums));
        nums.resize(unique(all(nums)) - nums.begin());
        for(auto& i : nums)
            mapping[i] = sz++;
        orig.resize(sz);
        for(auto& [f, s] : mapping) orig[s] = f;
        comp = nums;
        for(auto& i : comp) i = mapping[i];
    }

    vector < ll > orignal(){
        return orig;
    }

    vector < ll > compressed(){
        return comp;
    }

};

