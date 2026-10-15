// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/log_mod.hpp
ll log_mod(ll a,ll b,ll m){
    assert(m>0);
    a%=m;b%=m;
    if(a<0)a+=m;
    if(b<0)b+=m;
    assert(__gcd(a,m)==1&&__gcd(b,m)==1);
    if(m==1||b==1)return 0;
    ll bs=sqrtl(m)+1;
    map<ll,ll>memo1,memo2;
    ll s=1;
    for(ll i=0;i<bs;i++){
        if(memo1.find(s)==memo1.end())memo1[s]=i;
        s=s*a%m;
    }
    ll t=1;
    for(ll i=0;i<bs;i++){
        if(memo2.find(t)==memo2.end())memo2[t]=i;
        t=t*s%m;
    }
    ll res=1e18;
    for(auto[k,v]:memo1){
        ll t=b*inv_mod(k,m)%m;
        if(memo2.find(t)==memo2.end())continue;
        res=min(res,v+bs*memo2[t]); 
    }
    if(res>1e17)res=-1;
    return res;
}