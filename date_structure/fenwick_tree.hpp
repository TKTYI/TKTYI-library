template<typename T>
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
    void print(){
        for(auto i:tree)cout<<i<<" ";cout<<endl;
    }
};