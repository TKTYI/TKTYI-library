// https://github.com/TKTYI/TKTYI-library/blob/main/math/lcm_convolution.hpp
template<typename T>
vector<T>lcm_convolution(vector<T>A,vector<T>B){
    assert(A.size()==B.size());
    int N=A.size();
    for(int i=N-1;i;i--)for(int j=2*i;j<N;j+=i)A[j]+=A[i],B[j]+=B[i];
    vector<T>C(N);
    for(int i=1;i<N;i++)C[i]=A[i]*B[i];
    for(int i=1;i<N;i++)for(int j=2*i;j<N;j+=i)C[j]-=C[i];
    return C;
}