// https://github.com/TKTYI/TKTYI-library/blob/main/math/nim_product.hpp
vector<vector<int>>small_nim_product(256,vector<int>(256));
void init(){
  for(int i=1;i<256;i++)small_nim_product[1][i]=small_nim_product[i][1]=i;
  for(int a=2;a<256;a++)for(int b=2;b<256;b++){
    if(a>b){small_nim_product[a][b]=small_nim_product[b][a];continue;}
    int s=b<4?1:b<16?2:4;
    int au=a>>s,al=a^(au<<s),bu=b>>s,bl=b^(bu<<s);
    int c=small_nim_product[au][bu];
    small_nim_product[a][b]=((c^small_nim_product[al][bu]^small_nim_product[au][bl])<<s)^small_nim_product[c][1ull<<(s-1)]^small_nim_product[al][bl];
  }
}
unsigned long long nim_product(unsigned long long A,unsigned long long B){
  using ull=unsigned long long;
  function<ull(ull,ull,int)>prod=[&](ull a,ull b,int s)->ull{
    if(s==4)return small_nim_product[a][b];
    ull au=a>>s,al=a^(au<<s),bu=b>>s,bl=b^(bu<<s);
    ull c=prod(au,bu,s/2);
    return ((c^prod(al,bu,s/2)^prod(au,bl,s/2))<<s)^prod(c,1ull<<(s-1),s/2)^prod(al,bl,s/2);
  };
  return prod(A,B,32);
}