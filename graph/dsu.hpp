// https://github.com/TKTYI/TKTYI-library/blob/main/graph/dsu.hpp
struct dsu{
    private:
    vector<int>parent;
    public:
    dsu()=default;
	dsu(size_t n):parent(n,-1){}
	int leader(int i){
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