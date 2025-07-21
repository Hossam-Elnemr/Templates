const int mod = 1e9+7;
template <typename T> void matmul(vector<vector<T>> &a, vector<vector<T>> b) {
    int n = a.size(), m = a[0].size(), p = b[0].size();
    vector<vector<T>> c(n, vector<T>(p));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < m; k++) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j])%mod;
            }
        }
    }
    a = c;
}
template <typename T> struct Matrix {
    vector<vector<T>> mat;
    Matrix() {}
    Matrix(vector<vector<T>> a) { mat = a; }
    Matrix(int n, int m) {
        mat.resize(n);
        for (int i = 0; i < n; i++) { mat[i].resize(m); }
    }
    int rows() const { return mat.size(); }
    int cols() const { return mat[0].size(); }
    void makeiden() {
        // used on new matrices, if matrix has entries make it zero first or use mat[i][j] = (i==j)
        for (int i = 0; i < rows(); i++) { mat[i][i] = 1LL; }
    }
    Matrix operator*=(const Matrix &b) {
        matmul(mat, b.mat);
        return *this;
    }
    Matrix operator*(const Matrix &b) { return Matrix(*this) *= b; }
};
 
template<typename T> Matrix<T> matrixExpo(Matrix<T>& m, int n) {
   if (n==0) {
       Matrix<T> id(m.rows(), m.cols());
       id.makeiden();
       return id;
   }
    if (n&1) return m * matrixExpo(m, n-1);
    Matrix<T> temp = matrixExpo(m, n/2);
    return temp*temp;
}
