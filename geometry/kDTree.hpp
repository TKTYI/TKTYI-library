template<typename T>
struct kDTree{
    using Iter=vector<pair<pair<T,T>,int>>::iterator;
    kDTree *l=nullptr,*r=nullptr;
    int size=0;
    T xmin=numeric_limits<T>::max(),xmax=numeric_limits<T>::min(),ymin=numeric_limits<T>::max(),ymax=numeric_limits<T>::min();
    vector<int>idx;
    kDTree(Iter begin,Iter end,bool divx=true){
        for(auto p=begin;p!=end;p++){
            auto[x,y]=(*p).first;
            chmin(xmin,x);
            chmax(xmax,x);
            chmin(ymin,y);
            chmax(ymax,y);
            idx.emplace_back((*p).second);
        }
        size=int(end-begin);
        if(size<=1)return;
        auto cen=begin+size/2;
        if(divx)nth_element(begin,cen,end,[](pair<pair<int,int>,int>a,pair<pair<int,int>,int>b){return a.first.first<b.first.first;});
        else nth_element(begin,cen,end,[](pair<pair<int,int>,int>a,pair<pair<int,int>,int>b){return a.first.second<b.first.second;});
        l=new kDTree(begin,cen,!divx);
        r=new kDTree(cen,end,!divx);
    }
    int count(T x1,T x2,T y1,T y2)const{
        if(x2<xmin||xmax<x1||y2<ymin||ymax<y1)return 0;
        if(x1<=xmin&&xmax<=x2&&y1<=ymin&&ymax<=y2)return size;
        return l->count(x1,x2,y1,y2)+r->count(x1,x2,y1,y2);
    }
    vector<int>search(T x1,T x2,T y1,T y2)const{
        if(x2<xmin||xmax<x1||y2<ymin||ymax<y1)return {};
        if(x1<=xmin&&xmax<=x2&&y1<=ymin&&ymax<=y2)return idx;
        auto ps1=l->search(x1,x2,y1,y2);
        auto ps2=r->search(x1,x2,y1,y2);
        ps1.insert(ps1.end(),ps2.begin(),ps2.end());
        return ps1;
    }
    T closest2(T x,T y,T lim){
      if(size==0)return lim;
      if(size==1)return min(lim,(x-xmin)*(x-xmin)+(y-ymin)*(y-ymin));
      if(x<xmin&&(x-xmin)*(x-xmin)>=lim)return lim;
      if(x>xmax&&(x-xmax)*(x-xmax)>=lim)return lim;
      if(y<ymin&&(y-ymin)*(y-ymin)>=lim)return lim;
      if(y>ymax&&(y-ymax)*(y-ymax)>=lim)return lim;
      auto lans=l->closest2(x,y,lim);
      chmin(lim,lans);
      auto rans=r->closest2(x,y,lim);
      return min(lim,rans);
    }
};