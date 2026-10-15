template<class S,S(*op)(S,S),S(*e)()>
struct segtree_dynamic{
    long long min,max;
    S val;
    segtree_dynamic*l=nullptr,*r=nullptr;
    segtree_dynamic(long long N):min(0),max(N),val(e()){}
    segtree_dynamic(long long a,long long b):min(a),max(b),val(e()){}
    void set(long long i,S x){
      if(i<min||max<=i)return;
        if(max-min==1){
            val=x;
            return;
        }
        long long mid=(min+max)/2;
        if(i<mid){
            if(l==nullptr)l=new segtree_dynamic(min,mid);
            l->set(i,x);
        }
        else{
            if(r==nullptr)r=new segtree_dynamic(mid,max);
            r->set(i,x);
        }
        val=op(l==nullptr?e():l->val,r==nullptr?e():r->val);
    }
    S prod(long long a,long long b){
        if(b<=min||max<=a)return e();
        if(a<=min&&max<=b)return val;
        return op(l==nullptr?e():l->prod(a,b),r==nullptr?e():r->prod(a,b));
    }
};