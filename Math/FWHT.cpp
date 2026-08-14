// FWHT - XOR / OR / AND Convolution
// Complexity: O(N log N)
//
// Usage:
// auto res = multiply(a, b, XOR);
// auto res = multiply(a, b, OR);
// auto res = multiply(a, b, AND);
//
// res[x] = sum of a[i] * b[j] where:
// XOR: (i ^ j) == x
// OR : (i | j) == x
// AND: (i & j) == x
//
// Note:
// - Array size is automatically padded to a power of 2.
// - For frequency arrays, res[x] counts ordered pairs satisfying the operation.

enum Type {
    XOR,
    OR,
    AND
};

void fwht(vector<long long> &a, bool invert, Type type)
{
    int n = a.size();

    for (int len = 1; len < n; len <<= 1)
    {
        for (int i = 0; i < n; i += len << 1)
        {
            for (int j = 0; j < len; j++)
            {
                long long &x = a[i + j];
                long long &y = a[i + j + len];

                if (type == XOR)
                {
                    long long u = x, v = y;
                    x = u + v;
                    y = u - v;
                }

                else if (type == OR)
                {
                    if (!invert)
                        y += x;
                    else
                        y -= x;
                }

                else if (type == AND)
                {
                    if (!invert)
                        x += y;
                    else
                        x -= y;
                }
            }
        }
    }

    if (invert && type == XOR)
        for (long long &x : a)
            x /= n;
}

vector<long long> multiply(vector<int> const &a, vector<int> const &b, Type type)
{
    int n = 1;
    while (n < max(a.size(), b.size()))
        n <<= 1;

    vector<long long> fa(a.begin(), a.end());
    vector<long long> fb(b.begin(), b.end());

    fa.resize(n);
    fb.resize(n);

    fwht(fa, false, type);
    fwht(fb, false, type);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fwht(fa, true, type);

    return fa;
}
