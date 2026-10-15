// https://github.com/TKTYI/TKTYI-library/blob/main/string/aho_corasick.hpp
struct aho_corasick{
    vector<int>parent,position,failure,nextNode;
    vector<map<char,int>>children;
    vector<vector<int>>node;
    aho_corasick():parent({-1}),children(1){}
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
    void build(){
        failure.assign(parent.size(),0);
        queue<int>Q;
        for(auto[c,v]:children[0])Q.emplace(v);
        while(!Q.empty()){
            int v=Q.front();
            Q.pop();
            for(auto[c,u]:children[v]){
                Q.emplace(u);
                int fu=failure[v];
                while(fu&&children[fu].find(c)==children[fu].end()){
                    fu=failure[fu];
                }
                auto it=children[fu].find(c);
                if(it==children[fu].end())failure[u]=fu;
                else failure[u]=(*it).second;
            }
        }
        node.assign(parent.size(),vector<int>(0));
        for(int i=0;i<position.size();i++)node[position[i]].emplace_back(i);
        nextNode.assign(parent.size(),0);
        for(int i=1;i<node.size();i++){
            if(node[i].empty())nextNode[i]=nextNode[parent[i]];
            else nextNode[i]=i;
        }
    }
    vector<int>match(string S){
        queue<int>Q;
        int v=0;
        for(char c:S){
            while(v&&children[v].find(c)==children[v].end()){
                Q.emplace(v);
                v=failure[v];
            }
            auto it=children[v].find(c);
            if(it==children[v].end())continue;
            v=(*it).second;
        }
        while(v){
            Q.emplace(v);
            v=failure[v];
        }
        vector<int>ans;
        set<int>seen;
        while(!Q.empty()){
            int v=Q.front();Q.pop();
            if(seen.find(v)!=seen.end())continue;
            seen.insert(v);
            for(int i:node[v])ans.emplace_back(i);
            if(nextNode[v])Q.emplace(parent[v]);
            if(failure[v])Q.emplace(failure[v]);
        }
        return ans;
    }
};