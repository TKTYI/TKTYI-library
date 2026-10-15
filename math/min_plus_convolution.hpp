template<typename T>
vector<T>min_plus_convolution(vector<T>&a,vector<T>&b){
  if(a.size()==0)return b;
  if(b.size()==0)return a;
  for(int i=0;i+2<a.size();i++)assert(a[i+1]-a[i]<=a[i+2]-a[i+1]);
  vector<T>c(a.size()+b.size()-1,1+*max_element(a.begin(),a.end())+*max_element(b.begin(),b.end()));
  function<void(int,int,int,int)>f=[&](int l,int r,int x,int y){
    if(l>=r)return;
    int m=(l+r)/2,argmin;
    for(int i=x;i<y;i++)if(0<=m-i&&m-i<a.size()&&c[m]>a[m-i]+b[i])c[m]=a[m-i]+b[i],argmin=i;
    f(l,m,x,argmin+1);
    f(m+1,r,argmin,y);
  };
  f(0,c.size(),0,b.size());
  return c;
}
template<typename T>
vector<T>max_plus_convolution(vector<T>&a,vector<T>&b){
  if(a.size()==0)return b;
  if(b.size()==0)return a;
  for(int i=0;i+2<a.size();i++)assert(a[i+1]-a[i]>=a[i+2]-a[i+1]);
  vector<T>c(a.size()+b.size()-1,-1+*min_element(a.begin(),a.end())+*min_element(b.begin(),b.end()));
  function<void(int,int,int,int)>f=[&](int l,int r,int x,int y){
    if(l>=r)return;
    int m=(l+r)/2,argmax;
    for(int i=x;i<y;i++)if(0<=m-i&&m-i<a.size()&&c[m]<a[m-i]+b[i])c[m]=a[m-i]+b[i],argmax=i;
    f(l,m,x,argmax+1);
    f(m+1,r,argmax,y);
  };
  f(0,c.size(),0,b.size());
  return c;
}