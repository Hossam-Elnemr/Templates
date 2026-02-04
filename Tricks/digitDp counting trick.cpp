

// Problem: Sum of numbers in range [L, R] that each number contains at most k different digits
// Problem link: https://codeforces.com/problemset/problem/1073/E





// Always, the answers are complicated - and the questions are simple.
#include <bits/stdc++.h>
using namespace std;
# define int long long
const int N = 19, mod = 998244353;
int dpCount[N][1 << 11][2][2], dp[N][1 << 11][2][2], pw[N];
int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);


    pw[0] = 1;
    for (int i = 1; i<N; ++i)
        pw[i] = pw[i - 1] * 10 % mod;

    memset(dpCount, -1, sizeof dpCount);
    memset(dp, -1, sizeof dp);


    string l, r; cin >> l >> r;
    int k; cin >> k;
    while (l.size() < r.size())
        l = '0' + l;


    auto MASK = [](int mask, int d) {
        return mask == 0 && d == 0? 0 : 1 << d | mask;
    };

    int n = l.size();
    function<int(int, int, bool, bool)> solve = [&](int i, int mask, bool tl, bool tr) -> int {
        if (i == n)
            return __builtin_popcount(mask) <= k;
        int &ans = dpCount[i][mask][tl][tr];
        if (~ans)
            return ans;
        ans = 0;
        int low = tl? l[i] - '0' : 0;
        int high = tr? r[i] - '0' : 9;

        for (int j = low; j<=high; ++j) {
            ans += solve(i + 1, MASK(mask, j), tl && (j == l[i] - '0'), tr && (j == r[i] - '0'));
            ans %= mod;
        }
        return ans;
    };


    function<int(int, int, bool, bool)> sum = [&](int i, int mask, bool tl, bool tr) -> int {
        if (i == n)
            return 0;
        int &ans = dp[i][mask][tl][tr];
        if (~ans)
            return ans;
        ans = 0;
        int low = tl? l[i] - '0' : 0;
        int high = tr? r[i] - '0' : 9;

        for (int j = low; j<=high; ++j) {
            ans += sum(i + 1, MASK(mask, j), tl && (j == l[i] - '0'), tr && (j == r[i] - '0'));
            ans %= mod;
            int ways = solve(i + 1, MASK(mask, j), tl && (j == l[i] - '0'), tr && (j == r[i] - '0'));
            ans += ways * pw[n - i - 1] * j;
            ans %= mod;
        }
        return ans;
    };
    solve(0, 0, true, true);

    cout << sum(0, 0, true, true);
}
