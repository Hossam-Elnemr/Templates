const int N = 1e5;
bitset<N + 1> notPrime;
vector<int> primes;
void sieve() {
    notPrime[0] = notPrime[1] = true;
    for(long long i = 2; i<=N; ++i) {
        if(notPrime[i]) continue;
        primes.push_back(i);
        for(long long j = i*i; j<=N; j+=i)
            notPrime[j] = true;
    }
}
