void prefix_2d(){
    vector<vector<int>> v;
    int n, m; // Row and Col

    // Accumulate
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j] += v[i][j - 1];
        }
    }
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            v[i][j] += v[i - 1][j];
        }
    }
    int i, j; // Upper left
    int k, l; // Lower right
    // sum
    v[k][l] - v[k][j - 1] - v[i - 1][l] + v[i - 1][j - 1];
}
