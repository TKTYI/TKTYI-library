// https://github.com/TKTYI/TKTYI-library/blob/main/date_structure/segtree_2d_sparse.hpp
template<typename T,typename F>
struct segtree_2d_sparse{
    private:
    size_t H,W;
    vector<vector<int>>memo,idx;
    vector<T>seg;
    int id(int&h,int&w){
        int t=lower_bound(memo[h].begin(),memo[h].end(),w)-memo[h].begin();
        if(t==memo[h].size()||memo[h][t]!=w)return -1;
        return idx[h][t];
    }
    T val(int h,int w){
        int i=id(h,w);
        if(i==-1)return I;
        return seg[i];
    }
    void update(int h,int w,T x){
        int i=id(h,w);
        if(i!=-1)seg[i]=x;
    }
    public:
    const F f;
    const T I;
    vector<pair<int,int>>query;
    segtree_2d_sparse(size_t _H,size_t _W,F _f,const T&_I,vector<pair<int,int>>_query):f(_f),I(_I),query(_query){init(_H,_W);}
    void init(size_t _H,size_t _W){
        H=W=1;
        while(H<_H)H<<=1;
        while(W<_W)W<<=1;
        memo.resize(2*H);
        idx.resize(2*H);
        for(auto[_h,_w]:query){
            assert(0<=_h&&_h<H&&0<=_w&&_w<W);
            int h=H+_h,w=W+_w;
            memo[h].emplace_back(w);
            for(int i=h>>1;i;i>>=1)memo[i].emplace_back(w);
            for(;h;h>>=1)for(int j=w>>1;j;j>>=1)memo[h].emplace_back(j);
        }
        int c=0;
        for(int i=0;i<2*H;i++){
            sort(memo[i].begin(),memo[i].end());
            memo[i].erase(unique(memo[i].begin(),memo[i].end()),memo[i].end());
            for(int j=0;j<memo[i].size();j++)idx[i].emplace_back(c++);
        }
        seg.assign(c,I);
    }
    T get(int h,int w){
        return val(h+H,w+W);
    }
    void set(int h,int w,const T&x){
        h+=H;w+=W;
        update(h,w,x);
        for(int i=h>>1;i;i>>=1)update(i,w,f(val(2*i,w),val(2*i+1,w)));
        for(;h;h>>=1)for(int j=w>>1;j;j>>=1)update(h,j,f(val(h,2*j),val(h,2*j+1)));
    }
    T h_prod(int&h,int w1,int w2){
        T res=I;
        for(;w1<w2;w1>>=1,w2>>=1){
            if(w1&1)res=f(res,val(h,w1)),w1++;
            if(w2&1)--w2,res=f(res,val(h,w2));
        }
        return res;
    }
    T prod(int h1,int w1,int h2,int w2){
        assert(0<=h1&&h1<=h2&&h2<=H&&0<=w1&&w1<=w2&&w2<=W);
        if(h1==h2||w1==w2)return I;
        T res=I;
        h1+=H,h2+=H,w1+=W,w2+=W;
        for(;h1<h2;h1>>=1,h2>>=1){
            if(h1&1)res=f(res,h_prod(h1,w1,w2)),h1++;
            if(h2&1)--h2,res=f(res,h_prod(h2,w1,w2));
        }
        return res;
    }
};