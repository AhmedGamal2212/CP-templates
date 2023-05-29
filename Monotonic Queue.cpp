template<typename T> struct monotonic_stack {
    stack<pair<T, T>> st;

    void push(int x) {
        if(st.empty()) {
            st.emplace(x, x);
        } else {
            st.emplace(x, std::max(x, st.top().second));
        }
    }

    T pop() {
        T p = st.top().first;
        st.pop();
        return p;
    }

    T top() {
        return st.top().first;
    }

    T max() {
        return st.top().second;
    }

    int size() {
        return st.size();
    }

    bool empty() {
        return st.empty();
    }
};

template<typename T> struct monotonic_queue {
    monotonic_stack<T> push_st, pop_st;

    void push(int x) {
        push_st.push(x);
    }

    void move() {
        while(not push_st.empty()) {
            pop_st.push(push_st.pop());
        }
    }

    T pop() {
        if(pop_st.empty())
            move();
        return pop_st.pop();
    }

    T front() {
        if(pop_st.empty())
            move();
        return pop_st.top();
    }

    T max() {
        if(pop_st.empty()) {
            return push_st.max();
        }
        if(push_st.empty()) {
            return pop_st.max();
        }
        return std::max(pop_st.max(), push_st.max());
    }

    int size() {
        return push_st.size() + pop_st.size();
    }

    bool empty() {
        return push_st.empty() and pop_st.empty();
    }
};