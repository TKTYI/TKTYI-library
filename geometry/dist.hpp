template<typename T>
long double dist(T x1,T y1,T x2,T y2){
    return sqrtl((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
template<typename T>
long double dist(T x,T y,T x1,T y1,T x2,T y2){
    long double d=min(dist(x,y,x1,y1),dist(x,y,x2,y2));
    long double t=((x-x2)*(x1-x2)+(y-y2)*(y1-y2))/((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if(0<=t&&t<=1)d=abs((y1-y2)*x-(x1-x2)*y+x1*y2-x2*y1)/dist(x1,y1,x2,y2);
    return d;
}
// depend on intersect.hpp
template<typename T>
long double dist(T x,T y,T x1,T y1,T x2,T y2){
    long double d=min(dist(x,y,x1,y1),dist(x,y,x2,y2));
    T t=(x-x2)*(x1-x2)+(y-y2)*(y1-y2);
    T s=(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
    if(0<=t&&t<=s)d=abs((y1-y2)*x-(x1-x2)*y+x1*y2-x2*y1)/sqrtl(s);
    return d;
}