for (int i = 0; i<n; ++i) {
        int L = i;
        while (L<n) {
            int l = L-1, r = n, before = sparse.query(i, L);
            while (r>l+1) {
                int m = l+r>>1;
                int cur = sparse.query(i, m);
                if (cur == before)
                    l = m;
                else
                    r = m;
            }
            ans[before] += l-L+1;
            L = l+1;
        }
    }
