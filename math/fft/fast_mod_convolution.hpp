vl fast_mod_convolution(vl&a,vl&b,ll mod){
  const ll m1=167772161,m2=469762049,m3=1224736769;
  const ll m1_inv_m2=inv_mod(m1,m2);
  const ll m12_inv_m3=inv_mod(m1*m2,m3);
  const ll m12_mod=m1*m2%mod;
  auto x=convolution<m1>(a,b);
  auto y=convolution<m2>(a,b);
  auto z=convolution<m3>(a,b);
  vl ret(sz(a)+sz(b)-1);
  rep(i,0,sz(ret)){
    ll v1=(y[i]-x[i])*m1_inv_m2%m2;if(v1<0)v1+=m2;
    ll v2=(z[i]-(x[i]+m1*v1)%m3)*m12_inv_m3%m3;if(v2<0)v2+=m3;
  	ret[i]=(x[i]+m1*v1+m12_mod*v2)%mod;
  }
  return ret;
}