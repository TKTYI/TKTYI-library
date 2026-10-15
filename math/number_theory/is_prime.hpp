// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/is_prime.hpp
ll pow_mod(ll _a,ll b,ll m){
    __int128 res=1,a=_a%m;
    while(b){
        if(b%2)res=res*a%m;
        a=a*a%m;b/=2;
    }
    return res;
}
bool is_prime(ll N){
    if(N==1)return false;
    if(N==2)return true;
    if(N%2==0)return false;
    ll s=0,d=N-1;
    while(d%2==0)d/=2,s++;
    vector<long long>A={2,325,9375,28178,450775,9780504,1795265022};
    for(auto a:A){
        long long g=__gcd(a,N);
        if(g>1){
            if(g!=N)return false;
            continue;
        }
        __int128 x=pow_mod(a,d,N);
        if(x!=1&&x!=N-1){
            bool ok=0;
            for(int i=0;i<s-1;i++){
                x=x*x%N;
                if(x==N-1){ok=1;break;}
                if(x==1)break;
            }
            if(!ok)return false;
        }
    }
    return true;
}