// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/Pell.hpp
__int128 mysq(__int128 N){
  __int128 n=sqrtl(N);
  while(n*n>N)n--;
  while((n+1)*(n+1)<=N)n++;
  return n;
};
pair<__int128,__int128>Pell(__int128 D){
  __int128 a=-mysq(D),b=1,c=1;
  vector<__int128>A={-a};
  while(A.back()!=2*A[0]){
    auto x=a*c,y=-b*c,z=a*a-D*b*b;
    if(z<0)x=-x,y=-y,z=-z;
    auto w=x-mysq(y*y*D)-1;
    if(y>0)w=x+mysq(y*y*D);
    assert(w>=0);
    A.emplace_back(w/z);
    x-=A.back()*z;
    a=x;b=y;c=z;
    auto g=__gcd(__gcd(a,b),c);
    a/=g;b/=g;c/=g;
  }
  ll r=sz(A)-1;
  A.insert(A.end(),A.begin()+1,A.end());
  if(r%2==0)r--;
  else r=2*r-1;
  __int128 x=1,y=0;
  rrep(_,0,r+1){
    swap(x,y);
    x+=y*A[_];
  }
  return make_pair(x,y);
}