// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/sqrt_mod.hpp
int sqrt_mod(int a,int p){
    a%=p;
    if(a<0)a+=p;
    if(p==2)return a;
    if(pow_mod(a,(p-1)/2,p)==p-1)return -1;
    int b=rand()%p;
    while(pow_mod(1ll*b*b-a,(p-1)/2,p)==1)b=rand()%p;
    int c=(1ll*b*b-a+p)%p;
    if(c==0)return b;
    int x=1,y=0,n=(p+1)/2,s=b,t=1;
    while(n){
        if(n&1)tie(x,y)=make_pair((1ll*x*s+1ll*y*t%p*c)%p,(1ll*x*t+1ll*y*s)%p);
        tie(s,t)=make_pair((1ll*s*s+1ll*t*t%p*c)%p,2ll*s*t%p);
        n>>=1;
    }
    assert(y==0);
    assert(1ll*x*x%p==a%p);
    return x;
}