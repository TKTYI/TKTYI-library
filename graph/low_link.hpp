struct low_link{
    private:
    size_t N;
    vector<vector<int>>edges;
    public:
    struct dsu{
        private:
        vector<int>parent;
        public:
        dsu()=default;
        dsu(size_t n):parent(n,-1){}
        int leader(int i){
                if(parent[i]<0)return i;
                return parent[i]<0?i:(parent[i]=leader(parent[i]));
        }
        int merge(int a,int b){
                a=leader(a);
                b=leader(b);
                if (a!=b){
                    if(-parent[a]<-parent[b])swap(a,b);
                    parent[a]+=parent[b];
                    parent[b]=a;
                }
                return a;
        }
        bool same(int a,int b){return leader(a)==leader(b);}
        int size(int i){return -parent[leader(i)];}
        vector<vector<int>>groups(){
            size_t n=parent.size();
            vector<vector<int>>A(n);
            for(int i=0;i<n;i++)A[leader(i)].emplace_back(i);
            vector<vector<int>>res;
            for(auto a:A)if(a.size())res.emplace_back(a);
            return res;
        }
    };
    low_link(int _N):N(_N),edges(N){}
    void add_edge(int u,int v){
        assert(0<=u&&u<N&&0<=v&&v<N);
        edges[u].emplace_back(v);
        edges[v].emplace_back(u);
    }
    pair<vector<int>,vector<vector<int>>>construct(){
        vector<int>parent(N,-1),depth(N);
        for(int i=0;i<N;i++)if(parent[i]==-1){
            parent[i]=i;
            queue<int>Q;
            Q.emplace(i);
            while(Q.size()){
                int v=Q.front();Q.pop();
                for(int u:edges[v])if(parent[u]==-1){
                    parent[u]=v;
                    depth[u]=depth[v]+1;
                    Q.emplace(u);
                }
            }
        }
        vector<vector<int>>doubling(30,vector<int>(N));
        doubling[0]=parent;
        for(int i=1;i<30;i++){
            for(int v=0;v<N;v++){
                doubling[i][v]=doubling[i-1][doubling[i-1][v]];
            }
        }
        auto up=[&](int v,long long d){
            if(d>N)return doubling[29][v];
            for(int i=0;i<30;i++)if((d>>i)&1){
                v=doubling[i][v];
            }
            return v;
        };
        auto lca=[&](int u,int v){
            if(depth[u]>depth[v])swap(u,v);
            v=up(v,depth[v]-depth[u]);
            int l=-1,r=N;
            while(r-l>1){
                int m=(l+r)/2;
                if(up(v,m)==up(u,m))r=m;
                else l=m;
            }
            return up(v,r);
        };
        vector<int>imos(N);
        for(int v=0;v<N;v++){
            imos[parent[v]]+=2;
            imos[v]-=2;
        }
        for(int v=0;v<N;v++)for(int u:edges[v]){
            int w=lca(u,v);
            imos[w]-=2;
            imos[u]++;
            imos[v]++;
        }
        vector<int>cnt(N);
        for(int i=0;i<N;i++)if(i!=parent[i]){
          cnt[parent[i]]++;
        }
        queue<int>Q;
        for(int i=0;i<N;i++)if(!cnt[i]){
            Q.emplace(i);
        }
        while(Q.size()){
            int v=Q.front();Q.pop();
            if(v==parent[v])continue;
            imos[parent[v]]+=imos[v];
            cnt[parent[v]]--;
            if(!cnt[parent[v]])Q.emplace(parent[v]);
        }
        dsu D(N);
        for(int i=0;i<N;i++)if(imos[i]){
            D.merge(i,parent[i]);
        }
        vector<vector<int>>group=D.groups();
        vector<int>idx(N);
        for(int i=0;i<group.size();i++){
            for(int j:group[i])idx[j]=i;
        }
        vector<vector<int>>bridges(group.size());
        for(int i=0;i<N;i++)if(i!=parent[i]&&!imos[i]){
            bridges[idx[i]].emplace_back(idx[parent[i]]);
            bridges[idx[parent[i]]].emplace_back(idx[i]);
        }
        return make_pair(idx,bridges);
    }
};
