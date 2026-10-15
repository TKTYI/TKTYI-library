// https://github.com/TKTYI/TKTYI-library/blob/main/math/fft/fast_mod_convolution.hpp
// depend on ACL
template<typename T>
struct formal_power_series{
    private:
    size_t N;
    vector<T>F;
    public:
    formal_power_series(size_t _N):N(_N){F.assign(N,0);}
    T&operator[](int i){return F[i];}
    void operator+=(formal_power_series G){
        for(int i=0;i<N&&i<G.F.size();i++)F[i]+=G.F[i];
    }
    void operator-=(formal_power_series G){
        for(int i=0;i<N&&i<G.F.size();i++)F[i]-=G.F[i];
    }
    void operator*=(formal_power_series G){
        F=convolution(F,G.F);
        F.resize(N);
    }
    void operator*=(T k){
        for(int i=0;i<N;i++)F[i]*=k;
    }
    void operator/=(formal_power_series G){
        F=convolution(F,G.inv().F);
        F.resize(N);
    }
    formal_power_series operator+(formal_power_series G){
        formal_power_series res(N);
        for(int i=0;i<N;i++)res.F[i]=F[i];
        res+=G;
        return res;
    }
    formal_power_series operator-(formal_power_series G){
        formal_power_series res(N);
        for(int i=0;i<N;i++)res.F[i]=F[i];
        res-=G;
        return res;
    }
    formal_power_series operator*(formal_power_series G){
        formal_power_series res(N);
        for(int i=0;i<N;i++)res.F[i]=F[i];
        res*=G;
        return res;
    }
    formal_power_series operator*(T k){
        formal_power_series res(N);
        for(int i=0;i<N;i++)res.F[i]=F[i];
        res*=k;
        return res;
    }
    formal_power_series operator/(formal_power_series G){
        formal_power_series res(N);
        for(int i=0;i<N;i++)res.F[i]=F[i];
        res*=G.inv();
        return res;
    }
    formal_power_series pow(long long n){
        formal_power_series res(N);
        formal_power_series A(N);
        for(int i=0;i<N;i++)A.F[i]=F[i];
        res[0]=1;
        while(n){
            if(n&1LL)res*=A;
            A*=A;n>>=1;
        }
        return res;
    }
    formal_power_series inv(){
        formal_power_series res(N);
        formal_power_series A(N);
        for(int i=0;i<N;i++)A.F[i]=-F[i];
        res[0]=1;
        A.F[0]++;
        int n=N;
        while(n){
            res+=res*A;
            A*=A;
            n>>=1;
        }
        return res;
    }
    formal_power_series dif(){
        formal_power_series res(N);
        for(int i=1;i<N;i++)res[i-1]=F[i]*i;
        return res;
    }
    formal_power_series inte(){
        formal_power_series res(N);
        for(int i=1;i<N;i++)res[i]=F[i-1]/i;
        return res;
    }
    formal_power_series log(){
        return (dif()*inv()).inte();
    }
    formal_power_series exp(){
        formal_power_series res(N);
        res[0]=1;
        int n=N;
        while(n){
            formal_power_series A=this-log(res);
            A[0]++;
            res*=A;
            n>>=1;
        }
        return res;
    }
};
vm inv(const vm&f){
  vm g{1/f[0]};
  while(sz(g)<sz(f)){
    vm x(f.begin(),f.begin()+min(sz(f),2*sz(g)));
    x=convolution(x,convolution(g,g));
    g.resize(2*sz(g));
    for(int i=sz(g)/2;i<min(sz(x),sz(g));i++)g[i]-=x[i];
  }
  return {g.begin(),g.begin()+sz(f)};
}
vm log(const vm&f){
    assert(f[0]==1);
    ll N=sz(f);
    vm df=f;
    for(int i=0;i<N;i++)df[i]*=i;
    df.erase(df.begin());
    vm f_inv=inv(f),g=convolution(df,f_inv);
    g.resize(N-1);
    g.insert(g.begin(),0);
    for(int i=1;i<N;i++)g[i]/=i;
    return g;
}
vm exp(const vm&f){
    const ll N=sz(f);
    assert(N&&f[0]==0);
    vm g={1};
    while(sz(g)<N){
        ll M=sz(g);
        vm x(f.begin(),f.begin()+min(N,2*M));
        x[0]++;
        g.resize(2*M);
        auto log_g=log(g);
        for(int i=0;i<x.size();i++)x[i]-=log_g[i];
        x=convolution(x,{g.begin(),g.begin()+M});
        for(int i=M;i<min(sz(x),2*M);i++)g[i]=x[i];
    }
    return{g.begin(),g.begin()+N};
}
template<typename T>
pair<vector<T>,vector<T>>div(vector<T>f,const vector<T>&g){
    if(f.size()<g.size())return make_pair(vector<T>(0),f);
    reverse(f.begin(),f.end());
    vector<T>h=g;
    reverse(h.begin(),h.end());
    while(h.size()+g.size()<=f.size())h.emplace_back(0);
    vector<T>q=convolution(f,inv(h));
    q.resize(f.size()-g.size()+1);
    reverse(q.begin(),q.end());
    auto r=convolution(g,q);
    reverse(f.begin(),f.end());
    for(int i=0;i<f.size();i++)r[i]=f[i]-r[i];
    while(!r.empty()&&r.back()==T(0))r.erase(r.end()-1);
    return make_pair(q,r);
}