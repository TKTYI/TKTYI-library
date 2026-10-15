// https://github.com/TKTYI/TKTYI-library/blob/main/date_structure/segtree.hpp
template<class S,S(*op)(S,S),S(*e)()>
struct segtree{
    private:
    size_t N;
    vector<S>seg;
    public:
    segtree(int _N){init(_N);}
    void init(int _N){
        N=1;
        while(N<_N)N<<=1;
        seg.assign(2*N,e());
    }
    void set(int i,S x){
        assert(0<=i&&i<N);
        i+=N;
        seg[i]=x;
        while(i>1){
            i>>=1;
            seg[i]=op(seg[2*i],seg[2*i+1]);
        }
    }
    S get(int i){
        assert(0<=i&&i<N);
        return seg[i+N];
    }
    S prod(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        l+=N;r+=N;
        S L=e(),R=e();
        while(l<r){
            if(l&1)L=op(L,seg[l]),l++;
            if(r&1)r--,R=op(seg[r],R);
            l>>=1;
            r>>=1;
        }
        return op(L,R);
    }
};