template<typename T>
vector<T>inv(const vector<T>&f){
  vector<T>g{1/f[0]};
  while(g.size()<f.size()){
    vector<T>x(f.begin(),f.begin()+min(f.size(),2*g.size()));
    x=convolution(x,convolution(g,g));
    g.resize(2*sz(g));
    for(int i=g.size()/2;i<x.size()&&i<g.size();i++)g[i]-=x[i];
  }
  return {g.begin(),g.begin()+f.size()};
}
template<typename T>
vector<T>power_projection(const vector<T>&f,const vector<T>&g){
  assert(f.size()==g.size()&&!f.empty());
  int N=f.size()-1;
  vector<T>P(3*(N+1)),Q(3*(N+1));
  Q[0]=1;
  for(int i=0;i<=N;i++){
    P[3*i]=g[i];
    Q[3*i+1]=-f[i];
  }
  int n=N,k=1;
  while(n){
    auto R=Q;
    for(int i=1;i<=n;iS+=2)for(int j=0;j<=k;j++)R[(2*k+1)*i+j]=-Q[(2*k+1)*i+j];
    auto _P=convolution(P,R),_Q=convolution(Q,R);
    P=Q=vector<T>((4*k+1)*(n/2+1));
    for(int i=0;i<=n/2;i++)for(int j=0;j<=2*k;j++)P[(4*k+1)*i+j]=_P[(2*k+1)*(2*i+n%2)+j],Q[(4*k+1)*i+j]=_Q[(2*k+1)*2*i+j];
    n/=2;k*=2;
  }
  auto pp=convolution(P,inv(Q));
  return {pp.begin(),pp.begin()+N+1};
}