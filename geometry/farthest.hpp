// https://github.com/TKTYI/TKTYI-library/blob/main/geometry/farthest.hpp
// depend on convex_hull.hpp
template<typename T>
T area(pair<T,T>p1,pair<T,T>p2,pair<T,T>p3){
    return (p2.first-p1.first)*(p3.second-p1.second)-(p2.second-p1.second)*(p3.first-p1.first);
}
template<typename T>
long double dist(pair<T,T>p1,pair<T,T>p2){
    return sqrtl((p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second));
}
template<typename T>
long double farthest(vector<pair<T,T>>P){
    P=convex_hull(P);
    P.emplace_back(P[0]);
    long double ans=0;
    int v=1;
    for(int i=0;i<P.size()-1;i++){
        while(area(A[i],A[i+1],A[v])<area(A[i],A[i+1],A[v+1])){
            ans=max(ans,dist(A[i],A[v]));
            v++;
            if(v==P.size())v=0;
        }
        ans=max(ans,dist(A[i],A[v]));
        ans=max(ans,dist(A[i],A[v+1]));
    }
    return ans;
}