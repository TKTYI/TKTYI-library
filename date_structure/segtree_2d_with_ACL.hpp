template<class S,S(*op)(S,S),S(*e)()>
struct segtree_2d_with_ACL{
    private:
    size_t H,W;
    vector<segtree<S,op,e>>seg;
    public:
    segtree_2d_with_ACL(size_t _H,size_t _W){init(_H,_W);}
    void init(size_t _H,size_t _W){
        H=W=1;
        while(H<_H)H<<=1;
        while(W<_W)W<<=1;
        seg.assign(2*H,segtree<S,op,e>(W));
    }
    void set(int h,int w,S x){
        assert(0<=h&&h<H&&0<=w&&w<W);
        h+=H;
        seg[h].set(w,x);
        while(h>1){
            x=op(x,seg[h^1].get(w));
            h>>=1;
            seg[h].set(w,x);
        }
    }
    S get(int h,int w){
        assert(0<=h&&h<H&&0<=w&&w<W);
        return seg[h+H].get(w);
    }
    S prod(int h1,int h2,int w1,int w2){
        assert(0<=h1&&h1<=h2&&h2<=H&&0<=w1&&w1<=w2&&w2<=W);
        h1+=H;h2+=H;
        S res=e();
        while(h1<h2){
            if(h1&1)res=op(res,seg[h1].prod(w1,w2)),h1++;
            if(h2&1)h2--,res=op(res,seg[h2].prod(w1,w2));
            h1>>=1;
            h2>>=1;
        }
        return res;
    }
};
