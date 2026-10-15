// https://github.com/TKTYI/TKTYI-library/blob/main/math/BMBM.hpp
template<typename T>
vector<T>BMBM(vector<T>&A,int L){
  assert(A.size()>=2*L);
  vector<vector<T>>B(L,vector<T>(2*L));
  for(int i=0;i<L;i++)for(int j=0;j<L;j++)B[i][j]=A[i+j];
  for(int i=0;i<L;i++)B[i][i+L]=1;
  for(int i=0;i<L;i++){
    int t=i;
    while(t<L&&B[t][i]==0)t++;
    if(t==L)break;
    swap(B[t],B[i]);
    for(int j=i+1;j<2*L;j++)B[i][j]/=B[i][i];
    B[i][i]=1;
    for(int j=0;j<L;j++)if(j!=i){
      T c=B[j][i];
      for(int k=i;k<2*L;k++)B[j][k]-=c*B[i][k];
    }
  }
  vector<T>coeff(L);
  for(int i=0;i<L;i++)for(int j=0;j<L;j++)coeff[i]+=B[i][j+L]*A[j+L];
  return coeff;
}