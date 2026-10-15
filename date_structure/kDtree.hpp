template<typename T>
struct kDTree{
  struct node{
    int l,r,size;
    T xmin,xmax,ymin,ymax;
  };
  vector<node>V;
  using Iter=vector<pair<T,T>>::iterator;
  int init(Iter begin,Iter end,bool divx){
    if(begin==end)return -1;
    T xmin=numeric_limits<T>::max(),xmax=numeric_limits<T>::min(),ymin=numeric_limits<T>::max(),ymax=numeric_limits<T>::min();
    for(auto p=begin;p!=end;p++){
      ll x=(*p).first,y=(*p).second;
      if(x<xmin)xmin=x;
      if(x>xmax)xmax=x;
      if(y<ymin)ymin=y;
      if(y>ymax)ymax=y;
    }
    int i=V.size();
    V.emplace_back(node{-1,-1,int(end-begin),xmin,xmax,ymin,ymax});
    if(end-begin<=1)return i;
    auto cen=begin+V[i].size/2;
    if(divx)nth_element(begin,cen,end,[](pair<T,T>a,pair<T,T>b){return a.first<b.first;});
    else nth_element(begin,cen,end,[](pair<T,T>a,pair<T,T>b){return a.second<b.second;});
    V[i].l=init(begin,cen,!divx);
    V[i].r=init(cen,end,!divx);
    return i;
  }
  kDTree(Iter begin,Iter end){
    V.reserve((end-begin)<<1);
    init(begin,end,true);
  }
  T closest2(int i,T x,T y,T lim){
    if(i<0)return lim;
    if(V[i].size==1)return min(lim,(x-V[i].xmin)*(x-V[i].xmin)+(y-V[i].ymin)*(y-V[i].ymin));
    T dx=max({(T)0,V[i].xmin-x,x-V[i].xmax}),dy=max({(T)0,V[i].ymin-y,y-V[i].ymax});
    if(dx*dx+dy*dy>=lim)return lim;
    lim=min(lim,closest2(V[i].l,x,y,lim));
    lim=min(lim,closest2(V[i].r,x,y,lim));
    return lim;
  }
  T closest2(T x,T y,T lim){return closest2(0,x,y,lim);}
};