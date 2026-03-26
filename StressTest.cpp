#include <bits/stdc++.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;
#define int long long
mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int Random(int l,int r) {
    return l + (rng()%(r-l+1));
}
const int N = 1e3;
int dp[N];
int n, m, a, b;
int solve(int x) {
    if (x == m)
        return 0;

    int op1 = 1e9;
    if ((x >> 1) >= m)
        op1 = solve(x >> 1) + a;
    return dp[x] = min(op1, solve(x - 1) + b);
}
int32_t main() {
    srand(time(nullptr));
    int testCases = 1e3;

    for (int i = 0; i<testCases; ++i) {
        n = Random(3, 900);
        m = Random(1, n);
        a = Random(1, 500);
        b = Random(1, 1000);
        memset(dp, -1, sizeof dp);
        int ans1 = solve(n), ans2 = 0;
        while (n > m) {
            int nn = n >> 1;
            if (nn < m) {
                ans2 += (n - m) * b;
                break;
            }
            ans2 += min((n - nn) * b, a);
            n = nn;
        }

        cout << ans1 << ' ' << ans2 << '\n';

        assert(ans1 == ans2);
    }
}
