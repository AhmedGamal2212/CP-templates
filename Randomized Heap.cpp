template<typename T> struct randomized_heap {
    struct TreeNode {
        T val;
        TreeNode *l, *r;
        TreeNode(): l(nullptr), r(nullptr), val(numeric_limits<T>::min()) {};
        explicit TreeNode(T val): val(val), l(nullptr), r(nullptr) {};
        TreeNode(T val, TreeNode* l, TreeNode* r): val(val), l(l), r(r) {};
    };
    TreeNode* root;
    int mode{}, size{};

    randomized_heap(){
        root = nullptr;
        mode = 1;
        size = 0;
    }
    explicit randomized_heap(int mode){
        root = nullptr;
        this -> mode = mode;
        size = 0;
    }

    TreeNode* merge(TreeNode* h_1, TreeNode* h_2){
        if(not h_1 or not h_2){
            return h_1 ? h_1 : h_2;
        }
        if(mode == -1){
            if(h_1 -> val < h_2 -> val)
                swap(h_1, h_2);
        }else{
            if(h_1 -> val > h_2 -> val)
                swap(h_1, h_2);
        }
        
        if(rand() & 1)
            swap(h_1 -> l, h_1 -> r);
        h_1 -> l = merge(h_1 -> l, h_2);
        return h_1;
    }

    void push(T value){
        auto new_node = new TreeNode(value);
        root = merge(root, new_node);
        size++;
    }

    T top(){
        return root -> val;
    }

    void pop(){
        assert(size);
        root = merge(root -> l, root -> r);
        size--;
    }

    bool empty(){
        return not size;
    }
};