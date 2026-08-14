// NTT / Convolution - Pair Sum Counting
// Complexity: O(N log N)
//
// Usage:
// freq[x] = number of occurrences of value x
//
// auto res = multiply(freq, freq);
//
// res[s] = number of ordered pairs (a, b) such that:
// a + b = s
//
// Note:
// - (a, b) and (b, a) are both counted.
// - Results are modulo MOD.
// - For exact pair counts, make sure the answer doesn't exceed MOD.

const int N = 8e5 + 5; // CHANGE: max possible value / required frequency size

vector<int> freq(N); // freq[x] = occurrences of x

const int MOD = 998244353;
const int ROOT = 3;

int modpow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = (long long)res * a % MOD;
        a = (long long)a * a % MOD;
        b >>= 1;
    }
    return res;
}

void ntt(vector<int> &a, bool invert)
{
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1)
    {
        int wlen = modpow(ROOT, (MOD - 1) / len);

        if (invert)
            wlen = modpow(wlen, MOD - 2);

        for (int i = 0; i < n; i += len)
        {
            int w = 1;

            for (int j = 0; j < len / 2; j++)
            {
                int u = a[i + j];
                int v = (long long)a[i + j + len / 2] * w % MOD;

                a[i + j] = u + v;
                if (a[i + j] >= MOD)
                    a[i + j] -= MOD;

                a[i + j + len / 2] = u - v;
                if (a[i + j + len / 2] < 0)
                    a[i + j + len / 2] += MOD;

                w = (long long)w * wlen % MOD;
            }
        }
    }

    if (invert)
    {
        int inv_n = modpow(n, MOD - 2);
        for (int &x : a)
            x = (long long)x * inv_n % MOD;
    }
}

vector<long long> multiply(vector<int> const &a, vector<int> const &b)
{
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;

    fa.resize(n);
    fb.resize(n);

    ntt(fa, false);
    ntt(fb, false);

    for (int i = 0; i < n; i++)
        fa[i] = (long long)fa[i] * fb[i] % MOD;

    ntt(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        result[i] = fa[i];

    return result;
}
