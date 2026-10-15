template<typename T>
struct rational{
    private:
    T x,y;
    public:
    rational(T a=0,T b=1):x(a),y(b){f();}
    rational f(){
        T a=x,b=y;
        while(a!=0&&b!=0){
            b=a%b;
            swap(a,b);
        }
        T g=a+b;
        if((g<0)^(y<0))g*=-1;
        x/=g;y/=g;
        return rational{x,y};
    }
    ld val(){
        return (ld)x/(ld)y;
    }
    bool operator==(rational r){
        return r.x*y==r.y*x;
    }
    bool operator<(rational r){
        return f().x*r.f().y<f().y*r.f().x;
    }
    rational operator+(rational r){
        rational res={r.y*x+r.x*y,r.y*y};
        return res.f();
    }
    rational operator-(rational r){
        rational res={r.y*x-r.x*y,r.y*y};
        return res.f();
    }
    rational operator*(rational r){
        rational res={x*r.x,y*r.y};
        return res.f();
    }
    rational operator/(rational r){
        rational res={x*r.y,y*r.x};
        return res.f();
    }
    T top(){
        return x;
    }
    T bottom(){
        return y;
    }
};