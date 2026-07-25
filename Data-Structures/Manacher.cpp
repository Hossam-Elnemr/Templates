vector<int> manacherOdd(string s)
{
    int n = s.size();
    s = "$" + s + "^"; // $ and ^ are start and end markers
    vector<int> d(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++)
    {
        d[i] = min(r - i, d[l + r - i]);

        while (s[i - d[i]] == s[i + d[i]])
            ++d[i];

        if (i + d[i] > r)
            l = i - d[i], r = i + d[i];
    }

    return vector<int>(d.begin() + 1, d.end() - 1);
}

// returns vector d of size 2*n-1
// let i be 0-based
// lets define odd_pal_len[i] as the length of the odd palindrome with center i
// and even_pal_len[i] as the length of the even palindrome with left-center i
// d[i] where i is even (0-based) represent odd_pal_len[i/2]+1
// d[i] where i is odd (0-based) represent even_pal_len[i/2]+1
// TL;DR:
//      odd_pal_len[i]  = d[i * 2] - 1
//      even_pal_len[i] = d[i * 2 + 1] - 1
vector<int> manacher(const string &s)
{
    string t = "";
    for (auto c : s)
        t += string("#") + c; // # is padding to represent even-length palindromes

    auto d = manacherOdd(t + "#");
    return vector<int>(d.begin() + 1, d.end());
}

vector<pair<int, int>> palindromeRanges(string s)
{
    auto d = manacher(s);
    vector<pair<int, int>> ret;
    for (int i = 0; i < s.size(); i++)
    {
        { // odd
            int len = d[i * 2] - 1;
            if (len > 0) // > 1 if you don't want single character, 0 otherwise
                ret.push_back({i - len / 2, i + len / 2});
        }

        { // even
            int len = d[i * 2 + 1] - 1;
            if (len)
                ret.push_back({i - len / 2 + 1, i + len / 2});
        }
    }
    return ret;
}
