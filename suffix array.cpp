struct suffix_array {
    string x;
    int n;
    vector<int> suffix;

    suffix_array(string s = "") {
        x = s + '$';
        n = (int)x.size();
        suffix.resize(n);
    }

    void count_sort(vector<int> &p,  vector<int> &c) {
        vector<int> cnt(n);
        for(auto a: c)
            cnt[a]++;
        vector<int> p_new(n), pos(n);
        pos[0] = 0;
        for(int i = 1; i < n; i++)
            pos[i] = pos[i - 1] + cnt[i - 1];
        for(auto a: p){
            int i = c[a];
            p_new[pos[i]] = a;
            pos[i]++;
        }
        p = p_new;
    }

    void build() {
        vector<int> c(n);
        vector<pair<char, int>> v(n);
        for(int i = 0; i < n; i++)
            v[i] = {x[i], i};
        sort(all(v));
        for(int i = 0; i < n; i++)
            suffix[i] = v[i].second;
        c[suffix[0]] = 0;
        for(int i = 1; i < n; i++)
            c[suffix[i]] = c[suffix[i - 1]] + (v[i].first != v[i - 1].first);

        for(int k = 0; (1 << k) < n; k++){
            for(int i = 0; i < n; i++)
                suffix[i] = (suffix[i] - (1 << k) + n) % n;
            count_sort(suffix, c);
            c[suffix[0]] = 0;
            vector <int> c_new(n);
            c_new[suffix[0]] = 0;
            for(int i = 1; i < n; i++) {
                pair<int, int> prev = {c[suffix[i - 1]], c[(suffix[i - 1] + (1 << k)) % n]};
                pair<int, int> cur = {c[suffix[i]], c[(suffix[i] + (1 << k)) % n]};
                c_new[suffix[i]] = c_new[suffix[i - 1]] + (prev != cur);
            }
            c = c_new;
        }
    }
};


// Manacher's algorithm

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

// for even lengths

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}


// manacher's (GeeksforGeeks implementation)

void findLongestPalindromicString()
{
    int N = strlen(text);
    if(N == 0)
        return;
    N = 2*N + 1; //Position count
    int L[N]; //LPS Length Array
    L[0] = 0;
    L[1] = 1;
    int C = 1; //centerPosition
    int R = 2; //centerRightPosition
    int i = 0; //currentRightPosition
    int iMirror; //currentLeftPosition
    int maxLPSLength = 0;
    int maxLPSCenterPosition = 0;
    int start = -1;
    int end = -1;
    int diff = -1;
     
    //Uncomment it to print LPS Length array
    //printf("%d %d ", L[0], L[1]);
    for (i = 2; i < N; i++)
    {
        //get currentLeftPosition iMirror for currentRightPosition i
        iMirror = 2*C-i;
        L[i] = 0;
        diff = R - i;
        //If currentRightPosition i is within centerRightPosition R
        if(diff > 0)
            L[i] = min(L[iMirror], diff);
 
        //Attempt to expand palindrome centered at currentRightPosition i
        //Here for odd positions, we compare characters and
        //if match then increment LPS Length by ONE
        //If even position, we just increment LPS by ONE without
        //any character comparison
        while ( ((i + L[i]) < N && (i - L[i]) > 0) &&
            ( ((i + L[i] + 1) % 2 == 0) ||
            (text[(i + L[i] + 1)/2] == text[(i - L[i] - 1)/2] )))
        {
            L[i]++;
        }
 
        if(L[i] > maxLPSLength) // Track maxLPSLength
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }
 
        //If palindrome centered at currentRightPosition i
        //expand beyond centerRightPosition R,
        //adjust centerPosition C based on expanded palindrome.
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
        //Uncomment it to print LPS Length array
        //printf("%d ", L[i]);
    }
    //printf("\n");
    start = (maxLPSCenterPosition - maxLPSLength)/2;
    end = start + maxLPSLength - 1;
    printf("LPS of string is %s : ", text);
    for(i=start; i<=end; i++)
        printf("%c", text[i]);
    printf("\n");
}