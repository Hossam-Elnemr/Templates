const int N = 1e5;
bitset<N> notPrime;
void sieve() {
    notPrime[0] = notPrime[1] = true;
    for(long long i = 2; i*i<N; ++i) {
        if(notPrime[i]) continue;

        for(long long j = i*i; j<N; j+=i)
            notPrime[j] = true;
    }
}
