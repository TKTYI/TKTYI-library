https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/factorial.hpp
template<typename T>
vector<T>inv(const vector<T>&f){
    assert(f[0].val());
    vector<T>g{f[0].inv()};
    while(g.size()<f.size()){
      vector<T>x(f.begin(),f.begin()+min(f.size(),2*g.size()));
      x=convolution(x,convolution(g,g));
      g.resize(2*g.size());
      for(int i=g.size()/2;i<min(x.size(),g.size());i++)g[i]-=x[i];
    }
    return {g.begin(),g.begin()+f.size()};
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
template<typename T>
vector<T>multipoint_evaluation(vector<T>f,vector<T>p){
    int N=p.size(),n=1;
    while(n<N)n*=2;
    vector<vector<T>>seg(2*n,vector<T>(1,1));
    for(int i=0;i<N;i++)seg[i+n]=vector<T>{-p[i],1};
    for(int i=n-1;i;i--)seg[i]=convolution(seg[2*i],seg[2*i+1]);
    seg[1]=div(f,seg[1]).second;
    for(int i=1;i<n;i++)seg[2*i]=div(seg[i],seg[2*i]).second,seg[2*i+1]=div(seg[i],seg[2*i+1]).second;
    vector<T>ans(N);
    for(int i=0;i<N;i++)if(!seg[i+n].empty())ans[i]=seg[i+n][0];
    return ans;
}
mint factorial(long long N){
    assert(N>=0);
    if(!N)return 1;
    int n=sqrtl(N);
    mint ans=1;
    while(n*n>N)n--;
    while(N>n*n)ans*=N--;
    queue<vector<mint>>que;
    for(int i=1;i<=n;i++)que.emplace(vector<mint>{i,1});
    while(que.size()>1){
        auto u=que.front();que.pop();
        auto v=que.front();que.pop();
        que.emplace(convolution(u,v));
    }
    vector<mint>p(n);
    for(int i=0;i<n;i++)p[i]=(long long)i*n;
    auto me=multipoint_evaluation(que.front(),p);
    for(auto x:me)ans*=x;
    return ans;
}