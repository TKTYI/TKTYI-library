template<typename mint>
mint coeff_of_rational(vector<mint>p,vector<mint>q,long long T){
  assert(sz(q)&&q[0].val());
  while(T){
    vm p0,p1,q0,q1;
    rep(i,0,sz(p))(i%2?p1:p0).emplace_back(p[i]);
    rep(i,0,sz(q))(i%2?q1:q0).emplace_back(q[i]);
    auto X=convolution(q0,q0);
    auto Y=convolution(q1,q1);
    rep(i,0,sz(Y)){
      if(sz(X)==i+1)X.emplace_back(-Y[i]);
      else X[i+1]-=Y[i];
    }
    q=X;
    if(T%2){
      X=convolution(p1,q0);
      Y=convolution(p0,q1);
      rep(i,0,sz(Y)){
        if(i==sz(X))X.emplace_back(-Y[i]);
        else X[i]-=Y[i];
      }
      p=X;
    }
    else{
      X=convolution(p0,q0);
      Y=convolution(p1,q1);
      rep(i,0,sz(Y)){
        if(i+1==sz(X))X.emplace_back(-Y[i]);
        else X[i+1]-=Y[i];
      }
      p=X;
    }
    T/=2;
  }
  return p[0]/q[0];
}