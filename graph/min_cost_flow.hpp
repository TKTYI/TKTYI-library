// greedy O(F(N+M))
template<typename T1,typename T2>
struct min_cost_flow{
    struct edge{
        int from,to;
        T1 cap,flow;
        T2 cost;
    };
    int N;
    vector<edge>es;
    min_cost_flow(int _N):N(_N){}
    void add_edge(int from,int to,T1 cap,T2 cost){
        es.emplace_back(edge{from,to,cap,0,cost});
    }
    T2 flow(int s,int t,T1 F){
        assert(s!=t);
        vector<vector<int>>E(N);
        for(int i=0;i<es.size();i++){
            E[es[i].from].emplace_back(i);
            E[es[i].to].emplace_back(-1-i);
        }
        T2 total_cost=0;
        while(F){
            vector<T2>D(N,numeric_limits<T2>::max());
            vector<int>pre(N);
            D[s]=0;
            priority_queue<pair<T2,int>,vector<pair<T2,int>>,greater<pair<T2,int>>>Q;
            Q.emplace(make_pair(0,s));
            while(!Q.empty()){
                T2 c=Q.top().first;
                int v=Q.top().second;
                Q.pop();
                if(c!=D[v])continue;
                for(int i:E[v]){
                    if(i>=0){
                        if(es[i].flow<es[i].cap&&D[es[i].to]>c+es[i].cost){
                            D[es[i].to]=c+es[i].cost;
                            pre[es[i].to]=i;
                            Q.emplace(make_pair(D[es[i].to],es[i].to));
                        }
                    }
                    else if(es[-1-i].flow&&D[es[-1-i].from]>c-es[-1-i].cost){
                        D[es[-1-i].from]=c-es[-1-i].cost;
                        pre[es[-1-i].from]=i;
                        Q.emplace(make_pair(D[es[-1-i].from],es[-1-i].from));
                    }
                }
            }
            if(D[t]==numeric_limits<T2>::max())break;
            int v=t;
            T1 f=F;
            while(v!=s){
                int i=pre[v];
                if(i>=0)f=min(f,es[i].cap-es[i].flow),v=es[i].from;
                else f=min(f,es[-1-i].flow),v=es[-1-i].to;
            }
            F-=f;
            v=t;
            total_cost+=D[t]*f;
            while(v!=s){
                int i=pre[v];
                if(i>=0)es[i].flow+=f,v=es[i].from;
                else es[-1-i].flow-=f,v=es[-1-i].to;
            }
        }
        if(F)return -1;
        return total_cost;
    }
};