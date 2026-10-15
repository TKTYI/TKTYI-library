#include<utility>
template<typename T>
struct point{
    T x,y;
    point operator+(point a){
        return point{x+a.x,y+a.y};
    }
    point operator-(point a){
        return point{x-a.x,y-a.y};
    }
    T operator*(point a){
        return x*a.x+y*a.y;
    }
    T square_dist(){
        return x*x+y*y;
    }
};
template<typename T>
T cross(point<T>p,point<T>q){
    return p.x*q.y-p.y*q.x;
}
template<typename T>
struct segment{
    point<T>p,q;
};
template<typename T>
bool intersect(segment<T>s,point<T>p){
    point<T>a=p-s.p,b=p-s.q;
    return a.x*b.y==a.y*b.x&&a*b<=0;
}
template<typename T>
bool intersect(segment<T>s1,segment<T>s2){
    if(intersect(s1,s2.p)||intersect(s1,s2.q)||intersect(s2,s1.p)||intersect(s2,s1.q))return 1;
    point<T>a=s1.q-s1.p,b=s2.p-s1.p,c=s2.q-s1.p;
    T g=cross(a,b),h=cross(a,c);
    if(g*h>=0)return 0;
    swap(s1,s2);
    a=s1.q-s1.p,b=s2.p-s1.p,c=s2.q-s1.p;
    g=cross(a,b),h=cross(a,c);
    return g*h<0;
}
template<typename T>
std::pair<long double,long double>line_intersection(segment<T>s1,segment<T>s2){
    point<T>a=s1.q-s1.p,b=s2.p-s2.q,c=s2.q-s1.p;
    long double t=(ld)-cross(a,c)/cross(a,b);
    return make_pair(t*b.x+s2.q.x,t*b.y+s2.q.y);
}