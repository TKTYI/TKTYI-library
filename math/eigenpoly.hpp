// https://github.com/TKTYI/TKTYI-library/blob/main/math/eigenpoly.hpp
template<typename T>
vector<T>eigenpoly(vector<vector<T>>A){
    int N=A.size();
    for(int i=0;i<N-1;i++){
        int t=i+1;
        while(t<N&&A[t][i]==T(0))t++;
        if(t==N)continue;
        swap(A[t],A[i+1]);
        for(int j=0;j<N;j++)swap(A[j][t],A[j][i+1]);
        
        for(int j=i+2;j<N;j++){
            T a=A[j][i]/A[i+1][i];
            for(int k=0;k<N;k++)A[j][k]-=A[i+1][k]*a;
            for(int k=0;k<N;k++)A[k][i+1]+=A[k][j]*a;
        }
    }
    vector<vector<T>>poly(N+1);
    poly[0]={1};
    for(int i=0;i<N;i++){
        poly[i+1].assign(i+2,T(0));
        for(int j=0;j<=i;j++)poly[i+1][j+1]+=poly[i][j],poly[i+1][j]-=A[i][i]*poly[i][j];
        for(int j=0;j<i;j++){
            T c=A[j][i];
            for(int k=j+1;k<=i;k++)c*=A[k][k-1];
            for(int k=0;k<=j;k++)poly[i+1][k]-=poly[j][k]*c;
        }
    }
    return poly[N];
}