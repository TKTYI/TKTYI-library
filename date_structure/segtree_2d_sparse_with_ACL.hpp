template<class S,auto op,auto e>
struct segtree_2d_sparse_with_ACL{
    private:
    size_t H,W;
    vector<segtree<S,op,e>>seg;
    vector<vector<int>>E,LL,RR,PP;
    int id(int h,int w){
        if(!binary_search(E[h].begin(),E[h].end(),w))return -1;
        return lower_bound(E[h].begin(),E[h].end(),w)-E[h].begin();
    }
    public:
    segtree_2d_sparse_with_ACL(size_t _H,size_t _W,vector<pair<int,int>>query){init(_H,_W,query);}
    void init(size_t _H,size_t _W,vector<pair<int,int>>query){
        H=W=1;
        while(H<_H)H<<=1;
        while(W<_W)W<<=1;
        E.resize(2*H);
        LL.resize(H);
        RR.resize(H);
        PP.resize(2*H);
        seg.resize(2*H);
        for(auto[h,w]:query){
            assert(0<=h&&h<H&&0<=w&&w<W);
            E[h+H].emplace_back(w);
        }
        for(int i=2*H-1;i;i--){
            sort(E[i].begin(),E[i].end());
            E[i].erase(unique(E[i].begin(),E[i].end()),E[i].end());
            seg[i]=segtree<S,op,e>(E[i].size());
            if(i)E[i>>1].insert(E[i>>1].end(),E[i].begin(),E[i].end());
            PP[i].resize(E[i].size()+1);
            if(i>=H)continue;
            LL[i].resize(E[i].size()+1);
            RR[i].resize(E[i].size()+1);
            int t1=0,t2=0;
            for(int j=0;j<E[i].size();j++){
              while(t1<E[2*i].size()&&E[2*i][t1]<E[i][j])t1++;
              while(t2<E[2*i+1].size()&&E[2*i+1][t2]<E[i][j])t2++;
              LL[i][j]=t1;RR[i][j]=t2;
              if(t1<E[2*i].size()&&E[2*i][t1]==E[i][j])PP[2*i][t1]=j;
              if(t2<E[2*i+1].size()&&E[2*i+1][t2]==E[i][j])PP[2*i+1][t2]=j;
            }
            LL[i][E[i].size()]=E[2*i].size();
            RR[i][E[i].size()]=E[2*i+1].size();
            PP[2*i][E[2*i].size()]=PP[2*i+1][E[2*i+1].size()]=E[i].size();
        }
    }
    void set(int h,int w,S x){
        assert(0<=h&&h<H&&0<=w&&w<W);
        h+=H;
        assert(id(h,w)!=-1);
        int i=id(h,w);
        seg[h].set(i,x);
        while(h>1){
            int j=PP[h][i];
            if(h&1){
                if(LL[h>>1][j]<E[h^1].size()&&E[h^1][LL[h>>1][j]]==w)x=op(x,seg[h^1].get(LL[h>>1][j]));
            }
            else{
                if(RR[h>>1][j]<E[h^1].size()&&E[h^1][RR[h>>1][j]]==w)x=op(x,seg[h^1].get(RR[h>>1][j]));
            }
            i=j;h>>=1;
            seg[h].set(i,x);
        }
    }
    S get(int h,int w){
        assert(0<=h&&h<H&&0<=w&&w<W);
        h+=H;
        if(id(h,w)==-1)return e();
        return seg[h].get(id(h,w));
    }
    S prod(int h1,int h2,int lid,int rid,int v,int l,int r){
      if(h1>=r||h2<=l)return e();
      if(h1<=l&&r<=h2)return seg[v].prod(lid,rid);
      return op(prod(h1,h2,LL[v][lid],LL[v][rid],2*v,l,(l+r)/2),prod(h1,h2,RR[v][lid],RR[v][rid],2*v+1,(l+r)/2,r));
    }
    S prod(int h1,int h2,int w1,int w2){
        assert(0<=h1&&h1<=h2&&h2<=H&&0<=w1&&w1<=w2&&w2<=W);
        return prod(h1,h2,lower_bound(E[1].begin(),E[1].end(),w1)-E[1].begin(),lower_bound(E[1].begin(),E[1].end(),w2)-E[1].begin(),1,0,H);
    }
};