template<typename T=long double,class comp=std::less<T>>
struct convex_hull_trick_dynamic{
    // max
    private:
    const T INF=1e18;
    set<pair<pair<T,T>,pair<T,T>>>segments;
    set<pair<pair<T,T>,pair<T,T>>>lines;
    T intersection(pair<T,T>l1,pair<T,T>l2){
        return (l2.second-l1.second)/(l1.first-l2.first);
    }
    public:
    T get(T x){
        auto it=prev(segments.lower_bound(make_pair(make_pair(x,INF),make_pair(INF,INF))));
        return (*it).second.first*x+(*it).second.second;
    }
    void add(T a,T b){
        pair<T,T>l=make_pair(a,b);
        if(lines.size()==0){
            lines.insert(make_pair(l,make_pair(-INF,INF)));
            segments.insert(make_pair(make_pair(-INF,INF),l));
            return;
        }
        auto it=lines.lower_bound(make_pair(l,make_pair(-INF,-INF)));
        if(it!=lines.end()&&(*it).first.first==a)return;
        if(it!=lines.begin()&&(*prev(it)).first.first==a){
            pair<pair<T,T>,pair<T,T>>p=*prev(it);
            lines.erase(prev(it));
            segments.erase(make_pair(p.second,p.first));
            it=lines.lower_bound(make_pair(l,make_pair(-INF,-INF)));
        }
        if(it!=lines.end()){
            T x=(*it).second.first;
            if(comp()(a*x+b,(*it).first.first*x+(*it).first.second))return;
        }
        {
            auto left=it,right=it;
            while(left!=lines.begin()){
                T x=(*prev(left)).second.first;
                if(comp()(a*x+b,(*prev(left)).first.first*x+(*prev(left)).first.second))break;
                left--;
            }
            while(right!=lines.end()){
                T x=(*right).second.second;
                if(comp()(a*x+b,(*right).first.first*x+(*right).first.second))break;
                right++;
            }
            vector<pair<pair<T,T>,pair<T,T>>>P;
            for(auto i=left;i!=right;i++)P.emplace_back(*i);
            for(pair<pair<T,T>,pair<T,T>>p:P){
                lines.erase(p);
                segments.erase(make_pair(p.second,p.first));
            }
        }
        it=lines.lower_bound(make_pair(l,make_pair(-INF,-INF)));
        T left=-INF,right=INF;
        if(it!=lines.begin()){
            it--;
            left=intersection(l,(*it).first);
            pair<pair<T,T>,pair<T,T>>ls=*it;
            lines.erase(it);
            segments.erase(make_pair(ls.second,ls.first));
            ls.second.second=left;
            lines.insert(ls);
            segments.insert(make_pair(ls.second,ls.first));
            it=lines.lower_bound(make_pair(l,make_pair(-INF,-INF)));
        }
        if(it!=lines.end()){
            right=intersection(l,(*it).first);
            pair<pair<T,T>,pair<T,T>>ls=*it;
            lines.erase(it);
            segments.erase(make_pair(ls.second,ls.first));
            ls.second.first=right;
            lines.insert(ls);
            segments.insert(make_pair(ls.second,ls.first));
            it=lines.lower_bound(make_pair(l,make_pair(-INF,-INF)));
        }
        lines.insert(make_pair(l,make_pair(left,right)));
        segments.insert(make_pair(make_pair(left,right),l));
    }
    void print(){
        for(auto[line,seg]:lines){cout<<line.first<<"x"<<(line.second>=0?"+":"")<<line.second<<"("<<seg.F<<","<<seg.S<<") ";}cout<<endl;
    }
};