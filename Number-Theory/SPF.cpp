long long spf[(int)1e7+5];
void SPF(){
    for(int i = 0; i<=(int)1e7+5; i++)
        spf[i] = i;
    for(long long i = 2; i*i<=(int)1e7+5; i++)
    {
        if(spf[i] == i)
            for(long long j = i*i; j<=(int)1e7+1; j+=i)
                spf[j] = min(i,spf[j]);
    }
}
