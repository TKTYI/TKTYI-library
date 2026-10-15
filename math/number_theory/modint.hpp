template<const long long int mod=998244353>
struct modint{
    using mint=modint<mod>;
    long long int x;
    modint(long long int _x=0):x(_x%mod){if(x<0)x+=mod;}
    long long int val(){return x;}
    mint&operator=(const mint&a){x=a.x;return *this;}
    mint&operator+=(const mint&a){x+=a.x;if(x>=mod)x-=mod;return *this;}
    mint&operator-=(const mint&a){x-=a.x;if(x<0)x+=mod;return *this;}
    mint&operator*=(const mint&a){x*=a.x;x%=mod;return *this;}
    friend mint operator+(const mint&a,const mint&b){return mint(a)+=b;}
    friend mint operator-(const mint&a,const mint&b){return mint(a)-=b;}
    friend mint operator*(const mint&a,const mint&b){return mint(a)*=b;}
    mint operator-()const{return mint(0)-*this;}
    mint pow(long long int n){
        if(!n)return 1;
        mint a=1;
        mint _x=x;
        while(n){
            if(n&1)a*=_x;
            _x=_x*_x;n>>=1;
        }
        return a;
    }
    mint inv(){return pow(mod-2);}
    mint&operator/=(const mint&a){auto _a=a;return *this*=_a.inv();}
    friend mint operator/(const mint&a,mint b){return mint(a)/=b;}
};
using mint=modint<998244353>;