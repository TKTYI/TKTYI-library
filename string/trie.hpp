struct trie{
    vector<int>parent,position;
    vector<map<char,int>>children;
    trie():parent({-1}),children(1){}
    void add_string(string S){
        int v=0;
        for(char c:S){
            auto it=children[v].find(c);
            int nv;
            if(it==children[v].end()){
                nv=parent.size();
                children[v][c]=nv;
                children.emplace_back(map<char,int>());
                parent.emplace_back(v);
            }
            else nv=(*it).second;
            v=nv;
        }
        position.emplace_back(v);
    }
};