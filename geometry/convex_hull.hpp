// https://github.com/TKTYI/TKTYI-library/blob/main/geometry/convex_hull.hpp
template<typename T>
vector<pair<T,T>>convex_hull(vector<pair<T,T>>P){
    sort(P.begin(),P.end());
    P.erase(unique(P.begin(),P.end()),P.end());
    if(P.size()<3)return P;
    vector<pair<T,T>>upper,lower;
    for(auto[x,y]:P){
        while(lower.size()>1){
            auto [x1,y1]=lower[lower.size()-2];
            auto [x2,y2]=lower[lower.size()-1];
            if((x-x1)*(y2-y1)>=(y-y1)*(x2-x1))lower.erase(lower.end()-1);
            else break;
        }
        lower.emplace_back(make_pair(x,y));
    }
    reverse(P.begin(),P.end());
    for(auto[x,y]:P){
        while(upper.size()>1){
            auto [x1,y1]=upper[upper.size()-2];
            auto [x2,y2]=upper[upper.size()-1];
            if((x-x1)*(y2-y1)>=(y-y1)*(x2-x1))upper.erase(upper.end()-1);
            else break;
        }
        upper.emplace_back(make_pair(x,y));
    }
    lower.insert(lower.end(),upper.begin()+1,upper.end()-1);
    return lower;
}