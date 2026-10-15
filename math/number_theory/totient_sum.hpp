mint totient_sum(long long N){
    if(N==1)return 1;
    if(N==2)return 2;
    if(N==3)return 4;
    int sqrtN=sqrtl(N);
    vector<long long>Q;
    for(int i=1;i<=sqrtN;i++)Q.emplace_back(N/i);
    for(int i=sqrtN;i;i--)if(Q.back()!=i)Q.emplace_back(i);
    vector<mint>S(Q.size()),T(Q.size());
    for(int i=0;i<Q.size();i++)S[i]=(mint)Q[i]*(Q[i]+1)/2-1,T[i]=Q[i]-1;
    vector<bool>prime(sqrtN+1,1);
    for(long long x=2;x<=sqrtN;x++)if(prime[x]){
        for(long long y=x*x;y<=sqrtN;y+=x)prime[y]=0;
        for(int i=0;i<Q.size()&&Q[i]>=x*x;i++){
            S[i]-=x*(S[Q[i]/x<=sqrtN?Q.size()-Q[i]/x:N/(Q[i]/x)-1]-S[Q.size()-x+1]);
            T[i]-=T[Q[i]/x<=sqrtN?Q.size()-Q[i]/x:N/(Q[i]/x)-1]-T[Q.size()-x+1];
        }
    }
    for(int i=0;i<Q.size();i++)S[i]-=T[i];
    vector<int>ps,idx(sqrtN+1);
    for(int i=2;i<=sqrtN;i++)if(prime[i])idx[i]=ps.size(),ps.emplace_back(i);
    mint ans=1;
    function<void(long long,long long,int,mint)>dfs=[&](long long n,int p,int e,mint f){
        ans+=e==0?p-1:f*p;
        ans+=f*(S[n<=sqrtN?n-1:Q.size()-N/n]-S[Q.size()-p]);
        if(p<=N/n/p)dfs(n*p,p,e+1,e==0?p-1:f*p);
        for(int i=idx[p]+1;i<ps.size()&&ps[i]<=N/n/ps[i];i++)dfs(n*ps[i],ps[i],1,f*(ps[i]-1));
    };
    dfs(1,2,0,1);
    return ans;
}