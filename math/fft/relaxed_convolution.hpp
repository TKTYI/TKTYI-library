// https://github.com/TKTYI/TKTYI-library/blob/main/math/fft/relaxed_convolution.hpp
template<typename mint>
struct relaxed_convolution{
  vector<mint>F,G,H;
  mint query(mint x,mint y){
    int n=F.size();
    F.emplace_back(x);
    G.emplace_back(y);
    for(int i=0;;i++){
      if((((n+2)>>i)<<i)!=n+2)break;
      int l=(1<<i)-1,r=(1<<(i+1))-1;
      if(n==l+l){
        vector<mint>pr=convolution(vector<mint>(F.begin()+l,F.begin()+r),vector<mint>(G.begin()+l,G.begin()+r));
        for(int j=0;j<pr.size();j++){
          if(H.size()<=j+n)H.emplace_back(pr[j]);
          else H[j+n]+=pr[j];
        }
        break;
      }
      vector<mint>pr1=convolution(vector<mint>(F.begin()+l,F.begin()+r),vector<mint>(G.begin()+n+1-(1<<i),G.begin()+n+1));
      vector<mint>pr2=convolution(vector<mint>(F.begin()+n+1-(1<<i),F.begin()+n+1),vector<mint>(G.begin()+l,G.begin()+r));
      for(int j=0;j<pr1.size();j++){
        if(H.size()<=j+n)H.emplace_back(pr1[j]+pr2[j]);
        else H[j+n]+=pr1[j]+pr2[j];
      }
    }
    return H[n];
  }
};