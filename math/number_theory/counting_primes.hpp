// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/counting_primes.hpp
long long counting_primes(long long N){
    int sqrtN=sqrtl(N);
    vector<long long>Q;
    for(int i=1;i<=sqrtN;i++)Q.emplace_back(N/i);
    for(int i=sqrtN;i;i--)if(Q.back()!=i)Q.emplace_back(i);
    vector<long long>S(Q.size());
    for(int i=0;i<Q.size();i++)S[i]=Q[i]-1;
    vector<bool>prime(sqrtN+1,1);
    for(long long x=2;x<=sqrtN;x++)if(prime[x]){
        for(long long y=x*x;y<=sqrtN;y+=x)prime[y]=0;
        for(int i=0;i<Q.size()&&Q[i]>=x*x;i++)S[i]-=S[Q[i]/x<=sqrtN?Q.size()-Q[i]/x:N/(Q[i]/x)-1]-S[Q.size()-x+1];
    }
    return S[0];
}