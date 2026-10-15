T interpolation(vector<T>&X,vector<T>&Y,T x){
	assert(X.size()==Y.size());
	int N=X.size();
	T ans=0;
	rep(i,0,N){
		T a=0;
		rep(j,0,N)if(i!=j)a*=x-X[j],a/=X[i]-X[j];
		ans+=a*Y[i];
	}
	return ans;
}