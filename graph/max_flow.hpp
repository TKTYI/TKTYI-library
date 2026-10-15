// https://github.com/TKTYI/TKTYI-library/blob/main/graph/max_flow.hpp
// Dinic's algorithm O(N^2M)
template<typename T>
struct max_flow{
    struct edge{
        int from,to;
        T cap,flow;
    };
    int N;
    vector<edge>es;
    max_flow(int _N):N(_N){}
    void add_edge(int from,int to,T cap){
        es.emplace_back(edge{from,to,cap,0});
    }
    T flow(int s,int t){
        assert(s!=t);
        T total_flow=0;
        while(1){
            vector<int>level(N,N);
            {
                vector<vector<int>>E(N);
                for(auto e:es){
                    if(e.flow<e.cap)E[e.from].emplace_back(e.to);
                    if(e.flow)E[e.to].emplace_back(e.from);
                }
                level[s]=0;
                queue<int>Q;
                Q.emplace(s);
                while(!Q.empty()){
                    int v=Q.front();Q.pop();
                    for(auto u:E[v])if(level[u]>level[v]+1){
                        level[u]=level[v]+1;
                        Q.emplace(u);
                    }
                }
            }
            if(level[t]==N)return total_flow;
            vector<vector<int>>E(N);
            for(int i=0;i<es.size();i++){
                auto e=es[i];
                if(e.flow<e.cap&&level[e.from]+1==level[e.to])E[e.from].emplace_back(i);
                if(e.flow&&level[e.from]==level[e.to]+1)E[e.to].emplace_back(-i-1);
            }
            vector<int>idx(N);
            iota(idx.begin(),idx.end(),0);
            sort(idx.begin(),idx.end(),[&](int i,int j){return level[i]<level[j];});
            while(1){
                vector<T>dp(N,0);
                vector<int>pre(N);
                dp[s]=numeric_limits<T>::max();
                for(auto v:idx){
                    for(int i:E[v]){
                        if(i>=0){
                            if(dp[es[i].to]<min(dp[v],es[i].cap-es[i].flow)){
                                dp[es[i].to]=min(dp[v],es[i].cap-es[i].flow);
                                pre[es[i].to]=i;
                            }
                        }
                        else if(dp[es[-1-i].from]<min(dp[v],es[-1-i].flow)){
                            dp[es[-1-i].from]=min(dp[v],es[-1-i].flow);
                            pre[es[-1-i].from]=i;
                        }
                    }
                }
                if(!dp[t])break;
                T f=dp[t];
                total_flow+=f;
                int v=t;
                while(v!=s){
                    int i=pre[v];
                    if(i>=0){
                        v=es[i].from;
                        es[i].flow+=f;
                    }
                    else{
                        v=es[-1-i].to;
                        es[-1-i].flow-=f;
                    }
                }
            }
        }
    }
};