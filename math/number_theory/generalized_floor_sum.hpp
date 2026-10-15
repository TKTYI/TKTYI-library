// https://github.com/TKTYI/TKTYI-library/blob/main/math/number_theory/generalized_floor_sum.hpp
tuple<__int128,__int128,__int128>generalized_floor_sum(__int128 N,__int128 M,__int128 A,__int128 B){
    //(0,1),(1,1),(0,2)
    assert(N>=0&&M>0&&A>=0&&B>=0);
    if(A>=M){
        __int128 A1=A/M,A2=A%M;
        auto t=generalized_floor_sum(N,M,A2,B);
        __int128 p=get<0>(t),q=get<1>(t),r=get<2>(t);
        return {p+N*(N-1)/2*A1,q+N*(N-1)*(2*N-1)/6*A1,r+2*A1*q+A1*A1*N*(2*N-1)*(N-1)/6};
    }
    if(B>=M){
        __int128 B1=B/M,B2=B%M;
        auto t=generalized_floor_sum(N,M,A,B2);
        __int128 p=get<0>(t),q=get<1>(t),r=get<2>(t);
        return {p+N*B1,q+N*(N-1)/2*B1,r+2*B1*p+B1*B1*N};
    }
    if(!A)return {(B/M)*N,(B/M)*N*(N-1)/2,(B/M)*(B/M)*N};
    __int128 K=(A*(N-1)+B)/M;
    auto t=generalized_floor_sum(K,A,M,M-B+A-1);
    __int128 p=get<0>(t),q=get<1>(t),r=get<2>(t);
    return {N*K-p,N*(N-1)/2*K+(p-r)/2,N*K*K-p-2*q};
}