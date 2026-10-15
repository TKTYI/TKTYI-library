template<typename T>
vector<T>gcd_convolution(vector<T>A,vector<T>B){
    assert(A.size()==B.size());
    int N=A.size();
    for(int i=1;i<N;i++)for(int j=2*i;j<N;j+=i)A[i]+=A[j],B[i]+=B[j];
    vector<T>C(N);
    for(int i=1;i<N;i++)C[i]=A[i]*B[i];
    for(int i=N-1;i;i--)for(int j=2*i;j<N;j+=i)C[i]-=C[j];
    return C;
}