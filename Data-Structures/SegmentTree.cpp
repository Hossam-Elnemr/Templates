struct item {
    int val, count;
};
# define item int
class SegmentTree {
private:
    item* arr;
    int sz;
    item NEUTRAL = {0};
    item merge(item a, item b) {
        return {a + b};
    }
    item single(int v) {
        return {v};
    }
    void set(int i, int val, int x, int lx, int rx) {
        if (rx - lx == 1) {
            arr[x] = single(val);
            return;
        }
        const int m = lx+rx>>1;
        if (i<m)
            set(i, val, 2*x+1, lx, m);
        else
            set(i, val, 2*x+2, m, rx);
        arr[x] = merge(arr[x*2+1],arr[x*2+2]);
    }
    item get(int l, int r, int x, int lx, int rx) {
        if (lx>=r || rx<=l)
            return NEUTRAL;
        if (lx>=l && rx<=r)
            return arr[x];
        const int m = lx+rx>>1;
        item left = get(l,r,x*2+1, lx, m);
        item right = get(l,r,x*2+2, m, rx);
        return merge(left,right);
    }
    void build(int n, int a[], int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < n)
                arr[x] = single(a[lx]);
            return;
        }
        int m = lx+rx>>1;
        build(n, a, x*2+1, lx, m);
        build(n, a, x*2+2, m, rx);
        arr[x] = merge(arr[x*2+1],arr[x*2+2]);
    }
    public:
    void build(int n, int a[]) {
        build(n, a, 0, 0, sz);
    }
    explicit SegmentTree(const int n) {
        sz = 1;
        while (sz < n)
            sz <<= 1;
        arr = new item[2*sz];
    }
    item get(const int l, const int r) { // log(n)
        return get(l, r, 0, 0, sz);
    }
    void set(const int i, int val) { // log(n)
        set(i, val, 0, 0, sz);
    }

};
