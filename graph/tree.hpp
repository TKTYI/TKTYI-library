// https://github.com/TKTYI/TKTYI-library/blob/main/graph/tree.hpp
template<typename T=int>
struct tree{
    private:
    size_t N,M;
    int r;
    vector<vector<pair<int,T>>>edges;
    vector<vector<int>>doubling;
    vector<int>parent,depth,visit,discovery,finishing;
    vector<T>dist;
    public:
    tree(size_t _N,int _r=0):N(_N),M(0),r(_r),edges(_N),parent(_N),depth(_N),visit(_N),discovery(_N),finishing(_N),dist(_N){}
    void add_edge(int u,int v,T w=1){
        assert(0<=u&&u<N&&0<=v&&v<N&&u!=v);
        M++;
        edges[u].emplace_back(make_pair(v,w));
        edges[v].emplace_back(make_pair(u,w));
    }
    void init(){
        assert(M==N-1);
        vector<int>idx(N);
        vector<bool>seen(N);
        stack<int>st;
        parent.resize(N);
        discovery.resize(N);
        depth.resize(N);
        st.emplace(r);
        while(st.size()){
            int v=st.top();
            visit.emplace_back(v);
            if(!seen[v]){
                discovery[v]=visit.size()-1;
                seen[v]=1;
            }
            while(idx[v]<edges[v].size()&&seen[edges[v][idx[v]].first])idx[v]++;
            if(idx[v]==edges[v].size()){
                finishing[v]=visit.size();
                st.pop();
            }
            else{
                int u=edges[v][idx[v]].first;
                st.emplace(u);
                parent[u]=v;
                depth[u]=depth[v]+1;
                dist[u]=dist[v]+edges[v][idx[v]].second;
            }
        }
        doubling.assign(30,vector<int>(N));
        doubling[0]=parent;
        for(int i=1;i<30;i++){
            for(int v=0;v<N;v++){
                doubling[i][v]=doubling[i-1][doubling[i-1][v]];
            }
        }
    }
    int up(int v,int d){
        if(depth[v]<=d)return r;
        for(int i=0;i<30;i++)if((d>>i)&1)v=doubling[i][v];
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
    T distance(int u,int v){
        return dist[u]+dist[v]-2*dist[lca(u,v)];
    }
};
