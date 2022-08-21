struct Stack{
    vector<ll> sMax = {LLONG_MIN}, sMin = {LLONG_MAX}, s;
 
    void push(ll x){
        s.push_back(x);
        sMax.push_back(::max(x, sMax.back()));
        sMin.push_back(::min(x, sMin.back()));
    }
 
    bool empty(){
        return s.empty();
    }
 
    ll pop(){
        ll p = s.back();
        s.pop_back(), sMax.pop_back(), sMin.pop_back();
        return p;
    }
 
    ll max(){
        return sMax.back();
    }
 
    ll min(){
        return sMin.back();
    }
 
};
::Stack s1, s2;
 
void add(ll x){
    s2.push(x);
}
 
bool good(){
    ll mn = min(s1.min(), s2.min()),
    mx = max(s1.max(), s2.max());
 
    return mx - mn <= k;
}
 
void remove(ll x){
    if(s1.empty()){
        while(!s2.empty())
            s1.push(s2.pop());
    }
    s1.pop();
}