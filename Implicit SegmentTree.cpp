struct ImplicitSegmentTree {
    static const long long N = 1ll<<60;
    struct Node {
        int sum{}, lazy_add{};
        int L{}, R{};
        void add(int x, long long sz) {
            sum += x * sz;
            lazy_add += x;
        }
    };
    std::vector<Node> seg_data{Node()};

    void propagate(int ni, long long lx, long long rx) {
        if(!seg_data[ni].lazy_add || rx - lx == 1) return;

        seg_data[seg_data[ni].L].add(seg_data[ni].lazy_add, (rx-lx)/2);
        seg_data[seg_data[ni].R].add(seg_data[ni].lazy_add, (rx-lx)/2);

        seg_data[ni].lazy_add = 0;
    }

    void check(int &x){
        if(x) return;
        x = (int)seg_data.size();
        seg_data.push_back(Node());
    }

    long long get(long long l, long long r, int ni=0, long long lx=0, long long rx=N){
        if(lx >= l && rx <= r)
            return seg_data[ni].sum;
        if(rx <= l || lx >= r)
            return 0;

        check(seg_data[ni].L);
        check(seg_data[ni].R);
        propagate(ni, lx, rx);

        long long mid = (lx + rx) / 2;
        return get(l, r, seg_data[ni].L, lx, mid) + get(l, r, seg_data[ni].R, mid, rx);
    }

    void add(long long l, long long r, int v, int ni=0, long long lx=0, long long rx=N) {
        if(lx >= l && rx <= r) {
            seg_data[ni].add(v, rx-lx);
            return;
        }
        if(rx <= l || lx >= r)
            return;

        check(seg_data[ni].L);
        check(seg_data[ni].R);
        propagate(ni, lx, rx);

        long long mid = (lx + rx) / 2;
        add(l, r, v, seg_data[ni].L, lx, mid);
        add(l, r, v, seg_data[ni].R, mid, rx);

        seg_data[ni].sum = seg_data[seg_data[ni].L].sum + seg_data[seg_data[ni].R].sum;
    }
};
