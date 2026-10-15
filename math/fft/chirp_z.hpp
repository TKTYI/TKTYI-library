// https://github.com/TKTYI/TKTYI-library/blob/main/math/fft/chirp_z.hpp
template<typename T>
vector<T>chirp_z(vector<T>f,int M,T a,T r){
  int N=f.size();
  if(r==T(0)){
    vector<T>ans(M);
    T s(1);
    for(int i=0;i<N;i++){
      ans[0]+=f[i]*s;
      s*=a;
    }
    for(int i=1;i<M;i++)ans[i]=f[0];
    return ans;
  }
  T ir=r.inv();
  vector<T>pr(N+M-1,T(1)),pir(N+M-1,T(1));
  for(int i=1;i<N+M-1;i++)pr[i]=pr[i-1]*r,pir[i]=pir[i-1]*ir;
  for(int i=1;i<N+M-1;i++)pr[i]*=pr[i-1],pir[i]*=pir[i-1];
  vector<T>g(N);
  T s(1);
  for(int i=0;i<N;i++){
    g[N-1-i]=f[i]*s*pir[i];
    s*=a;
  }
  vector<T>ans=convolution(g,pr);
  ans.erase(ans.begin(),ans.begin()+N-1);
  ans.resize(M);
  for(int i=0;i<M;i++)ans[i]*=pir[i];
  return ans;
}