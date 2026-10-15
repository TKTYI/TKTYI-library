template<typename T>
void fast_hadamard_transformation(vector<T>&A){
    int h=1,n=0;
    while(1<<n<A.size())n++;
    for(int _=0;_<n;_++){
        for(int i=0;i<1<<n;i+=2*h){
            for(int j=i;j<i+h;j++){
                A[j]+=A[j+h];
                A[j+h]=A[j]-2*A[j+h];
            }
        }
        h*=2;
    }
    return;
}
template<typename T>
vector<T>xor_convolution(vector<T>A,vector<T>B){
    int n=0;
    while(1<<n<max(A.size(),B.size()))n++;
    vector<T>res(1<<n);
    A.resize(1<<n);
    B.resize(1<<n);
    fast_hadamard_transformation(A);
    fast_hadamard_transformation(B);
    for(int i=0;i<1<<n;i++)res[i]=A[i]*B[i];
    fast_hadamard_transformation(res);
    for(int i=0;i<1<<n;i++)res[i]/=1<<n;
    return res;
}