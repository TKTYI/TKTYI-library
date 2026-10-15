// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/multiplicative_prefix_sum.hpp
struct multiplicative_prefix_sum{
    long long N;
    int sqrtN;
    vector<bool>prime;
    vector<long long>Q;
    multiplicative_prefix_sum(long long _N):N(_N),sqrtN(sqrtl(N)),prime(sqrtN+1,1){
        prime[0]=prime[1]=0;
        for(int i=2;i<=sqrtN;i++)if(prime[i])for(int j=2*i;j<=sqrtN;j+=i)prime[j]=0;
        for(int i=1;i<=sqrtN;i++)Q.emplace_back(N/i);
        for(int i=sqrtN;i;i--)if(Q.back()!=i)Q.emplace_back(i);
    }
    //完全乗法的関数g s.t, g(1)=1 についてS[i]=\sum_{p<=Q[i]}g(p)を求める
    //g(p):g(p)を返す
    //init(N):g(1)+...+g(N)を返す
    template<class T,T(*g)(long long),T(*init)(long long)>
    vector<T>Lucy(){
        vector<T>S(Q.size());
        for(int i=0;i<Q.size();i++)S[i]=init(Q[i]);
        for(int x=2;x<=sqrtN;x++)if(prime[x]){
            for(int i=0;i<Q.size()&&Q[i]/x>=x;i++){
                long long t=Q[i]/x;
                int idx=t<=sqrtN?Q.size()-t:N/t-1;
                assert(Q[idx]==t);
                S[i]-=g(x)*(S[idx]-S[Q.size()-(x-1)]);
            }
        }
        for(int i=0;i<Q.size();i++)S[i]--;
        return S;
    }
    //乗法的関数f s.t, f(1)=1 についてS[i]=\sum_{p<=Q[i]}f(p)が求まっているときにDP[i]=f(2)+...+f(Q[i])を求める
    //nec(p,e,F):f(p^e)=Fからf(p^(e+1))を返す
    template<class T,T(*nec)(int,int,T)>
    vector<T>Min25_sieve(const vector<T>&S){
        assert(S.size()==Q.size());
        vector<T>DP=S;
        for(int x=sqrtN;x>=2;x--)if(prime[x]){
            for(int i=0;i<Q.size()&&Q[i]/x>=x;i++){
                T f=nec(x,0,1);
                for(long long e=1,y=x;x<=Q[i]/y;y*=x,f=nec(x,e++,f)){
                    long long t=Q[i]/y;
                    int idx=t<=sqrtN?Q.size()-t:N/t-1;
                    assert(Q[idx]==t);
                    DP[i]+=f*(DP[idx]-S[Q.size()-x])+nec(x,e,f);
                }
            }
        }
        for(int i=0;i<Q.size();i++)DP[i]++;
        return DP;
    }
};