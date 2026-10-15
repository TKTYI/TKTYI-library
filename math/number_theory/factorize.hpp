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
ll div(ll n){
    if(n%2==0)return 2;
    ll d=0;
    while(++d){
        __int128 x=0,y=0;
        while(1){
            x=(x*x+d)%n;
            y=(y*y+d)%n;
            y=(y*y+d)%n;
            ll g=__gcd((ll)(x-y),n);
            if(g==n)break;
            if(g>1)return g;
        }
    }
    return -1;
}
vector<ll>factorize(ll N){
    if(N==1)return {};
    vector<ll>f,c={N};
    while(!c.empty()){
        auto m=c.back();
        c.erase(c.end()-1);
        if(is_prime(m)){
            f.emplace_back(m);
            continue;
        }
        ll d=div(m);
        if(is_prime(m/d))f.emplace_back(m/d);
        else c.emplace_back(m/d);
        if(is_prime(d))f.emplace_back(d); 
        else c.emplace_back(d);
    }
    sort(f.begin(),f.end());
    return f;
}
vector<ll>divisor(ll N){
    vector<ll>F=factorize(N);
    vector<ll>D={1};
    for(int i=0;i<sz(F);i++){
        int j=i;
        while(i<sz(F)&&F[i]==F[j])i++;
        int x=sz(D)*(i-j);
        for(int k=0;k<x;k++)D.emplace_back(D[k]*F[j]);
        i--;
    }
    sort(all(D));
    return D;
}