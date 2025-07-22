class Sqrt {
public:
    vector<int> a, blocks;
    int SQ;
    Sqrt(int n) {
        SQ = sqrt(n) + 1;
        a.resize(n, 0);
        blocks.resize(SQ, 0);
    }
    void set(int i, int val) {
        blocks[i/SQ] += (val - a[i]);
        a[i] = val;
    }
    int get(int l, int r) {
        int ans = 0;
        int begin = l/SQ, end = r/SQ;
        for (int i = begin; i<end; ++i)
            ans += blocks[i];
        for (int i = begin*SQ; i<l; ++i)
            ans -= a[i];
        for (int i = r; i>=end*SQ; --i)
            ans += a[i];
        return ans;
    }
};
