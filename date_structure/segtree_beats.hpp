// https://github.com/TKTYI/TKTYI-library/blob/main/date_structure/segtree_beats.hpp
// 誰か整備してくれ
void solve(ll N,ll M,ll K,vl W,vl L,vl R){
    ll S=reduce(all(W));
    ll ans=0,sum=0;
    ll n=1;
    while(n<N)n<<=1;
    vl Xmin(2*n),Xmin2(2*n,1e18),lazy(2*n),A(2*n),AX(2*n),Aminsum(2*n);
    rep(i,0,N)A[i+n]=W[i];
    rrep(i,1,n)A[i]=A[2*i]+A[2*i+1];
    Aminsum=A;
    auto add=[&](ll p,ll v){
        Xmin[p]+=v;
        if(Xmin2[p]!=1e18)Xmin2[p]+=v;
        AX[p]+=A[p]*v;
        lazy[p]+=v;
    };
    auto chmax=[&](ll p,ll v){
        if(Xmin[p]>=v)return;
        AX[p]+=(v-Xmin[p])*Aminsum[p];
        Xmin[p]=v;
    };
    auto pull=[&](int p){
        ll l=2*p,r=2*p+1;
        AX[p]=AX[l]+AX[r];
        Xmin[p]=min(Xmin[l],Xmin[r]);
        Aminsum[p]=(Xmin[p]==Xmin[l]?Aminsum[l]:0)+(Xmin[p]==Xmin[r]?Aminsum[r]:0);
        if(Xmin[l]==Xmin[r])Xmin2[p]=min(Xmin2[l],Xmin2[r]);
        else if(Xmin[l]<Xmin[r])Xmin2[p]=min(Xmin2[l],Xmin[r]);
        else Xmin2[p]=min(Xmin[l],Xmin2[r]);
    };
    auto push=[&](ll p){
        if(lazy[p]){
            add(2*p,lazy[p]);
            add(2*p+1,lazy[p]);
            lazy[p]=0;
        }
        if(Xmin[2*p]<Xmin[p])chmax(2*p,Xmin[p]);
        if(Xmin[2*p+1]<Xmin[p])chmax(2*p+1,Xmin[p]);
    };
    function<void(ll,ll,ll,ll,ll,ll)>range_add=[&](ll p,ll l,ll r,ll ql,ll qr,ll v){
        if(ql<=l&&r<=qr){add(p,v);return;}
        push(p);
        ll m=(l+r)/2;
        if(ql<m)range_add(2*p,l,m,ql,qr,v);
        if(qr>m)range_add(2*p+1,m,r,ql,qr,v);
        pull(p);
    };
    function<void(ll,ll,ll,ll,ll)>range_chmax=[&](ll p,ll l,ll r,ll ql,ll qr){
        if(ql<=l&&r<=qr){
            if(Xmin[p]>=0)return;
            if(Xmin2[p]>0){chmax(p,0);return;}
        }
        push(p);
        ll m=(l+r)/2;
        if(ql<m)range_chmax(2*p,l,m,ql,qr);
        if(qr>m)range_chmax(2*p+1,m,r,ql,qr);
        pull(p);
    };
    rrep(i,0,M){
        ll l=L[i]-1,r=R[i];
        // cout<<i<<" ; "<<AX[1]<<endl;
        if(AX[1]+S<=K){ans++;range_add(1,0,n,0,N,1);}
        range_add(1,0,n,l,r,-1);
        range_chmax(1,0,n,l,r);
    }
    ll ma=0;
    rep(i,1,n)push(i);
    rep(i,0,N)ma=max(ma,Xmin[i+n]);
    cout<<ans-ma<<endl;
}