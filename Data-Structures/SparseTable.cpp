struct SparseTable{
#define T int
    T *a[30]{};
    int *lg;
    // const int &(*merge)(const int &, const int &);
    T merge(int x, const int y) {
    	return __gcd(x, y);
    }
    explicit SparseTable(const int n, const int b[]){
        lg = new int[n+1]{};
        for(int i=2;i<=n;++i)
            lg[i] = lg[i/2] + 1;
        for(auto & j : a)
            j = new T[n];
        for(int i=0;i<n;++i)
            a[0][i] = b[i];
        for(int j=1;j<30;++j)
            for(int i=0;i<=n-(1<<j);++i)
                a[j][i] = merge(a[j-1][i], a[j-1][i+(1<<(j-1))]);
    }
    ~SparseTable() {
        delete[] lg;
        for(const auto & j : a)
            delete[] j;
    }
    [[nodiscard]] T get(const int l, const int r) {
        return merge(a[lg[r-l+1]][l], a[lg[r-l+1]][r-(1<<lg[r-l+1])+1]);
    }
};
