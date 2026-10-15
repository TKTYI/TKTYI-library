// https://github.com/TKTYI/TKTYI-library/blob/main/math/fft/fast_fourier_transformation.hpp
typedef vector<ll> vl;
typedef complex<double> C;
void fft(vector<C>&F,bool inv){
  if(sz(F)==1)return;
  vector<C>F0(sz(F)/2),F1(sz(F)/2);
  rep(i,0,sz(F)/2)F0[i]=F[2*i],F1[i]=F[2*i+1];
  fft(F0,inv);fft(F1,inv);
  rep(i,0,sz(F))F[i]=F0[i<sz(F)/2?i:(i-sz(F)/2)]+polar(1.,(inv?-1:1)*acos(-1.)*2./sz(F)*i)*F1[i<sz(F)/2?i:i-(sz(F)/2)];
  if(inv)rep(i,0,sz(F))F[i]/=2;
}
vl conv(const vl&f,const vl&g){
  int n=1;
  while(n<=sz(f)+sz(g))n*=2;
  vector<C>F(n),G(n);
  rep(i,0,sz(f))F[i]=f[i];
  rep(i,0,sz(g))G[i]=g[i];
  fft(F,false);fft(G,false);
  vector<C>H(n);
  rep(i,0,n)H[i]=F[i]*G[i];
  fft(H,true);
  vl h(sz(f)+sz(g)-1);
  rep(i,0,sz(h))h[i]=round(H[i].real());
  return h;
}