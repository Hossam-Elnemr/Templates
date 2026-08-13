# define int long long
using row = vector<long long>;
using matrix = vector<row>;
 
const long long MOD = 10000;
 
struct Matrix {
    int n;
    matrix mat;
 
    Matrix(int n) : n(n), mat(n, row(n, 0)) {}
 
    void make_identity() {
        for (int i = 0; i < n; ++i) {
            mat[i][i] = 1;
        }
    }
 
    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
 
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
 
                if (mat[i][k] == 0) continue;
 
                long long val = mat[i][k] % MOD;
                for (int j = 0; j < n; ++j) {
                    res.mat[i][j] += val * other.mat[k][j];
 
                    res.mat[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    row multiply(const row& v) {
        row res(n, 0);
 
        for (int i = 0; i < n; ++i) {
 
            if (v[i] == 0) continue;
 
            long long val = v[i] % MOD;
            for (int j = 0; j < n; ++j) {
                res[j] += val * mat[i][j];
                res[j] %= MOD;
            }
        }
        return res;
    }
};
 
Matrix power(Matrix base, long long exp) {
    Matrix res(base.n);
    res.make_identity();
    while (exp > 0) {
        if (exp & 1) res = res * base;
        base = base * base;
        exp >>= 1;
    }
    return res;
}
