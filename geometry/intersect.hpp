// https://github.com/TKTYI/TKTYI-library/blob/main/geometry/intersect.hpp
template<typename T>
bool intersect(T x1,T y1,T x2,T y2,T x3,T y3,T x4,T y4){
    T dx1=x2-x1,dy1=y2-y1,dx2=x4-x3,dy2=y4-y3;
    if(dx1*dy2==dx2*dy1){
        ll dx=x3-x1,dy=y3-y1;
        if(dx*dy1!=dy*dx1)return false;
        else if(x1==x2){
            if(y1>y2)swap(y1,y2);
            if(y3>y4)swap(y3,y4);
            return max(y1,y3)<=min(y2,y4);
        }
        else{
            if(x1>x2)swap(x1,x2);
            if(x3>x4)swap(x3,x4);
            return max(x1,x3)<=min(x2,x4);
        }
    }
    else{
        ll det=dx1*dy2-dx2*dy1;
        ll x=dx1*(x3*dy2-dx2*y3)-dx2*(x1*dy1-dx1*y1);
        ll y=dy1*(x3*dy2-dx2*y3)-dy2*(x1*dy1-dx1*y1);
        if(det<0){
            det=-det;
            x=-x;
            y=-y;
        }
        if(x1==x2){
            if(y1>y2)swap(y1,y2);
            if(det*y1>y||y>det*y2)return false;
        }
        else{
            if(x1>x2)swap(x1,x2);
            if(det*x1>x||x>det*x2)return false;
        }
        if(x3==x4){
            if(y3>y4)swap(y3,y4);
            if(det*y3>y||y>det*y4)return false;
        }
        else{
            if(x3>x4)swap(x3,x4);
            if(det*x3>x||x>det*x4)return false;
        }
        return true;
    }
}