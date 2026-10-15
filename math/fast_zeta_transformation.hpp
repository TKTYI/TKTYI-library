template<typename T>
vector<T>fast_zeta_transformation(vector<T>A){
    int N=0;
    while((1<<N)<A.size())N++;
    for(int j=0;j<N;j++)for(int i=0;i<(1<<N);i++)if(i&(1<<j))A[i]+=A[i&~(1<<j)];
    return A;
}
template<typename T>
vector<T>fast_mobius_transformation(vector<T>A){
    int N=0;
    while((1<<N)<A.size())N++;
    for(int j=0;j<N;j++)for(int i=0;i<(1<<N);i++)if(i&(1<<j))A[i]-=A[i^(1<<j)];
    return A;
}