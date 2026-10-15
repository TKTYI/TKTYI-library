template<typename T>
long double dist(pair<T,T>p1,pair<T,T>p2){
    return dist(p1.first,p1.second,p2.first,p2.second);
}
// assume sorted by x coordinate
long double closest_pair(vector<pair<long double,long double>>::iterator begin,vector<pair<long double,long double>>::iterator end){
    int size=end-begin;
    assert(size>1);
    if(size==2)return dist(*begin,*(begin+1));
    if(size==3)return min({dist(*begin,*(begin+1)),dist(*begin,*(begin+2)),dist(*(begin+1),*(begin+2))});
    auto cen=begin+size/2;
    auto d=min(closest_pair(begin,cen),closest_pair(cen,end));
    vector<pair<long double,long double>>strip;
    for(auto it=begin;it<end;it++){
        if(abs((*it).first-(*cen).first)<d)strip.emplace_back(*it);
    }
    sort(strip.begin(),strip.end(),[](pair<long double,long double>&p,pair<long double,long double>&q){return p.second<q.second;});
    for(int i=0;i<strip.size();i++){
        for(int j=i-1;j>=0&&strip[j].second>strip[i].second-d;j--){
            d=min(d,dist(strip[i],strip[j]));
        }
        for(int j=i+1;j<strip.size()&&strip[j].second<strip[i].second+d;j++){
            d=min(d,dist(strip[i],strip[j]));
        }
    }
    return d;
}