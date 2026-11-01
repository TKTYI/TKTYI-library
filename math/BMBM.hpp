// https://github.com/TKTYI/TKTYI-library/blob/main/math/BMBM.hpp
template<typename T>
struct BMBM{
  vector<T>Q,A;
  BMBM(vector<T>_A):A(_A){
    int N=sz(A);
    Q={1};
    int L=0;
    vector<T>B={1};
    int n0=-1;
    T b=1;
    rep(n,0,N){
      T delta=0;
      rep(i,0,sz(Q))if(i<=n)delta+=Q[i]*A[n-i];
      if(!delta.val())continue;
      vector<T>Q_new=Q;
      rep(i,0,sz(B)){
        while(sz(Q_new)<=i+n-n0)Q_new.emplace_back(0);
        Q_new[i+n-n0]-=B[i]*delta/b;
      }
      int L_new;
      if(2*L<=n){L_new=n+1-L;B=Q;n0=n;b=delta;}
      else L_new=L;
      Q=Q_new;
      L=L_new;
    }
    reverse(all(Q));
    assert(Q.back().val()==1);
    Q.erase(Q.end()-1);
    rep(i,0,sz(Q))Q[i]=-Q[i];
  }
  T get(ll n){
    if(n<sz(A))return A[n];
    if(!sz(Q))return 0;
    int L=sz(Q);
    n+=L-sz(A);
    vector<T>F={0,1},G={1};
    if(sz(Q)==1)F={Q[0]};
    while(n){
      if(n&1){
        G=convolution_naive(F,G);
        while(sz(G)>L){
          rep(i,0,L)G[sz(G)-1-L+i]+=G.back()*Q[i];
          G.erase(G.end()-1);
        }
      }
      F=convolution_naive(F,F);
      while(sz(F)>L){
        rep(i,0,L)F[sz(F)-1-L+i]+=F.back()*Q[i];
        F.erase(F.end()-1);
      }
      n>>=1;
    }
    T ans=0;
    rep(i,0,sz(G))ans+=G[i]*A[sz(A)-L+i];
    return ans;
  }
};
