template<class S,S(*op)(S,S),S(*e)(),class T,S(*mapping)(T,S),T(*composition)(T,T),T(*id)()>
struct lazy_segtree{
    private:
    int N,h;
    vector<S>seg;
    vector<T>laz;
    void update(int k){seg[k]=op(seg[2*k],seg[2*k+1]);}
    void all_apply(int k,T f){
        seg[k]=mapping(f,seg[k]);
        if(k<N)laz[k]=composition(f,laz[k]);
    }
    void push(int k){
        all_apply(2*k,laz[k]);
        all_apply(2*k+1,laz[k]);
        laz[k]=id();
    }
    public:
    lazy_segtree(int _N){init(_N);}
    void init(int _N){
        N=1,h=0;
        while(N<_N)N<<=1,h++;
        seg.assign(2*N,e());
        laz.assign(2*N,id());
    }
    void set(int i,S x){
        assert(0<=i&&i<N);
        i+=N;
        for(int k=h;k>0;k--)push(i>>k);
        seg[i]=x;
        for(int v=i>>1;v;v>>=1)update(v);
    }
    S get(int i){
        assert(0<=i&&i<N);
        i+=N;
        for(int k=h;k>0;k--)push(i>>k);
        for(int v=i>>1;v;v>>=1)update(v);
        return seg[i];
    }
    S prod(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        if(l==r)return e();
        l+=N;r+=N;
        for(int k=h;k>0;k--)push(l>>k);
        for(int v=l>>1;v;v>>=1)update(v);
        for(int k=h;k>0;k--)push((r-1)>>k);
        for(int v=(r-1)>>1;v;v>>=1)update(v);
        S L=e(),R=e();
        while(l<r){
            if(l&1)L=op(L,seg[l]),l++;
            if(r&1)r--,R=op(seg[r],R);
            l>>=1;
            r>>=1;
        }
        return op(L,R);
    }
    void apply(int l,int r,T f){
        assert(0<=l&&l<=r&&r<=N);
        if(l==r)return;
        l+=N;r+=N;
        for(int k=h;k>0;k--)push(l>>k);
        for(int v=l>>1;v;v>>=1)update(v);
        for(int k=h;k>0;k--)push((r-1)>>k);
        for(int v=(r-1)>>1;v;v>>=1)update(v);
        int _l=l,_r=r;
        while(l<r){
            if(l&1)all_apply(l++,f);
            if(r&1)all_apply(--r,f);
            l>>=1;
            r>>=1;
        }
        l=_l;r=_r;
        for(int k=h;k>0;k--)push(l>>k);
        for(int v=l>>1;v;v>>=1)update(v);
        for(int k=h;k>0;k--)push((r-1)>>k);
        for(int v=(r-1)>>1;v;v>>=1)update(v);
    }
};