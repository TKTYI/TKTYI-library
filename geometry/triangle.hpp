#include<bits/stdc++.h>
using namespace std;
template<typename T>
struct triangle{
    complex<T>A,B,C;
    T a,b,c;
    triangle(complex<T>_A,complex<T>_B,complex<T>_C):A(_A),B(_B),C(_C),a(abs(_B-_C)),b(abs(_C-_A)),c(abs(_A-_B)){}
    complex<T>incenter(){
        auto E=(a*A+c*C)/(a+c),F=(a*A+b*B)/(a+b);
        return ((E-B)*(C*conj(F)-F*conj(C))-(F-C)*(B*conj(E)-E*conj(B)))/((E-B)*conj(F-C)-(F-C)*conj(E-B));
    }
    T incenter_radius(){
        return sqrtl((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c))/2/(a+b+c);
    }
    T area(){
        return sqrtl((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c))/4;
    }
    complex<T>excenter(){
        return ((B-C)*norm(A)+(C-A)*norm(B)+(A-B)*norm(C))/((B-C)*conj(A)+(C-A)*conj(B)+(A-B)*conj(C));
    }
};