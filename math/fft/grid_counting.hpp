// https://github.com/TKTYI/TKTYI-library/blob/main/math/fft/grid_counting.hpp
template<typename mint>
mint grid_counting(vector<bool>S){
    int N=S.size();
    vector<mint>ex(N+1,1),re(N+1);
    for(int i=1;i<=N;i++)ex[i]=ex[i-1]*i;
    for(int i=0;i<=N;i++)re[i]=1/ex[i];
    vector<int>A(N+1);
    for(int i=0;i<N;i++)A[i+1]=A[i]+S[i];
    function<vector<mint>(int,int,vector<mint>&)>dc=[&](int l,int r,vector<mint>&bottom){
  	    if(r-l==1){
            return S[l]?vector<mint>{bottom[1]}:vector<mint>{bottom[0],bottom[0]};
  	    }
        int m=(l+r)/2;
        vector<mint>left({bottom.begin(),bottom.begin()+A[m]+1-A[l]}),right({bottom.begin()+A[m]-A[l],bottom.end()});
        auto X=dc(l,m,left);
        int H=m-l-A[m]+A[l],W=A[r]-A[m];
        vector<mint>top(W+1),res(H+1);
        res[0]=right[W];top[0]=X[H];X[0]=right[0]=0;
        if(!W)for(int i=1;i<=H;i++)res[i]=X[i];
        else{
            vector<mint>F(H+W+1);
            for(int i=0;i<=H;i++)F[i]=ex[i+W-1]*re[W-1]*re[i];
            auto G=convolution(X,F);
            for(int i=1;i<=H;i++)res[i]+=G[i];
            for(int i=0;i<=H+W;i++)F[i]=ex[i];
            for(int i=0;i<=W;i++)right[i]*=re[W-i];
            G=convolution(F,right);
            for(int i=0;i<=W;i++)right[i]*=ex[W-i];
            for(int i=1;i<=H;i++)res[i]+=re[i-1]*G[i+W-1];
        }
        if(!H)for(int i=1;i<=W;i++)top[i]=right[i];
        else{
            vector<mint>F(H+W+1);
            for(int i=0;i<=W;i++)F[i]=ex[i+H-1]*re[H-1]*re[i];
            auto G=convolution(right,F);
            for(int i=1;i<=W;i++)top[i]+=G[i];
            for(int i=0;i<=H+W;i++)F[i]=ex[i];
            for(int i=0;i<=H;i++)X[i]*=re[H-i];
            G=convolution(F,X);
            for(int i=0;i<=H;i++)X[i]*=ex[H-i];
            for(int i=1;i<=W;i++)top[i]+=re[i-1]*G[i+H-1];
        }
        auto Y=dc(m,r,top);
        Y.erase(Y.begin());
        res.insert(res.end(),Y.begin(),Y.end());
  	    return res;
    };
    vector<mint>bottom(A[N]+1,1);
    return dc(0,N,bottom).back();
}