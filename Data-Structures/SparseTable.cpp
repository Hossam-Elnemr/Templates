class SparseTable {
public:
    int n{};
    vector<int> lg;              // precomputed logs
    vector<vector<long long>> sp;
 
    void build(const vector<long long> &a) {
        n = (int)a.size();
 
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
 
        int max_log = lg[n] + 1;
        sp.assign(max_log, {});
        sp[0] = a;
 
        for (int j = 1; j < max_log; ++j) {
            int len = 1 << j;
            sp[j].resize(n - len + 1);
            for (int i = 0; i + len <= n; ++i) {
                sp[j][i] = max(sp[j - 1][i], sp[j - 1][i + (len >> 1)]);
            }
        }
    }
 
    long long get(int l, int r) {
        int k = lg[r - l + 1];
        return max(sp[k][l], sp[k][r - (1 << k) + 1]);
    }
};
