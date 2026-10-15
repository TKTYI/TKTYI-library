// https://github.com/TKTYI/TKTYI-library/blob/main/math/fft/number_theoretic_transformation.hpp
typedef vector<ll> vl;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define sz(a) (int)(a).size()
const ll mod=998244353;
ll pow_mod(ll a,ll n,ll m){
  ll res=1%m;a%=m;
  while(n){
    if(n%2)res=res*a%m;
    a=a*a%m;n/=2;
  }
  if(res<0)res+=m;
  return res;
}
void ntt(vl&F,bool inv){
  if(sz(F)==1)return;
  vl F0(sz(F)/2),F1(sz(F)/2);
  rep(i,0,sz(F)/2)F0[i]=F[2*i],F1[i]=F[2*i+1];
  ntt(F0,inv);ntt(F1,inv);
  ll s=pow_mod(3,inv?mod-1-(mod-1)/sz(F):(mod-1)/sz(F),mod),t=1;
  rep(i,0,sz(F)){
    F[i]=(F0[i<sz(F)/2?i:i-sz(F)/2]+t*F1[i<sz(F)/2?i:i-sz(F)/2])%mod;
    t=t*s%mod;
  }
  if(inv)rep(i,0,sz(F))F[i]=(mod+1)/2*F[i]%mod;
}
vl conv(const vl&f,const vl&g){
  int n=1;
  while(n<=sz(f)+sz(g))n*=2;
  vl F(n),G(n);
  rep(i,0,sz(f))F[i]=f[i];
  rep(i,0,sz(g))G[i]=g[i];
  ntt(F,false);ntt(G,false);
  vl H(n);
  rep(i,0,n)H[i]=F[i]*G[i]%mod;
  ntt(H,true);
  H.resize(sz(f)+sz(g)-1);
  return H;
}