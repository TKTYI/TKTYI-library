template<typename T=long long>
struct fenwick_tree_on_tree{
    private:
    struct fenwick_tree{
        private:
        vector<T>tree;
        T sum_from_zero(int i){
            i++;
            T s=0;
            while(i){
                s+=tree[i];
                i-=i&-i;
            }
            return s;
        }
        public:
        fenwick_tree(size_t N):tree(vector<T>(N+1)){}
        T sum(int l,int r){
            assert(0<=l&&l<=r&&r<=tree.size());
            return sum_from_zero(r-1)-sum_from_zero(l-1);
        }
        T get(int i){
            assert(0<=i&&i<tree.size());
            return sum(i,i+1);
        }
        void add(int i,T x){
            assert(0<=i&&i<tree.size());
            i++;
            while(i<tree.size()){
                tree[i]+=x;
                i+=i&-i;
            }
        }
    };
    size_t N,M;
    vector<vector<int>>edges,doubling;
    vector<int>euler,first,last,depth;
    fenwick_tree_on_tree::fenwick_tree tree;
    public:
    fenwick_tree_on_tree(size_t _N):N(_N),M(0),edges(_N),euler(0),first(_N),last(_N),depth(_N),tree(2*_N-1){
      int h=0;
      while((1<<h)<N)h++;
      doubling.assign(h+1,vector<int>(N));
    }
    void add_edge(int u,int v){
        assert(0<=u&&u<N&&0<=v&&v<N&&u!=v);
        M++;
        edges[u].emplace_back(v);
        edges[v].emplace_back(u);
    }
    void init(){
        assert(M==N-1);
        function<void(int)>dfs=[&](int v){
            first[v]=euler.size();
            euler.emplace_back(v);
            for(int u:edges[v])if(u!=doubling[0][v]){
                depth[u]=depth[v]+1;
                doubling[0][u]=v;
                dfs(u);
                euler.emplace_back(v);
            }
            last[v]=euler.size()-1;
        };
        dfs(0);
        for(int i=1;i<doubling.size();i++)for(int v=0;v<N;v++)doubling[i][v]=doubling[i-1][doubling[i-1][v]];
    }
    void add(int v,T x){
        assert(0<=v&&v<N);
        tree.add(first[v],x);
        tree.add(last[v]+1,-x);
    }
    T sum_from_zero(int v){
        assert(0<=v&&v<N);
        return tree.sum(0,first[v]+1);
    }
    int up(int v,int d){
        if(depth[v]<=d)return 0;
        for(int i=0;i<doubling.size();i++)if((d>>i)&1)v=doubling[i][v];
        return v;
    }
    int lca(int u,int v){
        if(depth[u]>depth[v])swap(u,v);
        v=up(v,depth[v]-depth[u]);
        int l=-1,r=depth[u];
        while(r-l>1){
            int m=(l+r)/2;
            if(up(u,m)==up(v,m))r=m;
            else l=m;
        }
        return up(v,r);
    }
    T sum(int u,int v){
        int w=lca(u,v);
        T ret=sum_from_zero(u)+sum_from_zero(v)-sum_from_zero(w);
        if(w)ret-=sum_from_zero(doubling[0][w]);
        return ret;
    }
};