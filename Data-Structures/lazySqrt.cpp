const int N = 2e5 + 5, SQ = 325;
int n;
long long a[N], buckets[N / SQ], lazySet[N / SQ], lazyAdd[N / SQ];

void build(int x) { // builds a single block
    buckets[x] = 0;
    int start = x * SQ, end = min((x + 1) * SQ, n);
    for (int i = start; i<end; ++i) {
        if (lazySet[x])
            a[i] = lazySet[x];
        a[i] += lazyAdd[x];
        buckets[x] += a[i];
    }
    lazyAdd[x] = 0;
    lazySet[x] = 0;
}

void update(int l, int r, int val, bool set) {
    build(l / SQ);
    build(r / SQ);

    for (int i = l; i<=r; ) {
        if (i%SQ == 0 && i + SQ - 1 <= r) {
            int curBlock = i / SQ;
            if (set) {
                buckets[curBlock] = val * SQ;
                lazySet[curBlock] = val;
                lazyAdd[curBlock] = 0;
            }
            else {
                buckets[curBlock] += val * SQ;
                lazyAdd[curBlock] += val;
            }

            i += SQ;
        }
        else {
            if (set)
                a[i] = val;
            else
                a[i] += val;
            ++i;
        }
    }

    build(l / SQ);
    build(r / SQ);
}

long long get(int l, int r) {
    build(l / SQ);
    build(r / SQ);

    long long ans = 0;
    for (int i = l; i<=r; ) {
        if (i%SQ == 0 && i + SQ - 1 <= r) {
            ans += buckets[i / SQ];
            i += SQ;
        }
        else {
            ans += a[i];
            ++i;
        }
    }
    return ans;
}
