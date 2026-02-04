template<typename T, class CMP = function<T(const T &, const T &)>>
class SparseTable {
public:
    int n{};
    vector<int> lg;              // precomputed logs
    vector<vector<T>> sp;
    CMP func;

    void build(const vector<T> &a, const CMP &f) {
        func = f;
        n = (int)a.size();

        // precompute logs: lg[i] = floor(log2(i))
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;

        int max_log = lg[n] + 1;
        sp.assign(max_log, {});
        sp[0] = a;

        for (int j = 1; j < max_log; ++j) {
            int len = 1 << j;
            sp[j].resize(n - len + 1);
            for (int i = 0; i + len <= n; ++i) {
                sp[j][i] = func(sp[j - 1][i], sp[j - 1][i + (len >> 1)]);
            }
        }
    }

    T get(int l, int r) const {
        int k = lg[r - l + 1];
        return func(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
