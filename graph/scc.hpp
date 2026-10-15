vector<vector<int>>scc(vector<vector<int>>E){
    int N=E.size();
    vector<bool>seen(N);
    vector<int>ord;
    function<void(int)>dfs=[&](int v){
        seen[v]=1;
        for(int u:E[v])if(!seen[u])dfs(u);
        ord.emplace_back(v);
    };
    for(int i=0;i<N;i++)if(!seen[i])dfs(i);
    vector<vector<int>>rev(N);
    for(int i=0;i<N;i++)for(int j:E[i])rev[j].emplace_back(i);
    vector<vector<int>>scc;
    for(int i=N-1;i>=0;i--)if(seen[ord[i]]){
        vector<int>comp;
        function<void(int)>revdfs=[&](int v){
            comp.emplace_back(v);
            seen[v]=0;
            for(int u:rev[v])if(seen[u])revdfs(u);
        };
        revdfs(ord[i]);
        scc.emplace_back(comp);
    }
    return scc;
}