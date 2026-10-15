// https://github.com/TKTYI/TKTYI-library/blob/main/math/bigint.hpp
struct bigint{
  bool neg;
  vector<int>d;
  bigint(){neg=false;}
  bigint(__int128 x){
    neg=(x<0);
    if(neg)x=-x;
    while(x>0){d.push_back(x%10);x/=10;}
  }
  int operator[](int k){return d[k];}
  int size(){return d.size();}
};
bool operator==(bigint A,bigint B){return A.neg==B.neg&&A.d==B.d;}
bool operator!=(bigint A,bigint B){return!(A==B);}
bool operator<(bigint A,bigint B){
  if(A.neg&&B.neg){A.neg=B.neg=false;return!(A<B);}
  if(A.neg)return true;
  if(B.neg)return false;
  int N1=A.size(),N2=B.size();
  if(N1!=N2)return N1<N2;
  for(int i=N1-1;i>=0;i--)if(A[i]!=B[i])return A[i]<B[i];
  return false;
}
bool operator<=(bigint A,bigint B){return A<B||A==B;}
bool operator>(bigint A,bigint B){return B<A;}
bigint operator-(bigint A){if(A.size())A.neg=!A.neg;return A;}
bigint operator+(bigint A,bigint B);
bigint operator-(bigint A,bigint B);
bigint operator+(bigint A,bigint B){
  if(B.neg)return A-(-B);
  if(A.neg){A.neg=false;if(B<A)return-(A-B);return B-A;}
  int N1=A.size(),N2=B.size(),N=max(N1,N2)+1;
  bigint C;
  C.d=vector<int>(N,0);
  for(int i=0;i<N1;i++)C.d[i]+=A[i];
  for(int i=0;i<N2;i++)C.d[i]+=B[i];
  for(int i=0;i<N-1;i++)if(C[i]>=10)C.d[i+1]++,C.d[i]-=10;
  if(C.size()&&C[N-1]==0)C.d.pop_back();
  return C;
}
bigint operator-(bigint A,bigint B){
  if(B.neg)return A+(-B);
  if(A.neg)return-((-A)+B);
  if(A<B)return-(B-A);
  int N1=A.size(),N2=B.size();
  bigint C=A;
  for(int i=0;i<N2;i++)C.d[i]-=B[i];
  for(int i=0;i<N1-1;i++)if(C[i]<0)C.d[i+1]--,C.d[i]+=10;
  while(C.size()&&C.d.back()==0)C.d.pop_back();
  return C;
}
bigint operator*(bigint A,bigint B){
  if(A.size()==0)return A;
  if(B.size()==0)return B;
  bool neg=A.neg^B.neg;
  int N1=A.size(),N2=B.size(),N=N1+N2;
  bigint C;
  C.d=vector<int>(N,0);
  for(int i=0;i<N1;i++)for(int j=0;j<N2;j++)C.d[i+j]+=A[i]*B[j];
  for(int i=0;i<N-1;i++)C.d[i+1]+=C[i]/10,C.d[i]%=10;
  while(C.size()&&C.d.back()==0)C.d.pop_back();
  if(neg)C.neg=true;
  return C;
}
pair<bigint, bigint> divmod(bigint A, bigint B){
  int N1 = A.size();
  int N2 = B.size();
  bigint Q;
  for (int i = N1 - N2; i >= 0; i--){
  	int q = 0;
  	if (A.size() >= N2 + i){
  	  N1 = A.size();
      bigint C;
      C.d = vector<int>(N1 - i);
      for (int j = 0; j < N1 - i; j++){
        C.d[j] = A[i + j];
      }
      for (int j = 1; j <= 9; j++){
        if (B * j <= C){
          q = j;
        } else {
          break;
        }
      }
    }
    Q.d.push_back(q);
    bigint B2 = B * q;
    int M = B2.size();
    bigint B3;
    B3.d = vector<int>(M + i, 0);
    for (int j = 0; j < M; j++){
      B3.d[i + j] = B2[j];
    }
    while (B3.size() >= 2 && B3.d.back() == 0){
      B3.d.pop_back();
    }
    A = A - B3;
  }
  if (Q.size() == 0){
    Q.d.push_back(0);
  }
  reverse(Q.d.begin(), Q.d.end());
  if (Q.size() >= 2 && Q.d.back() == 0){
    Q.d.pop_back();
  }
  return make_pair(Q, A);
}
bigint operator /(bigint A, bigint B){
  return divmod(A, B).first;
}
bigint operator %(bigint A, bigint B){
  return divmod(A, B).second;
}