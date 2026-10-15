// https://github.com/TKTYI/TKTYI-library/blob/main/graph/edge_coloring_of_bipartite_graph.hpp
// depend on dsu
vector<int>edge_coloring_of_bipartite_graph(int L,int R,vector<pair<int,int>>E){
    vector<int>ldeg(L),rdeg(R);
    for(auto[a,b]:E)ldeg[a]++,rdeg[b]++;
    int K=max(*max_element(ldeg.begin(),ldeg.end()),*max_element(rdeg.begin(),rdeg.end()));
    using pii=pair<int,int>;
    priority_queue<pii,vector<pii>,greater<pii>>pq;
    {
        dsu D(L);
        for(int i=0;i<L;i++)pq.emplace(pii(ldeg[i],i));
        while(pq.size()>1){
            auto[d1,v1]=pq.top();pq.pop();
            auto[d2,v2]=pq.top();pq.pop();
            if(d1+d2>K)break;
            int v=D.merge(v1,v2);
            ldeg[v]=d1+d2;
            pq.emplace(pii(d1+d2,v));
        }
        while(!pq.empty())pq.pop();
        auto gr=D.groups();
        vector<int>_ldeg(gr.size()),idx(L);
        for(int i=0;i<gr.size();i++){
            for(int v:gr[i])idx[v]=i;
            _ldeg[i]=ldeg[D.leader(gr[i][0])];
        }
        for(auto&[a,b]:E)a=idx[a];
        ldeg=_ldeg;
    }
    {
        dsu D(R);
        for(int i=0;i<R;i++)pq.emplace(pii(rdeg[i],i));
        while(pq.size()>1){
            auto[d1,v1]=pq.top();pq.pop();
            auto[d2,v2]=pq.top();pq.pop();
            if(d1+d2>K)break;
            int v=D.merge(v1,v2);
            rdeg[v]=d1+d2;
            pq.emplace(pii(d1+d2,v));
        }
        auto gr=D.groups();
        vector<int>_rdeg(gr.size()),idx(R);
        for(int i=0;i<gr.size();i++){
            for(int v:gr[i])idx[v]=i;
            _rdeg[i]=rdeg[D.leader(gr[i][0])];
        }
        for(auto&[a,b]:E)b=idx[b];
        rdeg=_rdeg;
    }
    L=ldeg.size();
    R=rdeg.size();
    int M=E.size();
    for(int i=0,v=0;i<L;i++)while(ldeg[i]<K){
        while(v<R&&rdeg[v]==K)v++;
        if(R==v)rdeg.emplace_back(0),R++;
        E.emplace_back(pii(i,v));
        ldeg[i]++;rdeg[v]++;
    }
    for(int i=0,v=L;i<R;i++)while(rdeg[i]<K){
        while(v<L&&ldeg[v]==K)v++;
        if(L==v)ldeg.emplace_back(0),L++;
        E.emplace_back(pii(v,i));
        ldeg[v]++;rdeg[i]++;
    }
    assert(L==R);
    vector<int>ans(E.size());
    function<void(vector<int>,int,int)>dfs=[&](vector<int>es,int a,int b){
        if(b-a==1){for(int i:es)ans[i]=a;return;}
        if((b-a)%2){
            int t=0,M=es.size();
            while((1<<t)<es.size())t++;
            map<pii,int>memo,neno;
            for(auto e:es)memo[E[e]]+=(1<<t)/(b-a);
            int W=(1<<t)%(b-a);
            for(int i=0;i<L;i++)neno[pii(i,i)]+=W;
            while(t){
                map<pii,int>memo1,memo2,neno1,neno2;
                vector<vector<pii>>LE(L),RE(R);
                vector<bool>used;
                for(auto[k,w]:memo){
                    if(w>1){
                        memo1[k]+=w/2;
                        memo2[k]+=w/2;
                    }
                    if(w%2){
                        auto[u,v]=k;
                        LE[u].emplace_back(pii(v,used.size()));
                        RE[v].emplace_back(pii(u,used.size()));
                        used.emplace_back(0);
                    }
                }
                int M=used.size();
                for(auto[k,w]:neno){
                    if(w>1){
                        neno1[k]+=w/2;
                        neno2[k]+=w/2;
                    }
                    if(w%2){
                        auto[u,v]=k;
                        LE[u].emplace_back(pii(v,used.size()));
                        RE[v].emplace_back(pii(u,used.size()));
                        used.emplace_back(0);
                    }
                }
                vector<int>LI(L),RI(R);
                long long cnt1=0,cnt2=0;
                for(int i=0;i<L;i++)while(1){
                    while(LI[i]<LE[i].size()&&used[LE[i][LI[i]].second])LI[i]++;
                    if(LI[i]==LE[i].size())break;
                    int v=i;
                    do{
                        while(used[LE[v][LI[v]].second])LI[v]++;
                        auto[u,idx]=LE[v][LI[v]++];
                        used[idx]=1;
                        (idx<M?memo1:neno1)[pii(v,u)]++;
                        if(idx>=M)cnt1++;
                        while(used[RE[u][RI[u]].second])RI[u]++;
                        tie(v,idx)=RE[u][RI[u]++];
                        used[idx]=1;
                        (idx<M?memo2:neno2)[pii(v,u)]++;
                        if(idx>=M)cnt2++;
                    }while(v!=i);
                }
                if(cnt1>cnt2)memo=memo2,neno=neno2;
                else memo=memo1,neno=neno1;
                t--;
            }
            assert(neno.empty());
            vector<int>_es;
            for(auto i:es){
                if(memo[E[i]])memo[E[i]]--,ans[i]=a;
                else _es.emplace_back(i);
            }
            es=_es;
            a++;
        }
        vector<vector<pii>>LE(L),RE(R);
        vector<int>LI(L),RI(R);
        vector<bool>used(es.size());
        for(int i=0;i<es.size();i++){
            auto[u,v]=E[es[i]];
            LE[u].emplace_back(pii(v,i));
            RE[v].emplace_back(pii(u,i));
        }
        vector<int>es1,es2;
        for(int i=0;i<L;i++)while(1){
            while(LI[i]<LE[i].size()&&used[LE[i][LI[i]].second])LI[i]++;
            if(LI[i]==LE[i].size())break;
            int v=i;
            do{
                while(used[LE[v][LI[v]].second])LI[v]++;
                auto[u,idx]=LE[v][LI[v]++];
                used[idx]=1;
                es1.emplace_back(es[idx]);
                while(used[RE[u][RI[u]].second])RI[u]++;
                tie(v,idx)=RE[u][RI[u]++];
                used[idx]=1;
                es2.emplace_back(es[idx]);
            }while(v!=i);
        }
        dfs(es1,(a+b)/2,b);
        int t=0;
        while((1<<t)<(b-a)/2)t++;
        es=es2;
        for(int i:es1)if(ans[i]<a+(1<<t))es.emplace_back(i);
        b=a+(1<<t);
        queue<pair<vector<int>,pii>>que;
        que.emplace(make_pair(es,pii(a,b)));
        used=vector<bool>(E.size());
        while(!que.empty()){
            auto[es,p]=que.front();que.pop();
            auto[a,b]=p;
            if(b-a==1){
                for(auto i:es)ans[i]=a;
                continue;
            }
            vector<vector<pii>>LE(L),RE(R);
            vector<int>LI(L),RI(R);
            for(int i:es){
                auto[u,v]=E[i];
                LE[u].emplace_back(pii(v,i));
                RE[v].emplace_back(pii(u,i));
                used[i]=0;
            }
            vector<int>es1,es2;
            for(int i=0;i<L;i++)while(1){
                while(LI[i]<LE[i].size()&&used[LE[i][LI[i]].second])LI[i]++;
                if(LI[i]==LE[i].size())break;
                int v=i;
                do{
                    while(used[LE[v][LI[v]].second])LI[v]++;
                    auto[u,idx]=LE[v][LI[v]++];
                    used[idx]=1;
                    es1.emplace_back(idx);
                    while(used[RE[u][RI[u]].second])RI[u]++;
                    tie(v,idx)=RE[u][RI[u]++];
                    used[idx]=1;
                    es2.emplace_back(idx);
                }while(v!=i);
            }
            que.emplace(make_pair(es1,pii(a,(a+b)/2)));
            que.emplace(make_pair(es2,pii((a+b)/2,b)));
        }
    };
    vector<int>es(E.size());
    iota(es.begin(),es.end(),0);
    dfs(es,0,K);
    ans.resize(M);
    return ans;
}