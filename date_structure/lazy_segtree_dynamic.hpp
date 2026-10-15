// https://github.com/TKTYI/TKTYI-library/blob/main/date_structure/lazy_segtree_dynamic.hpp
struct lazy_segtree_dynamic{
    long long min,max;
    S val;
    F lz;
    lazy_segtree_dynamic*l=nullptr,*r=nullptr;
    lazy_segtree_dynamic(long long N):min(0),max(N),val(e()),lz(id()){}
    lazy_segtree_dynamic(long long a,long long b):min(a),max(b),val(e()),lz(id()){}
    void update(){val=op(l->val,r->val);}
    void all_apply(F f){
        val=mpp(f,val);
        lz=cmpo(f,lz);
    }
    void push(){
        if(l==nullptr)l=new lazy_segtree_dynamic(min,(min+max)/2);
        if(r==nullptr)r=new lazy_segtree_dynamic((min+max)/2,max);
        l->all_apply(lz);
        r->all_apply(lz);
        lz=id();
    }
    void set(long long i,S x){
        assert(min<=i&&i<max);
        if(max-min==1){val=x;return;}
        push();
        if(i<(min+max)/2)l->set(i,x);
        else r->set(i,x);
        update();
    }
    S prod(long long a,long long b){
        if(b<=min||max<=a)return e();
        if(a<=min&&max<=b)return val;
        push();
        if(b<=(min+max)/2)return l->prod(a,b);
        if(a>=(min+max)/2)return r->prod(a,b);
        return op(l->prod(a,b),r->prod(a,b));
    }
    void apply(long long a,long long b,F f){
        if(b<=min||max<=a)return;
        if(a<=min&&max<=b){all_apply(f);return;}
        push();
        if(a<(min+max)/2)l->apply(a,b,f);
        if(b>(min+max)/2)r->apply(a,b,f);
        update();
    }
};